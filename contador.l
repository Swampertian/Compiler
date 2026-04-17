%{ 
#include <stdio.h>
%}

%%
[struct]* { printf("<key,%s>",yytext); } 
[int]* { printf("<key,%s>",yytext); }
[float]* { printf("<key,%s>",yytext); }
[char]* { printf("<key,%s>",yytext); }
[void]* { printf("<key,%s>",yytext); }
[typeof]* { printf("<key,%s>",yytext); }
[if]* { printf("<key,%s>",yytext); }
[else]* { printf("<key,%s>",yytext); }
[while]* { printf("<key,%s>",yytext); }
[do]* { printf("<key,%s>",yytext); }
[0-9]+ { printf("<id,%s>",yytext); }
[a-zA-Z]+ { printf("<id,%s>",yytext); }
";" { printf("<del>"); }
"+" { printf("<op,+>"); }
"-" { printf("<op,-"); } 
"*" { printf("<op,*>"); }
"/" { printf("<op,/>"); }
"(" { printf("<ex>"); }
")" { printf("<ex>"); }
%%

int main () {
	yylex();
	return 0;
}

int yywrap() { return 1; }

