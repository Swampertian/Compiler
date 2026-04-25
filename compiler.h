#ifndef COMPILER_H
#define COMPILER_H

typedef enum {
    TIPO_INT = 0,
    TIPO_FLOAT = 1
} TipoDado;

const char *tipo_para_string(TipoDado tipo);
TipoDado keyword_para_tipo(const char *keyword);
TipoDado literal_para_tipo(const char *literal);

#endif
