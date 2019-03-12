%{
    #include "syntax.tab.h"
%}

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

%%

[ \t\n]+            /* eat up whitespace */

{integer}           return INT;

{float}             return FLOAT;

int|float           return TYPE;

struct              return STRUCT;

return              return RETURN;

if                  return IF;

else                return ELSE;

while               return WHILE;

.                   return yytext[0];

%%

int yywrap() { return 1; }
