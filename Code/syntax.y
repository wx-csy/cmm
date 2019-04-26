%code requires {

#include "ast/ast.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/function.h"
#include "ast/type.h"

}

%{

#include "ast/ast.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/function.h"
#include "ast/type.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmm.h"
#include "error.h"

void yyerror(const char*);

#define YYLTYPE cmm_loc_t;

/* track current position */
#define YYLLOC_DEFAULT(Cur, Rhs, N) {       \
    do {                                    \
        if (N) {                            \
            (Cur) = YYRHSLOC(Rhs, 1);       \
        } else {                            \
            (Cur) = YYRHSLOC(Rhs, 0);       \
        }                                   \
    while (0)

/* type for current deflist */
static Type *Specifier_Type = NULL;
%}

%union {
    unsigned long int_val;
    float float_val;
    const char *name;
    enum BasicType basictype;
    enum BinaryOperator binaryop;

    struct Program *program;
    struct {
            FuncList funclist;
            VarList varlist;
    } extdef;
    struct Expression *expr;    
    struct Statement *stmt;
    StmtList stmtlist;
    struct Type *type;
    struct {
         struct Variable *var;
         struct Type **underlying;
    } vardec;
    struct Variable *var;
    VarList varlist;
    struct Function *func;
    ArgList arglist;
    int dummy;
}

%define parse.error verbose
%start Program
%type  <program> Program;
%token <int_val>        INT
%token <float_val>      FLOAT
%token <name>           ID
%token <basictype>      TYPE
%token IF WHILE RETURN STRUCT

%right      '='
%left       AND OR
%left  <binaryop>     RELOP
%left       '+' '-'
%left       '*' '/'
%right      '!' UMINUS
%left       '.' '[' ']' '(' ')'

%nonassoc   LOWER_THAN_ELSE
%nonassoc   ELSE

/* High-level Definitions */
%type <extdef> ExtDefList ExtDef ExtDecList

/* Specifiers */
%type <type> Specifier StructSpecifier
%type <name> OptTag Tag

/* Declarators */
%type <vardec> VarDec
%type <func> FunDec
%type <varlist> VarList ParamList
%type <var> ParamDec

/* Statements */
%type <stmt> Stmt CompSt
%type <stmtlist> StmtList

/* Local Definitions */
%type <varlist> DecList Def DefList
%type <var> Dec

/* Expressions */
%type <expr> Exp
%type <arglist> Args ArgList

%%

// High level definitions

Program : 
                                        {
            symtbl_push_scope(false);
        }
      ExtDefList                        {
            symtbl_pop_scope();
            $$ = Program_Constructor($ExtDefList.funclist, $ExtDefList.varlist);
        }
    ;

ExtDefList : 
      ExtDef ExtDefList[old]            {
            $$ = $old;
            list_join(&$$.funclist, $old.funclist);
            list_join(&$$.varlist, $old.varlist);
        }
    | %empty                            {
            memset(&$$, 0, sizeof($$));
        }
    ;

ExtDef : 
      Specifier ExtDecList ';'          {
            $$ = $ExtDecList;
        }
    | Specifier ';'                     { }
    | Specifier FunDec CompSt           {
            $FunDec->rettype = $Specifier;
            $FunDec->stmt = $CompSt;
            symtbl_pop_scope();
            memset(&$$, 0, sizeof($$));
            list_prepend(&$$.funclist, $FunDec);
        }
    | error                             {
            memset(&$$, 0, sizeof($$));
        }
    ;

ExtDecList :
      VarDec                            {
            memset(&$$, 0, sizeof($$));
            *$VarDec.underlying = Specifier_Type;
            Type_Array_Semantic_Finalize($VarDec.var->valtype);
            list_prepend(&$$.varlist, $VarDec.var);
               }
    | VarDec ',' ExtDecList[old]        {
            $$ = $old;
            *$VarDec.underlying = Specifier_Type;
            Type_Array_Semantic_Finalize($VarDec.var->valtype);
            list_prepend(&$$.varlist, $VarDec.var);
        }

    ;

// Specifiers

Specifier : 
      TYPE                              {
            $$ = Type_Basic_Constructor($TYPE);
                  Specifier_Type = $Specifier;
        }
    | StructSpecifier                   {
            $$ = $StructSpecifier;
                  Specifier_Type = $Specifier;
        }
    ;

StructSpecifier : 
      STRUCT OptTag                     {
            if ($OptTag) {
                    $<type>$ = Type_Struct_Constructor(yylloc, $OptTag);

            } else {
                    $<type>$ = Type_Struct_Constructor(yylloc, "<anonymous struct>");
            }
            symtbl_push_scope(true);
        } [structdef]
      '{' DefList '}'                   {
            $$ = $<type>structdef;
            $$->varlist = $DefList;
            $$->symtable = symtbl_scope->variables;
            symtbl_pop_scope();
            Type_Struct_Semantic_Finalize($$);
            if ($OptTag) symtbl_struct_insert($OptTag, $$);
        }
    | STRUCT Tag                        {
            $$ = symtbl_struct_find($Tag, yylloc);
        }
    ;

OptTag : 
      ID                                { $$ = $ID; }
    | %empty                            { $$ = NULL; }
    ;

Tag :                                   
      ID                                { $$ = $ID; }
    ;

// Declarators

VarDec : 
      ID                                {
            $$.var = Variable_Constructor(yylloc, $ID);
            $$.underlying = &$$.var->valtype;
            symtbl_variable_insert($ID, $VarDec.var);
        }
    | VarDec '[' INT ']'                {
            $$.var = $1.var;
            $$.underlying =  &(
                *($1.underlying) = Type_Array_Constructor($INT)
            )->underlying;
        }
    ;

FunDec : 
      ID                                {
            $<func>$ = Function_Constructor($ID, yylloc);
            symtbl_function_insert($ID, $<func>$);
            symtbl_push_scope(false);
        }[func]
      '(' ParamList ')'                 {
            $$ = $<func>func;
            $$->paramlist = $ParamList;

        }
    ;

ParamList :
      VarList                           {
            $$ = $VarList;
        }
    | %empty                            {
            $$ = NULL;
        }

VarList : // ParamList
      ParamDec ',' VarList[old]         {
            $$ = $old;
            list_prepend(&$$, $ParamDec);
        }
    | ParamDec                          {
            $$ = NULL;
            list_prepend(&$$, $ParamDec);
        }
    ;

ParamDec : 
      Specifier VarDec                  {
            $$ = $VarDec.var;
            *($VarDec.underlying) = $Specifier;
            Type_Array_Semantic_Finalize($$->valtype);
        }
    ;

// Statements

CompSt : 
      '{' DefList StmtList '}'          { 
            $$ = Statement_Compound_Constructor(yylloc, $DefList, $StmtList);
        }
    ;

StmtList :                              
      Stmt StmtList[old]                { 
            $$ = $old;
            list_prepend(&$$, $Stmt);
        }
    | %empty                            { 
            $$ = NULL;
        }
    ;

Stmt : 
      Exp ';'                           { 
            $$ = Statement_Expression_Constructor(yylloc, $Exp);
        }
    | error ';'                         {
            $$ = &Statement_Invalid;  /* TODO: better error handling */
        }
    |                                   {
            symtbl_push_scope(false);
        }
      CompSt                            {
            symtbl_pop_scope();
            $$ = $CompSt;
        }
    | RETURN Exp ';'                    { 
            $$ = Statement_Return_Constructor(yylloc, $Exp);
        }
    | IF '(' Exp ')' Stmt[s1] %prec LOWER_THAN_ELSE     { 
            $$ = Statement_IfThen_Constructor(yylloc, $Exp, $s1);
        }
    | IF '(' Exp ')' Stmt[s1] ELSE Stmt[s2]             {
            $$ = Statement_IfThenElse_Constructor(yylloc, $Exp, $s1, $s2);
        }
    | WHILE '(' Exp ')' Stmt[s1]        { 
            $$ = Statement_While_Constructor(yylloc, $Exp, $s1);
        }
    ;

// Local Definitions

DefList : 
      Def DefList[old]                  {
            $$ = $Def;
            list_join(&$$, $old);
        }
    | %empty                            {
            $$ = NULL;
        }
    ;

Def : 
      Specifier DecList ';'             {
            $$ = $DecList;
        }
    ;

DecList : 
      Dec                               {
            $$ = NULL;
            list_prepend(&$$, $Dec);
        }
    | Dec ',' DecList[old]              {
            $$ = $old;
            list_prepend(&$$, $Dec);
        }
    ;

Dec : 
      VarDec                            {
            $$ = $VarDec.var;
            *$VarDec.underlying = Specifier_Type;
            Type_Array_Semantic_Finalize($$->valtype);
        }
    | VarDec '=' Exp                    {
            $$ = $VarDec.var;
            *$VarDec.underlying = Specifier_Type;
            Type_Array_Semantic_Finalize($$->valtype);
            if (symtbl_scope->is_struct_scope) {
                cmm_error(CMM_ERROR_INIT_MEMBER, yylloc);
            } else {
                $$->initializer = $Exp;
            }
        }
    ;

// Expressions

Exp :
      Exp '=' Exp                       {
            $$ = Expression_Assign_Constructor(yylloc, $1, $3);
        }
    | Exp AND Exp                       {
            $$ = Expression_Binary_Constructor(BOP_AND, yylloc, $1, $3);
        }
    | Exp OR Exp                        {
            $$ = Expression_Binary_Constructor(BOP_OR, yylloc, $1, $3);
        }
    | Exp RELOP Exp                     {
            $$ = Expression_Binary_Constructor($2, yylloc, $1, $3);
        }
    | Exp '+' Exp                       {
            $$ = Expression_Binary_Constructor(BOP_ADD, yylloc, $1, $3);
        }
    | Exp '-' Exp                       {
            $$ = Expression_Binary_Constructor(BOP_MINUS, yylloc, $1, $3);
        }
    | Exp '*' Exp                       {
            $$ = Expression_Binary_Constructor(BOP_STAR, yylloc, $1, $3);
        }
    | Exp '/' Exp                       { 
            $$ = Expression_Binary_Constructor(BOP_DIV, yylloc, $1, $3);
        }
    | '(' Exp ')'                       { 
            $$ = $2;
        }
    | '-' Exp   %prec UMINUS            { 
            $$ = Expression_Unary_Constructor(UOP_NEGATE, yylloc, $2);
        }
    | '!' Exp   %prec UMINUS            { 
            $$ = Expression_Unary_Constructor(UOP_NOT, yylloc, $2);
        }
    | ID '(' Args ')'                   {
            $$ = Expression_FuncCall_Constructor(yylloc, $ID, $Args);
        }
    | Exp '[' Exp ']'                   { 
            $$ = Expression_Binary_Constructor(BOP_ARRAY_ACCESS, yylloc, $1, $3);
        }
    | Exp '.' ID                        { 
            $$ = Expression_MemberAccess_Constructor(yylloc, $1, $ID);
        }
    | ID                                { 
            $$ = Expression_Variable_Constructor(yylloc, $ID);
        }
    | INT                               { 
            $$ = Expression_Literal_int_Constructor(yylloc, $INT);
        }
    | FLOAT                             { 
            $$ = Expression_Literal_float_Constructor(yylloc, $FLOAT);
        }
    ;

Args :
      ArgList                           {
            $Args = $ArgList;
        }
    | %empty                            {
            $Args = NULL;
        }

ArgList :
      Exp ',' ArgList[old]              {
            $$ = $old;
            list_prepend(&$$, $Exp);
        }
    | Exp                               {
            $$ = NULL;
            list_prepend(&$$, $Exp);
        }

    ;

%%

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, yylloc, msg);
}

