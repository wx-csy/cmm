#ifndef __AST_VARIABLE_H__
#define __AST_VARIABLE_H__

#include "ast/ast.h"

typedef struct Variable {
    const char *name;
    Type *vartype;
    size_t rank;
    size_t *extent;
} function;

#endif
