#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

typedef struct {
    char *nome;
    TipoDado tipo;
} Simbolo;

typedef struct {
    Simbolo *simbolos;
    int total;
    int capacidade;
} SymbolTable;

void symbol_table_init(SymbolTable *table);
void symbol_table_free(SymbolTable *table);
void symbol_table_print(const SymbolTable *table);
int semantic_analyze_program(const ASTNode *program, SymbolTable *table);

#endif
