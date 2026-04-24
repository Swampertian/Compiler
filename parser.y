%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

%token FIM 0 "fim da entrada"
%token ID NUMERO SOMA MENOS KEY DELIMITADOR ATRIB

%%

programa:
    expressao_algebrica FIM { printf("Expressao valida sintaticamente\n"); }
    ;

expressao_algebrica:
    chave termo atrib termo sinal termo delimitador
    ;

sinal:
    SOMA
    | MENOS
    ;

termo:
    ID
    | NUMERO
    ;

chave:
    KEY
    ;

delimitador:
    DELIMITADOR
    ;

atrib:
    ATRIB
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintatico: %s\n", s);
}

int main(void) {
    return yyparse();
}
