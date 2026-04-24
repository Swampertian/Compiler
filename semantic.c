#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int symbol_table_find(const SymbolTable *table, const char *nome);
static int symbol_table_insert(SymbolTable *table, const char *nome, TipoDado tipo);
static int semantic_analyze_declaration(const ASTNode *node, SymbolTable *table);
static int semantic_infer_expression(const ASTNode *node, SymbolTable *table, TipoDado *result);

void symbol_table_init(SymbolTable *table) {
    table->capacidade = 16;
    table->total = 0;
    table->simbolos = calloc((size_t)table->capacidade, sizeof(Simbolo));
    if (table->simbolos == NULL) {
        fprintf(stderr, "Erro interno: falha ao alocar tabela de simbolos\n");
        exit(EXIT_FAILURE);
    }
}

void symbol_table_free(SymbolTable *table) {
    for (int i = 0; i < table->total; i++) {
        free(table->simbolos[i].nome);
    }

    free(table->simbolos);
    table->simbolos = NULL;
    table->total = 0;
    table->capacidade = 0;
}

void symbol_table_print(const SymbolTable *table) {
    printf("Tabela de simbolos:\n");
    for (int i = 0; i < table->total; i++) {
        printf("  %s : %s\n", table->simbolos[i].nome, tipo_para_string(table->simbolos[i].tipo));
    }
}

int semantic_analyze_program(const ASTNode *program, SymbolTable *table) {
    const ASTNode *comando;

    if (program == NULL || program->kind != AST_PROGRAMA) {
        fprintf(stderr, "Erro interno: raiz da AST invalida\n");
        return 0;
    }

    comando = program->left;
    while (comando != NULL) {
        if (!semantic_analyze_declaration(comando, table)) {
            return 0;
        }
        comando = comando->next;
    }

    return 1;
}

static int symbol_table_find(const SymbolTable *table, const char *nome) {
    for (int i = 0; i < table->total; i++) {
        if (strcmp(table->simbolos[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

static int symbol_table_insert(SymbolTable *table, const char *nome, TipoDado tipo) {
    Simbolo *simbolos_expandidos;

    if (symbol_table_find(table, nome) >= 0) {
        fprintf(stderr, "Erro semantico: identificador '%s' ja declarado\n", nome);
        return 0;
    }

    if (table->total == table->capacidade) {
        table->capacidade *= 2;
        simbolos_expandidos = realloc(table->simbolos, (size_t)table->capacidade * sizeof(Simbolo));
        if (simbolos_expandidos == NULL) {
            fprintf(stderr, "Erro interno: falha ao expandir tabela de simbolos\n");
            exit(EXIT_FAILURE);
        }
        table->simbolos = simbolos_expandidos;
    }

    table->simbolos[table->total].nome = strdup(nome);
    table->simbolos[table->total].tipo = tipo;
    table->total++;
    return 1;
}

static int semantic_analyze_declaration(const ASTNode *node, SymbolTable *table) {
    TipoDado tipo_expressao;

    if (node->kind != AST_DECLARACAO) {
        fprintf(stderr, "Erro interno: comando inesperado na AST\n");
        return 0;
    }

    if (!semantic_infer_expression(node->left, table, &tipo_expressao)) {
        return 0;
    }

    if (!symbol_table_insert(table, node->texto, node->tipo)) {
        return 0;
    }

    if (node->tipo == TIPO_INT && tipo_expressao == TIPO_FLOAT) {
        fprintf(
            stderr,
            "Erro semantico: atribuicao invalida para '%s' (%s <- %s)\n",
            node->texto,
            tipo_para_string(node->tipo),
            tipo_para_string(tipo_expressao)
        );
        return 0;
    }

    return 1;
}

static int semantic_infer_expression(const ASTNode *node, SymbolTable *table, TipoDado *result) {
    TipoDado tipo_esquerda;
    TipoDado tipo_direita;
    int indice;

    switch (node->kind) {
        case AST_NUMERO:
            *result = node->tipo;
            return 1;
        case AST_IDENTIFICADOR:
            indice = symbol_table_find(table, node->texto);
            if (indice < 0) {
                fprintf(stderr, "Erro semantico: identificador '%s' nao declarado\n", node->texto);
                return 0;
            }
            *result = table->simbolos[indice].tipo;
            return 1;
        case AST_BINARIO:
            if (!semantic_infer_expression(node->left, table, &tipo_esquerda)) {
                return 0;
            }
            if (!semantic_infer_expression(node->right, table, &tipo_direita)) {
                return 0;
            }
            *result = (tipo_esquerda == TIPO_FLOAT || tipo_direita == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
            return 1;
        default:
            fprintf(stderr, "Erro interno: expressao invalida na AST\n");
            return 0;
    }
}
