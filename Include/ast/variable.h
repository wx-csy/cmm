#ifndef __AST_VARIABLE_H__
#define __AST_VARIABLE_H__

#include "ast/ast.h"

enum VariableType {
    VAR_GLOBAL,
    VAR_ARGUMENT,
    VAR_LOCAL
};

typedef struct Variable {
    enum VariableType type;
    size_t offset;
    Type *valtype;
} Variable;

Variable *
Variable_Constructor(enum VariableType type, Type *valtype);

#endif
