#include "cmm.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/function.h"

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
