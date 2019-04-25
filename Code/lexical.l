%{

#include <stdint.h>
#include <stdlib.h>
#include "cmm.h"
#include "error.h"
#include "syntax.tab.h"

union YYSTYPE yylval;
cmm_loc_t yylloc = CMM_LOC_INITIALIZER;
static cmm_loc_t prev_loc = CMM_LOC_INITIALIZER;

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
    yylloc = prev_loc;                                      \
    for (int i = 0; yytext[i] != '\0'; i++) {               \
        if (yytext[i] == '\n') {                            \
            prev_loc.line++; prev_loc.col = 1;              \
        } else {                                            \
            prev_loc.col++;                                 \
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
                        cmm_error(CMM_ERROR_UNTERMCOMM, yylloc); 
                        return 0; 
                    }

"//"                { BEGIN(CPP_COMMENT); }

<CPP_COMMENT>\n     { BEGIN(INITIAL); }

<CPP_COMMENT><<EOF>>    { BEGIN(INITIAL); return 0; }

<CPP_COMMENT>.      /* eat up cpp-comment */

{ppnumber}          {
                        char *endptr;
                        
                        errno = 0;                        
                        if (yytext[0] == '0' && yytext[1] == 'x') {
                            /* hexadecimal number literal */
                            unsigned long value = strtol(yytext, &endptr, 16);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVHEXLIT, yylloc, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF, yylloc, yytext);
                            }
                            yylval.int_val = value;
                            return INT;

                        } if (strchr(yytext, '.') || strchr(yytext, 'e') ||
                            strchr(yytext, 'E')) {
                            /* floating-point number literal */
                            double value = strtod(yytext, &endptr);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVFPLIT, yylloc, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_FPLIT_OF, yylloc, yytext);
                            }
                            yylval.float_val = value;
                            return FLOAT;
                                
                        } else if (yytext[0] == '0') {
                            /* octal number literal */
                            unsigned long value = strtol(yytext, &endptr, 8);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVOCTLIT, yylloc, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF, yylloc, yytext);
                            }
                            yylval.int_val = value;
                            return INT;

                        } else {
                            /* decimal number literal */
                            unsigned long value = strtol(yytext, &endptr, 10);
                            if (*endptr != '\0') {
                                cmm_error(CMM_ERROR_INVDECLIT, yylloc, yytext);
                            } else if (errno == ERANGE) {
                                cmm_error(CMM_ERROR_INTLIT_OF, yylloc, yytext);
                            }
                            yylval.int_val = value;
                            return INT;

                        }
                    }

int                 {
                        yylval.basictype = BT_INT;
                        return TYPE;
                    }

float               {
                        yylval.basictype = BT_FLOAT;
                        return TYPE;
                    }

struct              {
                        return STRUCT;
                    }

if                  {
                        return IF;
                    }

else                {
                        return ELSE;
                    }

while               {
                        return WHILE;
                    }

return              {
                        return RETURN;
                    }

{relop}             {
                        if (strcmp(yytext, ">") == 0) {
                            yylval.binaryop = BOP_GT;
                        } else if (strcmp(yytext, "<") == 0) {
                            yylval.binaryop = BOP_LT;
                        } else if (strcmp(yytext, ">=") == 0) {
                            yylval.binaryop = BOP_GE;
                        } else if (strcmp(yytext, "<=") == 0) {
                            yylval.binaryop = BOP_LE;
                        } else if (strcmp(yytext, "==") == 0) {
                            yylval.binaryop = BOP_EQU;
                        } else if (strcmp(yytext, "!=") == 0) {
                            yylval.binaryop = BOP_NEQ;
                        }
                        return RELOP;
                    }

{identifier}        {
                        yylval.name = yytext;
                        return ID;
                    }

&&                  {
                        return AND;
                    }

\|\|                {
                        return OR;
                    }

[(){};!=.,]         {
                        return yytext[0];
                    }

[-+/*]              {
                        return yytext[0];
                    }

\[|\]               {
                        return yytext[0];
                    }

.                   { 
                        cmm_error(CMM_ERROR_MYSCHAR, yylloc, yytext); 
                    }
                
%%

int yywrap() { return 1; }

