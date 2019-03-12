%{
#include <stdio.h>
%}

%token  INT FLOAT ID TYPE
%token  IF WHILE ELSE RETURN STRUCT 
%token  RELOP AND OR 

%%

// High level definitions

Program     : ExtDefList
            ;

ExtDefList  : ExtDef ExtDefList 
            |
            ;

ExtDef      : Specifier ExtDecList ';'
            | Specifier ';'
            | Specifier FunDec CompSt
            ;

ExtDecList  : VarDec
            | VarDec ',' ExtDecList
            ;

// Specifiers

Specifier   : TYPE
            | StructSpecifier 
            ;

StructSpecifier : STRUCT OptTag '{' DefList '}'
                | STRUCT Tag
                ;

OptTag      : ID 
            |
            ;

Tag         : ID
            ;

// Declarators

VarDec      : ID
            | VarDec '[' INT ']'
            ;

FunDec      : ID '(' VarList ')'
            | ID '(' ')'
            ;

VarList     : ParamDec ',' VarList
            | ParamDec
            ;

ParamDec    : Specifier VarDec
            ;

// Statements

CompSt      : '{' DefList StmtList '}'
            ;

StmtList    : Stmt StmtList
            |
            ;

Stmt        : Exp ';'
            | CompSt
            | RETURN Exp ';'
            | IF '(' Exp ')' Stmt
            | IF '(' Exp ')' Stmt ELSE Stmt
            | WHILE '(' Exp ')' Stmt
            ;

// Local Definitions

DefList     : Def DefList
            |
            ;

Def         : Specifier DecList ';'
            ;

DecList     : Dec
            | Dec ',' DecList
            ;

Dec         : VarDec
            | VarDec '=' Exp
            ;

// Expressions

Exp         : Exp '=' Exp
            | Exp AND Exp
            | Exp OR Exp
            | Exp RELOP Exp
            | Exp '+' Exp
            | Exp '-' Exp
            | Exp '*' Exp
            | Exp '/' Exp
            | '(' Exp ')'
            | '-' Exp
            | '!' Exp
            | ID '(' Args ')'
            | ID '(' ')'
            | Exp '(' Exp ')'
            | Exp '.' ID
            | ID
            | INT
            | FLOAT
            ;

Args        : Exp ',' Args
            | Exp
            ;

%%

#include "lexical.yy.c"

int main() {
    yyparse();
}

void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}

