#include "cmm.h"
#include "ast/expression.h"

#define _EXPR_BINARY_BEGIN      EXPR_BINARY_ADD
#define _EXPR_BINARY_END        EXPR_BINARY_OR
#define _EXPR_UNARY_BEGIN       EXPR_UNARY_NEGATE
#define _EXPR_UNARY_END         EXPR_UNARY_NOT

Expression *
Expression_Binary_Constructor(enum ExprType type, cmm_loc_t location,
Expression *lhs, Expression *rhs) {
    assert(type >= _EXPR_UNARY_BEGIN && type <= _EXPR_UNARY_END);
    Expression *ret = palloc(sizeof(Expression));
    ret->type = type;
    ret->location = location;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_Unary_Constructor(enum ExprType type, cmm_loc_t location,
Expression *rhs) {
    assert(type >= _EXPR_UNARY_BEGIN && type <= _EXPR_UNARY_END);
    Expression *ret = palloc(sizeof(Expression));
    ret->type = type;
    ret->location = location;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_Assign_Constructor(cmm_loc_t location,
Expression *lhs, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_ASSIGN;
    ret->location = location;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_FuncCall_Constructor(cmm_loc_t location,
Function *func, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_FUNCCALL;
    ret->location = location;
    ret->func = func;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_ArrayAccess_Constructor(cmm_loc_t location,
Expression *arr, Expression *subscript) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_ARRAYACCESS;
    ret->location = location;
    ret->arr = arr;
    ret->subscript = subscript;
    return ret;
}

Expression *
Expression_Variable_Constructor(cmm_loc_t location, Variable *var) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_VARIABLE;
    ret->location = location;
    ret->var = var;
    return ret;
}

Expression *
Expression_Literal_Constructor(cmm_loc_t location, Literal lit) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_LITERAL;
    ret->location = location;
    ret->lit = lit;
    return ret;
}
