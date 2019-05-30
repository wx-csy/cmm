#include <stdio.h>
#include "ast/function.h"
#include "ast/statement.h"
#include "ast/type.h"
#include "ir.h"

void Function_IR_Generate_Code(Function *func) {
    ir_nextval = 0;
    func->ir_start_label = ir_newlabel();
    ir_gen_add(ir_make_function(func->name));
    ir_gen_add(ir_make_label(func->ir_start_label));
    for (VarList param = func->paramlist; param; param = param->next)
        Variable_IR_Generate_Declaration(param->data, true);
    Statement_IR_Generate_Declaration(func->stmt);
    Statement_IR_Generate_Code(func->stmt);
    ir_gen_add(ir_make_return(ir_make_immd(0)));
    ir_gen_add_with_comment(ir_make_endfunction(func->name), "end function '%s'", func->name);
}