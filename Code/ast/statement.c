#include "cmm.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/function.h"
#include "ir.h"

Statement Statement_Invalid = { .type = STMT_INVALID };

Statement *
Statement_Compound_Constructor(cmm_loc_t location, VarList varlist, StmtList stmtlist) {
    Statement *ret = palloc(sizeof(Statement));
    ret->type = STMT_COMPOUND;
    ret->location = location;
    ret->varlist = varlist;
    ret->stmtlist = stmtlist;
    return ret;
}

Statement *
Statement_Expression_Constructor(cmm_loc_t location, Expression *expr) {
    Statement *ret = palloc(sizeof(Statement));
    ret->type = STMT_EXPRESSION;
    ret->location = location;
    ret->expr = expr;
    return ret;
}

Statement *
Statement_Return_Constructor(cmm_loc_t location, Expression *expr, Function *func) {
    Statement *ret = palloc(sizeof(Statement));
    ret->type = STMT_RETURN;
    ret->location = location;
    ret->expr = expr;
    ret->func = func;
    if (!Type_Compatible(func->rettype, expr->valtype))
        cmm_error(CMM_ERROR_RETURN_TYPE_MISMATCH, location);
    return ret;
}

Statement *
Statement_IfThen_Constructor(cmm_loc_t location, Expression *if_cond, Statement *stat_if_true) {
    Statement *ret = palloc(sizeof(Statement));
    if (!Type_Is_Int(if_cond->valtype))
        cmm_error(CMM_ERROR_IF_TYPE_MISMATCH, if_cond->location);
    ret->type = STMT_IFTHEN;
    ret->location = location;
    ret->if_cond = if_cond;
    ret->stat_if_true = stat_if_true;
    return ret;
}

Statement *
Statement_IfThenElse_Constructor(cmm_loc_t location,
        Expression *if_cond, Statement *stat_if_true, Statement *stat_if_false) {
    Statement *ret = palloc(sizeof(Statement));
    if (!Type_Is_Int(if_cond->valtype))
        cmm_error(CMM_ERROR_IF_TYPE_MISMATCH, if_cond->location);
    ret->type = STMT_IFTHENELSE;
    ret->location = location;
    ret->if_cond = if_cond;
    ret->stat_if_true = stat_if_true;
    ret->stat_if_false = stat_if_false;
    return ret;
}

Statement *
Statement_While_Constructor(cmm_loc_t location, Expression *while_cond, Statement *while_body) {
    Statement *ret = palloc(sizeof(Statement));
    if (!Type_Is_Int(while_cond->valtype))
        cmm_error(CMM_ERROR_WHILE_TYPE_MISMATCH, while_cond->location);
    ret->type = STMT_WHILE;
    ret->location = location;
    ret->while_cond = while_cond;
    ret->while_body = while_body;
    return ret;
}

void Statement_IR_Generate_Declaration(Statement *stmt) {
    if (stmt->type != STMT_COMPOUND) return;
    for (VarList var = stmt->varlist; var; var = var->next)
        Variable_IR_Generate_Declaration(var->data, false);
    for (StmtList subst = stmt->stmtlist; subst; subst = subst->next)
        Statement_IR_Generate_Declaration(subst->data);
}

static void _return_ir_gen(Statement *stmt) {
    if (stmt->expr->type == EXPR_FUNCCALL) {
        /* tail call optimization */
        Expression_TailCall_IR_Generate_Code(stmt->expr);
    } else {
        ir_gen_add(ir_make_return(Expression_IR_Generate_Code(stmt->expr)));
    }
}

static void _ifthen_ir_gen(Statement *stmt) {
    ir_val cond = Expression_IR_Generate_Code(stmt->if_cond);
    size_t if_false_label = ir_newlabel();
    ir_gen_add(ir_make_if(IRREL_EQU, cond, ir_make_immd(0), if_false_label));
    Statement_IR_Generate_Code(stmt->stat_if_true);
    ir_gen_add(ir_make_label(if_false_label));
}

static void _ifthenelse_ir_gen(Statement *stmt) {
    ir_val cond = Expression_IR_Generate_Code(stmt->if_cond);
    size_t if_false_label = ir_newlabel(), if_end_label = ir_newlabel();
    ir_gen_add(ir_make_if(IRREL_EQU, cond, ir_make_immd(0), if_false_label));
    Statement_IR_Generate_Code(stmt->stat_if_true);
    ir_gen_add(ir_make_goto(if_end_label));
    ir_gen_add(ir_make_label(if_false_label));
    Statement_IR_Generate_Code(stmt->stat_if_false);
    ir_gen_add(ir_make_label(if_end_label));
}

static void _while_ir_gen(Statement *stmt) {
    size_t while_begin = ir_newlabel(), while_end = ir_newlabel();
    ir_gen_add(ir_make_label(while_begin));
    ir_val cond = Expression_IR_Generate_Code(stmt->while_cond);
    ir_gen_add(ir_make_if(IRREL_EQU, cond, ir_make_immd(0), while_end));
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
