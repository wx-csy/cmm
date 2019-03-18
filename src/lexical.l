%{

#include <stdint.h>
#include <stdlib.h>
#include "error.h"
#include "cst.h"
#include "syntax.tab.h"

cst_node_t *yylval;
static int lineno = 0, colno = 0, prev_lineno = 1, prev_colno = 1;

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

#define YY_USER_ACTION                                      \
    lineno = prev_lineno; colno = prev_colno;               \
    for (int i = 0; yytext[i] != '\0'; i++) {               \
        if (yytext[i] == '\n') {                            \
            prev_lineno++; prev_colno = 1;                  \
        } else {                                            \
            prev_colno++;                                   \
        }                                                   \
    }

%}

%option nounput noinput
%x C_COMMENT
%x CPP_COMMENT

digit               [0-9]

ppnumber            \.?{digit}([.0-9a-zA-Z_]|(e+)|(e-)|(E+)|(E-))*
relop               >|<|>=|<=|==|!=
identifier          [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n]+            /* eat up whitespace */

"/*"                { BEGIN(C_COMMENT); }

<C_COMMENT>"*/"     { BEGIN(INITIAL); }

<C_COMMENT>(.|\n)   /* eat up c-comment */

<C_COMMENT><<EOF>>  { 
                        cmm_error(CMM_ERROR_UNTERMCOMM, lineno, colno); 
                        return 0; 
                    }

"//"                { BEGIN(CPP_COMMENT); }

<CPP_COMMENT>\n     { BEGIN(INITIAL); }

<CPP_COMMENT><<EOF>>    { BEGIN(INITIAL); return 0; }

<CPP_COMMENT>.      /* eat up cpp-comment */

{ppnumber}          {
                        char *endptr;
                        if (strchr(yytext, '.') || strchr(yytext, 'e') ||
                            strchr(yytext, 'E')) {
                            /* floating-point number literal */
                            double value = strtod(yytext, &endptr);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVFPLIT, 
                                    lineno, colno, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_FPLIT_OF,
                                    lineno, colno, yytext);
                            }
                            yylval = cst_node_ctor(lineno, colno, 
                                "FLOAT: %.6f", value);
                            return FLOAT;
                        
                        } else if (yytext[0] == '0' && yytext[1] == 'x') {
                            /* hexadecimal number literal */
                            long value = strtol(yytext, &endptr, 16);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVHEXLIT, 
                                    lineno, colno, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF,
                                    lineno, colno, yytext);
                            }
                            yylval = cst_node_ctor(lineno, colno, 
                                "INT: %d", value);
                            return INT;
                            
                        } else if (yytext[0] == '0') {
                            /* octal number literal */
                            long value = strtol(yytext, &endptr, 8);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVOCTLIT, 
                                    lineno, colno, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF,
                                    lineno, colno, yytext);
                            }
                            yylval = cst_node_ctor(lineno, colno, 
                                "INT: %d", value);
                            return INT;

                        } else {
                            /* decimal number literal */
                            long value = strtol(yytext, &endptr, 10);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVDECLIT, 
                                    lineno, colno, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF,
                                    lineno, colno, yytext);
                            }
                            yylval = cst_node_ctor(lineno, colno, 
                                "INT: %d", value);
                            return INT;

                        }
                    }

int|float           {
                        yylval = cst_node_ctor(lineno, colno, "TYPE: %s", 
                            yytext);
                        return TYPE;
                    }

struct              {
                        yylval = cst_node_ctor(lineno, colno, "STRUCT");
                        return STRUCT;
                    }

if                  {
                        yylval = cst_node_ctor(lineno, colno, "IF");
                        return IF;
                    }

else                {
                        yylval = cst_node_ctor(lineno, colno, "ELSE");
                        return ELSE;
                    }

while               {
                        yylval = cst_node_ctor(lineno, colno, "WHILE");
                        return WHILE;
                    }

return              {
                        yylval = cst_node_ctor(lineno, colno, "RETURN");
                        return RETURN;
                    }

{relop}             {
                        yylval = cst_node_ctor(lineno, colno, "RELOP");
                        return RELOP;
                    }

{identifier}        {
                        yylval = cst_node_ctor(lineno, colno, 
                            "ID: %s", yytext);
                        return ID;
                    }

&&                  {
                        yylval = cst_node_ctor(lineno, colno, "AND");
                        return AND;
                    }

\|\|                {
                        yylval = cst_node_ctor(lineno, colno, "OR");
                        return OR;
                    }

[(){};!=.,]         {
                        yylval = cst_node_ctor(lineno, colno, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

[-+/*]              {
                        yylval = cst_node_ctor(lineno, colno, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

\[|\]               {
                        yylval = cst_node_ctor(lineno, colno, 
                            token_name[UCHAR(yytext[0])]);
                        return yytext[0];
                    }

.                   { 
                        cmm_error(CMM_ERROR_MYSCHAR, lineno, colno, 
                            yytext); 
                    }
                
%%

int yywrap() { return 1; }

