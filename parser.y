%{
#include "ast.h"
#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

static ASTNode *ast_root = NULL;
%}

%code requires {
#include "ast.h"
}

%union {
    char *str;
    char op;
    TipoDado tipo;
    ASTNode *node;
}

%token FIM 0 "fim da entrada"
%token SOMA MENOS DELIMITADOR ATRIB
%token <str> ID NUMERO KEY

%type <node> programa lista_comandos comando declaracao expressao termo
%type <tipo> tipo chave
%type <op> sinal

%destructor { free($$); } <str>

%%

programa:
    lista_comandos FIM {
        ast_root = ast_create_program($1);
        $$ = ast_root;
    }
    ;

lista_comandos:
    %empty { $$ = NULL; }
    | lista_comandos comando { $$ = ast_append_command($1, $2); }
    ;

comando:
    declaracao delimitador { $$ = $1; }
    ;

declaracao:
    tipo ID atrib expressao {
        $$ = ast_create_declaration($1, $2, $4);
    }
    ;

expressao:
    termo { $$ = $1; }
    | expressao sinal termo {
        $$ = ast_create_binary($2, $1, $3);
    }
    ;

termo:
    ID { $$ = ast_create_identifier($1); }
    | NUMERO { $$ = ast_create_number($1); }
    ;

tipo:
    chave { $$ = $1; }
    ;

sinal:
    SOMA { $$ = '+'; }
    | MENOS { $$ = '-'; }
    ;

chave:
    KEY {
        $$ = keyword_para_tipo($1);
        free($1);
    }
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
    SymbolTable table;
    int ok;

    if (yyparse() != 0) {
        ast_free(ast_root);
        return EXIT_FAILURE;
    }

    symbol_table_init(&table);
    ok = semantic_analyze_program(ast_root, &table);

    if (ok) {
        printf("Programa valido sintatica e semanticamente\n");
        printf("AST:\n");
        ast_print(ast_root);
        symbol_table_print(&table);
    }

    symbol_table_free(&table);
    ast_free(ast_root);
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
