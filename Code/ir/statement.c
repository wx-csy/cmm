#include "cmm.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/function.h"
#include "ir.h"
#include "option.h"

void Statement_IR_Generate_Declaration(Statement *stmt) {
    if (stmt->type != STMT_COMPOUND) return;
    for (VarList var = stmt->varlist; var; var = var->next)
        Variable_IR_Generate_Declaration(var->data, false);
    for (StmtList subst = stmt->stmtlist; subst; subst = subst->next)
        Statement_IR_Generate_Declaration(subst->data);
}

static void _return_ir_gen(Statement *stmt) {
    assert(Type_Is_Int(stmt->expr->valtype));
    if (opt_optimize && stmt->expr->type == EXPR_FUNCCALL) {
        /* tail call optimization */
        Expression_TailCall_IR_Generate_Code(stmt->expr);
    } else {
        ir_gen_add(ir_make_return(Expression_IR_Generate_Code(stmt->expr)));
    }
}

static void _ifthen_ir_gen(Statement *stmt) {
    size_t if_true_label = ir_newlabel(), if_false_label = ir_newlabel();
    Cond_IR_Gen(stmt->if_cond, if_true_label, if_false_label);
    ir_gen_add(ir_make_label(if_true_label));
    Statement_IR_Generate_Code(stmt->stat_if_true);
    ir_gen_add(ir_make_label(if_false_label));
}

static void _ifthenelse_ir_gen(Statement *stmt) {
    size_t if_true_label = ir_newlabel(), if_false_label = ir_newlabel(), if_end_label = ir_newlabel();
    Cond_IR_Gen(stmt->if_cond, if_true_label, if_false_label);
    ir_gen_add(ir_make_label(if_true_label));
    Statement_IR_Generate_Code(stmt->stat_if_true);
    ir_gen_add(ir_make_goto(if_end_label));
    ir_gen_add(ir_make_label(if_false_label));
    Statement_IR_Generate_Code(stmt->stat_if_false);
    ir_gen_add(ir_make_label(if_end_label));
}

static void _while_ir_gen(Statement *stmt) {
    size_t while_begin = ir_newlabel(), while_block = ir_newlabel(), while_end = ir_newlabel();
    ir_gen_add(ir_make_label(while_begin));
    Cond_IR_Gen(stmt->if_cond, while_block, while_end);
    ir_gen_add(ir_make_label(while_block));
    Statement_IR_Generate_Code(stmt->while_body);
    ir_gen_add(ir_make_goto(while_begin));
    ir_gen_add(ir_make_label(while_end));
}

void Statement_IR_Generate_Code(Statement *stmt) {
    switch (stmt->type) {
    case STMT_INVALID:
        assert(0);
    case STMT_COMPOUND:
        for (StmtList subst = stmt->stmtlist; subst; subst = subst->next)
            Statement_IR_Generate_Code(subst->data);
        break;
    case STMT_EXPRESSION:
        Expression_IR_Generate_Code(stmt->expr);
        break;
    case STMT_RETURN:
        return _return_ir_gen(stmt);
    case STMT_IFTHEN:
        return _ifthen_ir_gen(stmt);
    case STMT_IFTHENELSE:
        return _ifthenelse_ir_gen(stmt);
    case STMT_WHILE:
        return _while_ir_gen(stmt);
    }
}
