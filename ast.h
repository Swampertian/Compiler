#ifndef AST_H
#define AST_H

#include "compiler.h"

typedef enum {
    AST_PROGRAMA,
    AST_DECLARACAO,
    AST_BINARIO,
    AST_IDENTIFICADOR,
    AST_NUMERO
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType kind;
    TipoDado tipo;
    char operador;
    char *texto;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

ASTNode *ast_create_program(ASTNode *comandos);
ASTNode *ast_create_declaration(TipoDado tipo, char *identificador, ASTNode *expressao);
ASTNode *ast_create_binary(char operador, ASTNode *left, ASTNode *right);
ASTNode *ast_create_identifier(char *nome);
ASTNode *ast_create_number(char *literal);
ASTNode *ast_append_command(ASTNode *lista, ASTNode *comando);
void ast_print(const ASTNode *node);
void ast_free(ASTNode *node);

#endif
