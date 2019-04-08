#ifndef __AST_FUNCTION_H__
#define __AST_FUNCTION_H__

#include "ast/ast.h"
#include "location.h"

typedef struct Function {
    const char *name;
    cmm_loc_t location;
    struct VarList paramlist;
    Statement *stmt;
} function;

#endif