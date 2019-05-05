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

    size_t ir_start_label;
} Function;

extern Function Function_Invalid;

Function *Function_Constructor(const char *name, cmm_loc_t location, Type *rettype);
bool Function_Declaration_Compatible(Function *func1, Function *func2);
void Function_IR_Generate_Code(Function *func);

#endif
