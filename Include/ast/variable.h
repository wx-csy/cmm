#ifndef __AST_VARIABLE_H__
#define __AST_VARIABLE_H__

#include "ast/ast.h"

typedef struct Variable {
    const char *name;
    Type *valtype;
    Expression *initializer; // nullable
} Variable;

Variable *Variable_Constructor(const char *name, Type *valtype);


#endif
