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

    size_t ir_id;
} Variable;

extern Variable Variable_Invalid;

Variable *Variable_Constructor(cmm_loc_t location, const char *name);
void Variable_Add_Initializer(Variable *var, Expression *init);
void Variable_IR_Generate_Declaration(Variable *var, bool is_param);
#endif
