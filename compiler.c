#include "compiler.h"

#include <stdlib.h>
#include <string.h>

const char *tipo_para_string(TipoDado tipo) {
    return tipo == TIPO_FLOAT ? "float" : "int";
}

TipoDado keyword_para_tipo(const char *keyword) {
    if (strcmp(keyword, "int") == 0) {
        return TIPO_INT;
    }

    if (strcmp(keyword, "float") == 0) {
        return TIPO_FLOAT;
    }

    return TIPO_INT;
}

TipoDado literal_para_tipo(const char *literal) {
    return strchr(literal, '.') != NULL ? TIPO_FLOAT : TIPO_INT;
}
