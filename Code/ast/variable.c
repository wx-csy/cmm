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
    var->ir_id = ir_newvar();
    if (is_param) {
        if (Type_Is_Basic(var->valtype)) {
            ir_gen_add_with_comment(ir_make_param(ir_make_var(var->ir_id)), "param '%s'", var->name);
        } else {
            ir_val tmpparam = ir_make_var(ir_newvar()), param = ir_make_var(var->ir_id), pptr = ir_make_var(ir_newvar());
            ir_gen_add_with_comment(ir_make_param(tmpparam), "param '%s' (ptr)", var->name);
            ir_gen_add_with_comment(ir_make_dec(param, var->valtype->width), "param '%s'", var->name);
            ir_gen_add(ir_make_assign(pptr, ir_make_ref(param)));
            for (int i = 0; i < var->valtype->width; i += 4) {
                ir_gen_add(ir_make_assign(ir_make_deref(pptr.varid), ir_make_deref(tmpparam.varid)));
                ir_gen_add(ir_make_binary_op(IRBOP_ADD, pptr, pptr, ir_make_immd(4)));
                ir_gen_add(ir_make_binary_op(IRBOP_ADD, tmpparam, tmpparam, ir_make_immd(4)));
            }
        }
    } else {
        ir_gen_add_with_comment(ir_make_dec(ir_make_var(var->ir_id), var->valtype->width), "var '%s'", var->name);
        if (var->initializer)
            ir_gen_add(ir_make_assign(ir_make_var(var->ir_id), Expression_IR_Generate_Code(var->initializer)));
    }
}