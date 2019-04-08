#include "cmm.h"
#include "ast/expression.h"

Expression *
Binary_Expression_Constructor(enum ExprType type, cmm_loc_t location, 
Expression *lhs, Expression *rhs) {
    assert(type >= _EXPR_UNARY_BEGIN && type <= _EXPR_UNARY_END);
    Expression *ret = malloc(sizeof(Expression));
    ret->type = type;
    ret->location = location;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Unary_Expression_Constructor(enum ExprType type, cmm_loc_t location,
Expression *rhs) {
    assert(type >= _EXPR_UNARY_BEGIN && type <= _EXPR_UNARY_END);
    Expression *ret = malloc(sizeof(Expression));
    ret->type = type;
    ret->location = location;
    ret->rhs = rhs;
    return ret;
}

Expression *
Assign_Expression_Constructor(cmm_loc_t location, 
Expression *lhs, Expression *rhs) {
    Expression *ret = malloc(sizeof(Expression));
    ret->type = EXPR_ASSIGN;
    ret->location = location;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
FuncCall_Expression_Constructor(cmm_loc_t location, 
Function *func, Expression *rhs) {
    Expression *ret = malloc(sizeof(Expression));
    ret->type = EXPR_FUNCCALL;
    ret->location = location;
    ret->func = func;
    ret->rhs = rhs;
    return ret;
}

Expression *
ArrayAccess_Expression_Constructor(cmm_loc_t location, 
Variable *var, SubList sublist) {
    Expression *ret = malloc(sizeof(Expression));
    ret->type = EXPR_ARRAYACCESS;
    ret->location = location;
    ret->var = var;
    ret->sublist = sublist; 
    return ret;
}

Expression *
Variable_Expression_Constructor(cmm_loc_t location, Variable *var) {
    Expression *ret = malloc(sizeof(Expression));
    ret->type = EXPR_VARAIBLE;
    ret->location = location;
    ret->var = var;
    return ret;
}

Expression *
Literal_Expression_Constructor(cmm_loc_t location, Literal *lit) {
    Expression *ret = malloc(sizeof(Expression));
    ret->type = EXPR_LITERAL;
    ret->location = location;
    ret->lit = lit;
    return ret;
}

void Expression_Destructor(Expression *expr) {
    if (expr == NULL) return;
    switch (expr->type) {
        case _EXPR_BINARY_BEGIN ... _EXPR_BINARY_END :
            Expression_Destructor(expr->lhs);
            Expression_Destructor(expr->rhs);
            break;
        case _EXPR_UNARY_BEGIN ... _EXPR_UNARY_END :
            Expression_Destructor(expr->rhs);
            break;
        case EXPR_ASSIGN :
            Expression_Destructor(expr->lhs);
            Expression_Destructor(expr->rhs);
            break;
        case EXPR_FUNCCALL :
            for (size_t i = 0; i < expr->arglist.nr_arg; i++)
                Expression_Destructor(expr->arglist.args[i]);
            free(expr->arglist.args);
            break;
        case EXPR_ARRAYACCESS :
            for (size_t i = 0; i < expr->sublist.nr_arg; i++)
                Expression_Destructor(expr->sublist.args[i]);
            free(expr->arglist.args);
            break;
        default :
            assert(0);
    }
    free(expr);
}
