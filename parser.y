%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
%}


%token INT FLOAT IF ELSE WHILE
%token ID NUMERO
%token DELIM SOMA MENOS MULT DIV ATRIB
%token LPARENTESES RPARENTESES

%%


programa:
    declaracao
    | atribuicao
    ;

declaracao:
    tipo ID DELIM { printf("\n declaração faz sentido sintaticamente\n"); }
    ;

tipo:
    INT 
    | FLOAT
    ;

atribuicao:
    ID ATRIB expressao DELIM { printf("\Atribuição válida sintaticamente\n"); }
    ;

expressao:
    ID operacao ID
    | NUMERO operacao NUMERO
    | ID
    | NUMERO
    ;

operacao:
    SOMA | MENOS | MULT | DIV
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "\n[Erro Sintático] %s\n", s);
}

int main() {
    printf("Digite o código para análise:\n");
    yyparse();
    return 0;
}
