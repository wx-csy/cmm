#ifndef __AST_FUNCTION_H__
#define __AST_FUNCTION_H__

#include "ast/ast.h"
#include "location.h"

typedef struct ParamList {
    size_t nr_param;
    Variable **params;
} ParamList;

typedef struct Function {
    const char *name;
    cmm_loc_t location;
    ParamList paramlist;
    Statement *stmt;
} function;

#endif