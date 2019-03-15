%{

#include <stdint.h>
#include <stdlib.h>
#include <cmm/error.h>
#include <syntax/cst.h>
#include <syntax/syntax.tab.h>

cst_node_t *yylval;

#define UCHAR(ch) ((uint8_t)(ch))
static const char *const token_name[256] = {
    [UCHAR(';')] = "SEMI",
    [UCHAR(',')] = "COMMA",
    [UCHAR('=')] = "ASSIGNOP",
    [UCHAR('+')] = "PLUS",
    [UCHAR('-')] = "MINUS",
    [UCHAR('*')] = "STAR",
    [UCHAR('/')] = "DIV",
    [UCHAR('.')] = "DOT",
    [UCHAR('!')] = "NOT",
    [UCHAR('(')] = "LP",
    [UCHAR(')')] = "RP",
    [UCHAR('[')] = "LB",
    [UCHAR(']')] = "RB",
    [UCHAR('{')] = "LC",
    [UCHAR('}')] = "RC",
};

%}

%option yylineno

digit               [0-9]
nonzerodigit        [1-9]
octdigit            [0-7]
hexdigit            [0-9a-fA-F]
decimalinteger      {nonzerodigit}{digit}*|0
octinteger          0{octdigit}+
hexinteger          0(x|X){hexdigit}+
integer             {decimalinteger}|{octinteger}|{hexinteger}

intpart             {digit}+
fraction            \.{digit}+
exponent            (e|E)[+-]?{digit}+
pointfloat          {intpart}?{fraction}|{intpart}\.
exponentfloat       ({intpart}|{pointfloat}){exponent}
float               {pointfloat}|{exponentfloat}

keyword             int|float|struct|return|if|else|while

relop               >|<|>=|<=|==|!=
and                 &&
or                  \|\|

identifier          [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n]+            /* eat up whitespace */

{integer}           {
                        yylval = cst_node_ctor(yylineno, 0, "INT: %d", 
                            atoi(yytext));
                        return INT;
                    }

{float}             {
                        yylval = cst_node_ctor(yylineno, 0, "FLOAT: %.6f", 
                            atof(yytext));
                        return FLOAT;
                    }

int|float           {
                        yylval = cst_node_ctor(yylineno, 0, "TYPE: %s", yytext);
                        return TYPE;
}

struct              {
                        yylval = cst_node_ctor(yylineno, 0, "STRUCT");
                        return STRUCT;
                    }

if                  {
                        yylval = cst_node_ctor(yylineno, 0, "IF");
                        return IF;
                    }

else                {
                        yylval = cst_node_ctor(yylineno, 0, "ELSE");
                        return ELSE;
                    }

while               {
                        yylval = cst_node_ctor(yylineno, 0, "WHILE");
                        return WHILE;
                    }

return              {
                        yylval = cst_node_ctor(yylineno, 0, "RETURN");
                        return RETURN;
                    }

relop               {
                        yylval = cst_node_ctor(yylineno, 0, "RELOP");
                        return RELOP;
                    }

{identifier}        {
                        yylval = cst_node_ctor(yylineno, 0, "ID: %s", yytext);
                        return ID;
                    }

&&                  {
                        yylval = cst_node_ctor(yylineno, 0, "AND");
                        return AND;
                    }

\|\|                {
                        yylval = cst_node_ctor(yylineno, 0, "OR", yytext);
                        return OR;
                    }

[(){};!=.,]         {
                        yylval = cst_node_ctor(yylineno, 0, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

[-+/*]              {
                        yylval = cst_node_ctor(yylineno, 0, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

\[|\]               {
                        yylval = cst_node_ctor(yylineno, 0, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

.                   { cmm_error(1, yylineno, 0, yytext); }
                
%%

int yywrap() { return 1; }

