#ifndef __AST_VARIABLE_H__
#define __AST_VARIABLE_H__

#include "ast/ast.h"
#include "location.h"

typedef struct Variable {
    const char *name;
    cmm_loc_t location;
    Type *valtype;
    size_t offset;
    Expression *initializer; // nullable
} Variable;

Variable *Variable_Constructor(cmm_loc_t location, const char *name);

#endif
