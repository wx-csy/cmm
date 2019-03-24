%{

#include <stdio.h>
#include "cmm.h"
#include "error.h"
#include "cst.h"

void yyerror(const char*);

#define BUILD_CST_NODE0($$, ...) { \
        $$ = NULL; \
    }

#define BUILD_CST_NODE1($$, $1, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 1, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
    }

#define BUILD_CST_NODE2($$, $1, $2, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 2, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
    }

#define BUILD_CST_NODE3($$, $1, $2, $3, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 3, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
    }
    
#define BUILD_CST_NODE4($$, $1, $2, $3, $4, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 4, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
    }

#define BUILD_CST_NODE5($$, $1, $2, $3, $4, $5, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 5, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
    }
    
#define BUILD_CST_NODE6($$, $1, $2, $3, $4, $5, $6, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 6, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
        $$->child[5] = $6; \
    }
    
#define BUILD_CST_NODE7($$, $1, $2, $3, $4, $5, $6, $7, fmt, ...) { \
        $$ = cst_node_ctor(yylloc, 7, fmt " (%d)", ##__VA_ARGS__, \
            yylloc.line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
        $$->child[5] = $6; \
        $$->child[6] = $7; \
    }

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

%define api.value.type {cst_node_t *}
%define parse.error verbose
%destructor { cst_node_dtor($$); } <>
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
      '{' DefList StmtList '}'          { BUILD_CST_NODE4($$, $1, $2, $3, $4, "CompSt"); }
    ;

StmtList :                              
      Stmt StmtList                     { BUILD_CST_NODE2($$, $1, $2, "StmtList"); }
    | %empty                            { BUILD_CST_NODE0($$, "StmtList"); }
    ;

Stmt : 
      Exp ';'                           { BUILD_CST_NODE2($$, $1, $2, "Stmt"); }
    | error ';'                         { BUILD_CST_NODE1($$, $2, "Stmt (Error)"); }
    | CompSt                            { BUILD_CST_NODE1($$, $1, "Stmt"); }
    | RETURN Exp ';'                    { BUILD_CST_NODE3($$, $1, $2, $3, "Stmt"); }
    | IF '(' Exp ')' Stmt %prec LOWER_THAN_ELSE
                                        { BUILD_CST_NODE5($$, $1, $2, $3, $4, $5, "Stmt"); }
    | IF '(' Exp ')' Stmt ELSE Stmt     { BUILD_CST_NODE7($$, $1, $2, $3, $4, $5, $6, $7, "Stmt"); }
    | WHILE '(' Exp ')' Stmt            { BUILD_CST_NODE5($$, $1, $2, $3, $4, $5, "Stmt"); }
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
      Exp '=' Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp AND Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp OR Exp                        { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp RELOP Exp                     { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp '+' Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp '-' Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp '*' Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp '/' Exp                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | '(' Exp ')'                       { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | '-' Exp   %prec UMINUS            { BUILD_CST_NODE2($$, $1, $2, "Exp"); }
    | '!' Exp   %prec UMINUS            { BUILD_CST_NODE2($$, $1, $2, "Exp"); }
    | ID '(' Args ')'                   { BUILD_CST_NODE4($$, $1, $2, $3, $4, "Exp"); }
    | ID '(' ')'                        { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | Exp '[' Exp ']'                   { BUILD_CST_NODE4($$, $1, $2, $3, $4, "Exp"); }
    | Exp '.' ID                        { BUILD_CST_NODE3($$, $1, $2, $3, "Exp"); }
    | ID                                { BUILD_CST_NODE1($$, $1, "Exp"); }
    | INT                               { BUILD_CST_NODE1($$, $1, "Exp"); }
    | FLOAT                             { BUILD_CST_NODE1($$, $1, "Exp"); }
    ;

Args : 
      Exp ',' Args                      { BUILD_CST_NODE3($$, $1, $2, $3, "Args"); }
    | Exp                               { BUILD_CST_NODE1($$, $1, "Args"); }
    ;

%%

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, yylloc, msg);
}

