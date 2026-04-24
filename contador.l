%{
#include "parser.tab.h"
#include <string.h>
%}

%%


"int"                   { yylval.str = strdup(yytext); return KEY; }
"float"                 { yylval.str = strdup(yytext); return KEY; }

[0-9]+"."[0-9]+         { yylval.str = strdup(yytext); return NUMERO; }
[0-9]+                  { yylval.str = strdup(yytext); return NUMERO; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
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
