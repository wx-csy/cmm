%code requires {
    #include "ast/ast.h"
    #include "ast/expression.h"
    #include "ast/statement.h"
    #include "ast/variable.h"
    #include "ast/function.h"
    #include "ast/type.h"
}

%{

#include <stdio.h>
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
    int int_val;
    float float_val;
    const char *name;
    enum BasicType basictype;
    enum UnaryOperator unaryop;
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
%start  Program
%token <int_val>        INT
%token <float_val>      FLOAT
%token <name>           ID
%token <basictype>      TYPE
%token IF WHILE RETURN STRUCT

%right      '='
%left       AND OR
%left  <unaryop>     RELOP
%left       '+' '-'
%left       '*' '/'
%right      '!' UMINUS
%left       '.' '[' ']' '(' ')'

%nonassoc   LOWER_THAN_ELSE
%nonassoc   ELSE

/* High-level Definitions */
%type <dummy> Program ExtDefList ExtDef ExtDecList

/* Specifiers */
%type <type> Specifier StructSpecifier
%type <name> OptTag Tag

/* Declarators */
%type <vardec> VarDec
%type <func> FunDec
%type <varlist> VarList
%type <var> ParamDec

/* Statements */
%type <stmt> Stmt CompSt
%type <stmtlist> StmtList

/* Local Definitions */
%type <varlist> DecList Def DefList
%type <var> Dec

/* Expressions */
%type <expr> Exp
%type <arglist> Args

%%

// High level definitions

Program : 
      ExtDefList                        {  }
    ;

ExtDefList : 
      ExtDef ExtDefList                 {  }
    | %empty                            { }
    ;

ExtDef : 
      Specifier ExtDecList ';'          {  }
    | Specifier ';'                     {  }
    | Specifier FunDec CompSt           {  }
    | error                             {  }
    ;

ExtDecList :
      VarDec                            {  }
    | VarDec ',' ExtDecList             { }
    ;

// Specifiers

Specifier : 
      TYPE                              {
            $$ = Type_Basic_Constructor($TYPE);
        }
    | StructSpecifier                   {
            $$ = $StructSpecifier;
        }
    ;

StructSpecifier : 
      STRUCT OptTag                     {
            $<type>$ = Type_Struct_Constructor(OptTag);
            symtbl_push_scope(true);
        } [structdef]
      '{' DefList '}'                   {
            $$ = $<type>structdef;
            $$->varlist = $DefList;
            $$->symtable = symtbl_scope->variables;
            symtbl_pop_scope();
            // TODO: insert to symtbl if tag is not empty
        }
    | STRUCT Tag                        {
            $$ = symtbl_struct_find(Tag);
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
            $$.var = Variable_Constructor($ID, NULL);
            $$.underlying = &$$.var->valtype;
        }
    | VarDec '[' INT ']'                {
            $$.var = $1.var;
            $$.underlying =  &(
                *($1.underlying) = Type_Array_Constructor($INT, NULL)
            )->underlying;
        }
    ;

FunDec : 
      ID '(' VarList ')'                {
            $$ = Function_Constructor($ID, yylloc, NULL, VarList, NULL);
        }
    ;

VarList : 
      ParamDec ',' VarList[old]         {
            $$ = $old;
            list_prepend(&$$, $ParamDec);
        }
    | ParamDec                          {
            $$ = NULL;
            list_prepend(&$$, $ParamDec);
        }
    | %empty                    {
            $$ = NULL;
        }
    ;

ParamDec : 
      Specifier VarDec                  {
            $$ = $VarDec.var;
            *($VarDec.underlying) = $Specifier;
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
            $$ = NULL;  /* TODO: better error handling */
        }
    | CompSt                            { 
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
            $$ = $old;
            list_prepend(&$$, $Def);
        }
    | %empty                            {
            $$ = NULL;
        }
    ;

Def : 
      Specifier                {
            Specifier_Type = $Specifier;
        }
      DecList ';'                       {
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
            *($VarDec->underlying) = Specifier_Type;
        }
    | VarDec '=' Exp                    {
            $$ = $VarDec.var;
            *($VarDec->underlying) = Specifier_Type;
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
            $$ = Literal_Expression_int_Constructor(yylloc, $INT);
        }
    | FLOAT                             { 
            $$ = Literal_Expression_float_Constructor(yylloc, $FLOAT);
        }
    ;

Args : // left recurision eases array list construction
      Exp ',' Args[old]                 {
            $$ = $old;
            list_prepend(&$$, $Exp);
        }
    | Exp                               {
            $$ = NULL;
            list_prepend(&$$, $Exp);
        }
    | %empty                    {
            $$ = NULL;
        }
    ;

%%

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, yylloc, msg);
}

