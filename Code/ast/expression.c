#include "cmm.h"
#include "ast/expression.h"
#include "ast/function.h"
#include "ast/variable.h"

static bool __check_binary_operand_type_mismatch(enum BinaryOperator op, Type *t1, Type *t2) {
    // TODO:
}

static bool __check_unary_operand_type_mismatch(enum UnaryOperator op, Type *t) {
    // TODO:
}


Expression *
Expression_Binary_Constructor(enum BinaryOperator optype, cmm_loc_t location,
Expression *lhs, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_BINARY_EXPR;
    ret->location = location;
    ret->valtype = lhs->valtype;
    ret->lvalue = false;
    ret->bop_type = optype;
    if (__check_binary_operand_type_mismatch(optype, lhs->valtype, rhs->valtype))
        cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
    ret->location = location;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_Unary_Constructor(enum UnaryOperator optype, cmm_loc_t location,
Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_UNARY_EXPR;
    ret->location = location;
    ret->valtype = rhs->valtype;
    ret->lvalue = false;
    ret->uop_type = optype;
    if (__check_unary_operand_type_mismatch(optype, rhs->valtype))
        cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_Assign_Constructor(cmm_loc_t location, Expression *lhs, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_ASSIGN;
    ret->location = location;
    ret->valtype = lhs->valtype;
    ret->lvalue = true;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_FuncCall_Constructor(cmm_loc_t location, const char *funcname, ArgList args) {
    Expression *ret = palloc(sizeof(Expression));
    Function *func = symtbl_function_find(funcname);
    if (func == NULL) {
        // TODO: add dummy function
        cmm_error(CMM_ERROR_UNDEF_FUNC, location, funcname);
    }
    ret->type = EXPR_FUNCCALL;
    ret->location = location;
    ret->valtype = func->rettype;
    ret->lvalue = false;
    ret->func = func;
    ret->arglist = args;
    // TODO: argument type check
    return ret;
}

Expression *
Expression_MemberAccess_Constructor(cmm_loc_t location, Expression *expr, const char *memname) {
    Expression *ret = palloc(sizeof(Expression));
    Variable *member =  symtbl_find(&expr->valtype->symtable, memname);
    if (member == NULL) {
        // TODO: add dummy member
        cmm_error(CMM_ERROR_UNDEF_MEMBER, location, memname);
    }
    ret->type = EXPR_MEMBERACCESS;
    ret->location = location;
    ret->valtype = member->valtype;
    ret->expr = expr;
    ret->member = member;
    ret->lvalue = true;
    return ret;
}

Expression *
Expression_Variable_Constructor(cmm_loc_t location, const char *varname) {
    Expression *ret = palloc(sizeof(Expression));
    Variable *var = symtbl_variable_find(varname);
    if (var == NULL) {
        // TODO: add dummy variable
        cmm_error(CMM_ERROR_UNDEF_VAR, location, varname);
    }
    ret->type = EXPR_VARIABLE;
    ret->location = location;
    ret->valtype = var->valtype;
    ret->lvalue = true;
    ret->var = var;
    return ret;
}

Expression *
Expression_Literal_int_Constructor(cmm_loc_t location, int value) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_LITERAL;
    ret->location = location;
    ret->valtype = Type_Basic_Constructor(BT_INT);
    ret->lvalue = false;
    ret->lit_int = value;
    return ret;
}

Expression *
Expression_Literal_float_Constructor(cmm_loc_t location, float value) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_LITERAL;
    ret->location = location;
    ret->valtype = Type_Basic_Constructor(BT_FLOAT);
    ret->lvalue = false;
    ret->lit_float = value;
    return ret;
}
