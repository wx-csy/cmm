#include "ast/function.h"
#include "ast/statement.h"
#include "ast/type.h"
#include "ir.h"

Function Function_Invalid = {
    .name = "(invalid)",
    .rettype = &Type_Invalid,
    .paramlist = NULL,
    .stmt = NULL
};

Function *Function_Constructor(const char *name, cmm_loc_t location, Type *rettype) {
    Function *ret = pzalloc(sizeof(Function));
    ret->name = strpdup(name);
    ret->location = location;
    ret->rettype = rettype;
    return ret;
}

bool Function_Declaration_Compatible(Function *func1, Function *func2) {
    /* TODO: currently, we define two function declaration as compatible
     *   if and only if the return type and param list are compatible.
     *   This is problematic: two arrays declared with different sizes
     *   may lead to binary incompatibility during assignment.
     */
    if (!Type_Compatible(func1->rettype, func2->rettype))
        return false;
    VarList list1 = func1->paramlist, list2 = func2->paramlist;
    for (; list1 && list2; list1 = list1->next, list2 = list2->next)
        if (!Type_Compatible(list1->data->valtype, list2->data->valtype))
            return false;
    if (list1 || list2) return false;
    return true;
}

void Function_IR_Generate_Declaration(Function *func) {
    ir_print_function(func->name);
    for (VarList param = func->paramlist; param; param = param->next)
        Variable_IR_Generate_Declaration(param->data, true);
    Statement_IR_Generate_Declaration(func->stmt);
}

