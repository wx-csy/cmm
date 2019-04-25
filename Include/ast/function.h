#ifndef __AST_FUNCTION_H__
#define __AST_FUNCTION_H__

#include "ast/ast.h"
#include "location.h"

typedef struct Function {
    const char *name;
    cmm_loc_t location;
    Type *rettype;
    VarList paramlist;
    Statement *stmt;
} Function;

Function *Function_Constructor(const char *name, cmm_loc_t location,
    Type *rettype, VarList paramlist, Statement *stmt);
#endif
