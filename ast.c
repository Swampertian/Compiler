#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

static ASTNode *ast_alloc(ASTNodeType kind);
static void ast_print_node(const ASTNode *node, int depth);
static void ast_indent(int depth);

static ASTNode *ast_alloc(ASTNodeType kind) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    if (node == NULL) {
        fprintf(stderr, "Erro interno: falha ao alocar no da AST\n");
        exit(EXIT_FAILURE);
    }

    node->kind = kind;
    return node;
}

ASTNode *ast_create_program(ASTNode *comandos) {
    ASTNode *node = ast_alloc(AST_PROGRAMA);
    node->left = comandos;
    return node;
}

ASTNode *ast_create_declaration(TipoDado tipo, char *identificador, ASTNode *expressao) {
    ASTNode *node = ast_alloc(AST_DECLARACAO);
    node->tipo = tipo;
    node->texto = identificador;
    node->left = expressao;
    return node;
}

ASTNode *ast_create_binary(char operador, ASTNode *left, ASTNode *right) {
    ASTNode *node = ast_alloc(AST_BINARIO);
    node->operador = operador;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *ast_create_identifier(char *nome) {
    ASTNode *node = ast_alloc(AST_IDENTIFICADOR);
    node->texto = nome;
    return node;
}

ASTNode *ast_create_number(char *literal) {
    ASTNode *node = ast_alloc(AST_NUMERO);
    node->texto = literal;
    node->tipo = literal_para_tipo(literal);
    return node;
}

ASTNode *ast_append_command(ASTNode *lista, ASTNode *comando) {
    ASTNode *cursor = lista;

    if (lista == NULL) {
        return comando;
    }

    while (cursor->next != NULL) {
        cursor = cursor->next;
    }

    cursor->next = comando;
    return lista;
}

void ast_print(const ASTNode *node) {
    ast_print_node(node, 0);
}

static void ast_print_node(const ASTNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    ast_indent(depth);

    switch (node->kind) {
        case AST_PROGRAMA:
            printf("Programa\n");
            ast_print_node(node->left, depth + 1);
            break;
        case AST_DECLARACAO:
            printf("Chave %s : %s\n", node->texto, tipo_para_string(node->tipo));
            ast_print_node(node->left, depth + 1);
            break;
        case AST_BINARIO:
            printf("Operador: '%c'\n", node->operador);
            ast_print_node(node->left, depth + 1);
            ast_print_node(node->right, depth + 1);
            break;
        case AST_IDENTIFICADOR:
            printf("Identificador %s\n", node->texto);
            break;
        case AST_NUMERO:
            printf("Valor: %s : %s\n", node->texto, tipo_para_string(node->tipo));
            break;
    }

    if (depth > 0 && node->next != NULL) {
        ast_print_node(node->next, depth);
    }
}

static void ast_indent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
}

void ast_free(ASTNode *node) {
    if (node == NULL) {
        return;
    }
    ast_free(node->left);
    ast_free(node->right);
    ast_free(node->next);
    free(node->texto);
    free(node);
}
