%{
#include "parser.tab.h"
%}

%%


[int]*                  { return KEY; }
[float]*                { return KEY; }

[0-9]+                  { return NUMERO; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
"+"                     { return SOMA; }
"-"                     { return MENOS; }
"="                     { return ATRIB; }
";"                     { return DELIMITADOR; }
[ \t\r\n]+              { /* Ignore whitespace. */ }
.                       { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
