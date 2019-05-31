#include "cmm.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/type.h"
#include "ir.h"

void Variable_IR_Generate_Declaration(Variable *var, bool is_param) {
    var->ir_id = ir_newvar(var->valtype->width);
    if (is_param) {
        assert(Type_Is_Basic(var->valtype));
        ir_gen_add_with_comment(ir_make_param(ir_make_var(var->ir_id)), "param '%s'", var->name);
    } else {
        ir_gen_add_with_comment(ir_make_dec(ir_make_var(var->ir_id), var->valtype->width), "var '%s'", var->name);
        if (var->initializer)
            ir_gen_add(ir_make_assign(ir_make_var(var->ir_id), Expression_IR_Generate_Code(var->initializer)));
    }
}