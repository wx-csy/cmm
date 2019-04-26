#include "cmm.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/type.h"

Variable Variable_Invalid = {
    .name = "(invalid)",
    .valtype = &Type_Invalid
};

Variable *Variable_Constructor(cmm_loc_t location, const char *name) {
    Variable *ret = pzalloc(sizeof(Variable));
    ret->name = strpdup(name);
    ret->location = location;
    return ret;
}

void Variable_Add_Initializer(Variable *var, Expression *init) {
    if (!Type_Compatible(var->valtype, init->valtype)) {
        cmm_error(CMM_ERROR_INIT_TYPE_MISMATCH, init->location);
    } else {
        var->initializer = init;
    }
}