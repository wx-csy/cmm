%{

#include <stdio.h>
#include "cmm.h"
#include "error.h"
#include "cst.h"

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
%}
h
%union {
    struct Expression *expr;    
    struct Statement *stmt;
    ArgList arglist;
    Literal lit;
}

%define parse.error verbose
%start  Program
%token  INT FLOAT ID TYPE
%token  IF WHILE RETURN STRUCT 

%right      '='
%left       AND OR
%left       RELOP
%left       '+' '-'
%left       '*' '/'
%right      '!' UMINUS
%left       '.' '[' ']' '(' ')'

%nonassoc   LOWER_THAN_ELSE
%nonassoc   ELSE

%%

// High level definitions

Program : 
      ExtDefList                        { cst = $1; $$ = NULL; }
    ;

ExtDefList : 
      ExtDef ExtDefList                 { BUILD_CST_NODE2($$, $1, $2, "ExtDefList"); }
    | %empty                            { BUILD_CST_NODE0($$, "ExtDefList"); }
    ;

ExtDef : 
      Specifier ExtDecList ';'          { BUILD_CST_NODE3($$, $1, $2, $3, "ExtDef"); }
    | Specifier ';'                     { BUILD_CST_NODE2($$, $1, $2, "ExtDef"); }
    | Specifier FunDec CompSt           { BUILD_CST_NODE3($$, $1, $2, $3, "ExtDef"); }
    | error                             { BUILD_CST_NODE0($$, "ExtDef (Error)"); }
    ;

ExtDecList : 
      VarDec                            { BUILD_CST_NODE1($$, $1, "ExtDecList"); }
    | VarDec ',' ExtDecList             { BUILD_CST_NODE3($$, $1, $2, $3, "ExtDecList"); }
    ;

// Specifiers

Specifier : 
      TYPE                              { BUILD_CST_NODE1($$, $1, "Specifier"); }
    | StructSpecifier                   { BUILD_CST_NODE1($$, $1, "Specifier"); }
    ;

StructSpecifier : 
      STRUCT OptTag '{' DefList '}'     { BUILD_CST_NODE5($$, $1, $2, $3, $4, $5, "StructSpecifier"); }
    | STRUCT Tag                        { BUILD_CST_NODE2($$, $1, $2, "StructSpecifier"); }
    ;

OptTag : 
      ID                                { BUILD_CST_NODE1($$, $1, "OptTag"); }
    | %empty                            { BUILD_CST_NODE0($$, "OptTag"); }
    ;

Tag :                                   
      ID                                { BUILD_CST_NODE1($$, $1, "Tag"); }
    ;

// Declarators

VarDec : 
      ID                                { BUILD_CST_NODE1($$, $1, "VarDec"); }
    | VarDec '[' INT ']'                { BUILD_CST_NODE4($$, $1, $2, $3, $4, "VarDec"); }
    ;

FunDec : 
      ID '(' VarList ')'                { BUILD_CST_NODE4($$, $1, $2, $3, $4, "FunDec"); }
    | ID '(' ')'                        { BUILD_CST_NODE3($$, $1, $2, $3, "FunDec"); }
    ;

VarList : 
      ParamDec ',' VarList              { BUILD_CST_NODE3($$, $1, $2, $3, "VarList"); }
    | ParamDec                          { BUILD_CST_NODE1($$, $1, "VarList"); }
    ;

ParamDec : 
      Specifier VarDec                  { BUILD_CST_NODE2($$, $1, $2, "ParamDec"); }
    ;

// Statements

CompSt : 
      '{' DefList StmtList '}'          { 
          $$ = Statement_Compound_Constructor(yylloc, $DefList, $StmtList);
        }
    ;

StmtList :                              
      Stmt StmtList                     { 
            $$ = $StmtList;
            array_append($$.stmts, $$.nr_stmt, $Stmt);
        }
    | %empty                            { 
            memset($$, 0, sizeof(*$$))
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
    | IF '(' Exp ')' Stmt %prec LOWER_THAN_ELSE     { 
            $$ = Statement_IfThen_Constructor(yylloc, $Exp, $Stmt);
        }
    | IF '(' Exp ')' Stmt[s1] ELSE Stmt[s2]         { 
            $$ = Statement_IfThenElse_Constructor(yylloc, $Exp, $s1, $s2);
        }
    | WHILE '(' Exp ')' Stmt            { 
            $$ = Statement_While_Constructor(yylloc, $Exp, $Stmt);
        }
    ;

// Local Definitions

DefList : 
      Def DefList                       { BUILD_CST_NODE2($$, $1, $2, "DefList"); }
    | %empty                            { BUILD_CST_NODE0($$, "DefList"); }
    ;

Def : 
      Specifier DecList ';'             { BUILD_CST_NODE3($$, $1, $2, $3, "Def"); }
    ;

DecList : 
      Dec                               { BUILD_CST_NODE1($$, $1, "DecList"); }
    | Dec ',' DecList                   { BUILD_CST_NODE3($$, $1, $2, $3, "DecList"); }
    ;

Dec : 
      VarDec                            { BUILD_CST_NODE1($$, $1, "Dec"); }
    | VarDec '=' Exp                    { BUILD_CST_NODE3($$, $1, $2, $3, "Dec"); }
    ;

// Expressions

Exp :
      Exp '=' Exp                       {
            $$ = Expression_Assign_Constructor(yylloc, $1, $3);
        }
    | Exp AND Exp                       {
            $$ = Expression_Binary_Constructor(EXPR_BINARY_AND, yylloc, $1, $3);
        }
    | Exp OR Exp                        {
            $$ = Expression_Binary_Constructor(EXPR_BINARY_OR, yylloc, $1, $3);
        }
    | Exp RELOP Exp                     {
            $$ = Expression_Binary_Constructor($2, yylloc, $1, $3);
        }
    | Exp '+' Exp                       {
            $$ = Expression_Binary_Constructor(EXPR_BINARY_ADD, yylloc, $1, $3);
        }
    | Exp '-' Exp                       {
            $$ = Expression_Binary_Constructor(EXPR_BINARY_MINUS, yylloc, $1, $3);
        }
    | Exp '*' Exp                       {
            $$ = Expression_Binary_Constructor(EXPR_BINARY_STAR, yylloc, $1, $3);
        }
    | Exp '/' Exp                       { 
            $$ = Expression_Binary_Constructor(EXPR_BINARY_DIV, yylloc, $1, $3);
        }
    | '(' Exp ')'                       { 
            $$ = $Exp;
        }
    | '-' Exp   %prec UMINUS            { 
            $$ = Expression_Unary_Constructor(EXPR_UNARY_NEGATE, yylloc, $Exp);
        }
    | '!' Exp   %prec UMINUS            { 
            $$ = Expression_Unary_Constructor(EXPR_UNARY_NOT, yylloc, $Exp);
        }
    | ID '(' Args ')'                   { 
            /* TODO: symtbl lookup */
        }
    | ID '(' ')'                        { 
            /* TODO: symtbl lookup */
        }
    | Exp '[' Exp ']'                   { 
            $$ = Expression_ArrayAccess_Constructor(yylloc, $1, $3);
        }
    | Exp '.' ID                        { 
            /* TODO: symtbl lookup */
        }
    | ID                                { 
            /* TODO: symtbl lookup */
        }
    | INT                               { 
            $$ = Literal_Expression_Constructor(yylloc, $FLOAT);
        }
    | FLOAT                             { 
            $$ = Literal_Expression_Constructor(yylloc, $FLOAT);
        }
    ;

Args : 
      Exp ',' Args                      { 
            $$ = $Args;
            array_append($$.args, $$.nr_arg, $Exp);
        }
    | Exp                               { 
            memset($$, 0, sizeof(*$$));
            array_append($$.args, $$.nr_arg, $Exp);
        }
    ;

%%

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, yylloc, msg);
}

