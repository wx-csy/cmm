#include "cmm.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/type.h"
#include "ir.h"

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

void Variable_IR_Generate_Declaration(Variable *var, bool is_param) {
    var->ir_id = ir_newval();
    if (is_param) {
        // only size=4 parameter supported
        assert(var->valtype->width == 4);
        ir_printf("\tPARAM v%zu\n", var->ir_id);
    } else if (var->valtype->width != 4) {
        ir_printf("\tDEC v%zu %zu\n", var->ir_id, var->valtype->width);
    }
}