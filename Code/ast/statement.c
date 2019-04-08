#include "cmm.h"
#include "ast/statement.h"

Statement *
Compound_Expression_Constructor(cmm_loc_t location, VarList varlist, StmtList stmtlist) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_COMPOUND;
    ret->location = location;
    ret->varlist = varlist;
    ret->stmtlist = stmtlist;
    return ret;
}

Statement *
Expression_Statement_Constructor(cmm_loc_t location, Expression *expr) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_EXPRESSION;
    ret->location = location;
    ret->expr = expr;
    return ret;
}

Statement *
Return_Statement_Constructor(cmm_loc_t location, Expression *expr) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_RETURN;
    ret->location = location;
    ret->expr = expr;
    return ret;
}

Statement *
IfThen_Statement_Constructor(cmm_loc_t location, Expression *if_cond, Statement *stat_if_true) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_IFTHEN;
    ret->location = location;
    ret->if_cond = if_cond;
    ret->stat_if_true = stat_if_true;
    return ret;
}

Statement *
IfThenElse_Statement_Constructor(cmm_loc_t location,
        Expression *if_cond, Statement *stat_if_true, Statement *stat_if_false) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_IFTHENELSE;
    ret->location = location;
    ret->if_cond = if_cond;
    ret->stat_if_true = stat_if_true;
    ret->stat_if_false = stat_if_false;
    return ret;
}

Statement *
While_Statement_Constructor(cmm_loc_t location, Expression *while_cond, Statement *while_body) {
    Statement *ret = malloc(sizeof(Statement));
    ret->type = STMT_WHILE;
    ret->location = location;
    ret->while_cond = while_cond;
    ret->while_body = while_body;
    return ret;
}

void Statement_Destructor(Statement *stmt) {
    if (stmt == NULL) return;
    switch (stmt->type) {
        case STMT_COMPOUND :
            for (size_t i = 0; i < stmt->varlist.nr_var; i++)
                Variable_Destructor(stmt->varlist.vars[i]);
            free(stmt->varlist.vars);
            for (size_t i = 0; i < stmt->stmtlist.nr_stmt; i++)
                Statement_Destructor(stmt->stmtlist.stmts[i]);
            free(stmt->stmtlist.stmts);
            break;
        case STMT_EXPRESSION :
            Expression_Destructor(stmt->expr);
            break;
        case STMT_RETURN :
            Expression_Destructor(stmt->expr);
            break;
        case STMT_IFTHEN :
            Expression_Destructor(stmt->if_cond);
            Statement_Destructor(stmt->stat_if_true);
            break;
        case STMT_IFTHENELSE :
            Expression_Destructor(stmt->if_cond);
            Statement_Destructor(stmt->stat_if_true);
            Statement_Destructor(stmt->stat_if_false);
            break;
        case STMT_WHILE :
            Expression_Destructor(stmt->while_cond);
            Statement_Destructor(stmt->while_body);
            break;
        default :
            assert(0);
    }
    free(stmt);
}
