#include <stdio.h>
#include <string.h>
#include "ir.h"
#include "cmm.h"
#include "ast/expression.h"
#include "ast/function.h"
#include "ast/variable.h"

static inline Type *__get_binary_operand_return_type(cmm_loc_t location,
        enum BinaryOperator op, Type *t1, Type *t2) {
    if (t1->typector == TC_INVALID || t2->typector == TC_INVALID)
        return &Type_Invalid;
    switch (op) {
    case BOP_ADD:
    case BOP_MINUS:
    case BOP_STAR:
    case BOP_DIV:
        if (!Type_Is_Basic(t1) || !Type_Compatible(t1, t2)) {
            cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
            return &Type_Invalid;
        }
        return t1;
    case BOP_GT:
    case BOP_LT:
    case BOP_GE:
    case BOP_LE:
    case BOP_EQU:
    case BOP_NEQ:
        if (!Type_Is_Basic(t1) || !Type_Compatible(t1, t2)) {
            cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
            return &Type_Invalid;
        }
        return Type_Basic_Constructor(BT_INT);
    case BOP_AND:
    case BOP_OR:
        if (!Type_Is_Int(t1) || !Type_Is_Int(t2)) {
            cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
            return &Type_Invalid;
        }
        return Type_Basic_Constructor(BT_INT);
    case BOP_ARRAY_ACCESS:
        if (!Type_Is_Array(t1)) {
            cmm_error(CMM_ERROR_INVSUB, location);
            return &Type_Invalid;
        }
        if (!Type_Is_Int(t2))
            cmm_error(CMM_ERROR_INVSUBTYPE, location);
        return t1->underlying;
    default:
        assert(0);
    }
}

static inline Type *__get_unary_operand_return_type(cmm_loc_t location,
        enum UnaryOperator op, Type *t) {
    if (t->typector == TC_INVALID) return t;
    switch (op) {
    case UOP_NEGATE:
        if (!Type_Is_Basic(t)) {
            cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
            return &Type_Invalid;
        }
        return t;
    case UOP_NOT:
        if (!Type_Is_Int(t)) {
            cmm_error(CMM_ERROR_OPERAND_TYPE_MISMATCH, location);
            return &Type_Invalid;
        }
        return Type_Basic_Constructor(BT_INT);
    default:
        assert(0);
    }
}


Expression *
Expression_Binary_Constructor(enum BinaryOperator optype, cmm_loc_t location,
Expression *lhs, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_BINARY_EXPR;
    ret->location = location;
    ret->lvalue = (optype == BOP_ARRAY_ACCESS ? lhs->lvalue : false);
    ret->bop_type = optype;
    ret->valtype = __get_binary_operand_return_type(location, optype,
        lhs->valtype, rhs->valtype);
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
    ret->lvalue = false;
    ret->uop_type = optype;
    ret->valtype = __get_unary_operand_return_type(location, optype, rhs->valtype);
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_Assign_Constructor(cmm_loc_t location, Expression *lhs, Expression *rhs) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_ASSIGN;
    ret->location = location;
    if (!lhs->lvalue)
        cmm_error(CMM_ERROR_ASSIGN_TO_RVALUE, location);
    if (!Type_Compatible(lhs->valtype, rhs->valtype))
        cmm_error(CMM_ERROR_ASSIGN_TYPE_MISMATCH, location);
    ret->valtype = lhs->valtype;
    ret->lvalue = true;
    ret->lhs = lhs;
    ret->rhs = rhs;
    return ret;
}

Expression *
Expression_FuncCall_Constructor(cmm_loc_t location, const char *funcname, ArgList args) {
    Expression *ret = palloc(sizeof(Expression));
    Function *func = symtbl_function_find(funcname, location);

    ret->type = EXPR_FUNCCALL;
    ret->location = location;
    ret->valtype = func->rettype;
    ret->lvalue = false;
    ret->func = func;
    ret->arglist = args;
    VarList param = func->paramlist;
    ArgList arg = args;
    // for dummy function, do not perform argument check
    if (func == &Function_Invalid) return ret;

    for (; param && arg; param = param->next, arg = arg->next)
        if (!Type_Compatible(param->data->valtype, arg->data->valtype))
            cmm_error(CMM_ERROR_ARG_TYPE_MISMATCH, location);
    if (param || arg)
        cmm_error(CMM_ERROR_ARG_NUMBER_MISMATCH, location);
    return ret;
}

static inline Variable *
__MemberAccess(cmm_loc_t location, Expression *expr, const char *memname) {
    if (expr->valtype->typector != TC_STRUCT) {
        cmm_error(CMM_ERROR_MEMBER_NONSTRUCT, location);
        return &Variable_Invalid;
    } else {
        Variable *member = symtbl_find(&expr->valtype->symtable, memname);
        if (member == NULL) {
            cmm_error(CMM_ERROR_UNDEF_MEMBER, location, expr->valtype->name, memname);
            return &Variable_Invalid;
        }
        return member;
    }
}

Expression *
Expression_MemberAccess_Constructor(cmm_loc_t location, Expression *expr, const char *memname) {
    Expression *ret = palloc(sizeof(Expression));
    Variable *member = __MemberAccess(location, expr, memname);
    ret->type = EXPR_MEMBERACCESS;
    ret->location = location;
    ret->valtype = member->valtype;
    ret->expr = expr;
    ret->member = member;
    ret->lvalue = expr->lvalue;
    return ret;
}

Expression *
Expression_Variable_Constructor(cmm_loc_t location, Variable *var) {
    Expression *ret = palloc(sizeof(Expression));
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

Expression *
Expression_Read_Constructor(cmm_loc_t location) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_READ;
    ret->location = CMM_LOC_INITIALIZER;
    ret->valtype = Type_Basic_Constructor(BT_INT);
    ret->lvalue = false;
    return ret;
}

Expression *
Expression_Write_Constructor(cmm_loc_t location, Expression* src) {
    Expression *ret = palloc(sizeof(Expression));
    ret->type = EXPR_WRITE;
    ret->location = CMM_LOC_INITIALIZER;
    ret->valtype = Type_Basic_Constructor(BT_INT);
    ret->lvalue = false;
    ret->rhs = src;
    return ret;
}

static ir_val _binary_arith_ir_gen(Expression *expr) {
    IRBinaryOperator arith_op;
    switch (expr->bop_type) {
    case BOP_ADD: arith_op = IRBOP_ADD; break;
    case BOP_MINUS: arith_op = IRBOP_MINUS; break;
    case BOP_STAR: arith_op = IRBOP_STAR; break;
    case BOP_DIV: arith_op = IRBOP_DIV; break;
    default: assert(0);
    }
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_binary_op(arith_op, dest,
        Expression_IR_Generate_Code(expr->lhs),
        Expression_IR_Generate_Code(expr->rhs)
    ));
    return dest;
}

static ir_val _binary_relop_ir_gen(Expression *expr) {
    IRRelationalOperator rel_op;
    switch (expr->bop_type) {
    case BOP_GT: rel_op = IRREL_GT; break;
    case BOP_LT: rel_op = IRREL_LT; break;
    case BOP_GE: rel_op = IRREL_GE; break;
    case BOP_LE: rel_op = IRREL_LE; break;
    case BOP_EQU: rel_op = IRREL_EQU; break;
    case BOP_NEQ: rel_op = IRREL_NEQ; break;
    default: assert(0);
    }
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_if(rel_op,
        Expression_IR_Generate_Code(expr->lhs),
        Expression_IR_Generate_Code(expr->rhs),
        tmplabel
    ));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _binary_logic_and_gen(Expression *expr) {
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_if(IRREL_EQU, Expression_IR_Generate_Code(expr->lhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_if(IRREL_EQU, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _binary_logic_or_gen(Expression *expr) {
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_if(IRREL_NEQ, Expression_IR_Generate_Code(expr->lhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_if(IRREL_NEQ, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _array_access_gen(Expression *expr) {
    ir_val val_addr = ir_make_var(ir_newvar()), index = ir_make_var(ir_newvar());
    ir_val addr = ir_make_ref(Expression_IR_Generate_Code(expr->lhs));
    ir_gen_add(ir_make_binary_op(
        IRBOP_STAR, index,
        Expression_IR_Generate_Code(expr->rhs),
        ir_make_immd((int)expr->lhs->valtype->underlying->width)));
    ir_gen_add(ir_make_binary_op(IRBOP_ADD, val_addr, addr, index));
    return ir_make_deref(val_addr.varid);
}

static ir_val _binary_expr_ir_gen(Expression *expr) {
    switch (expr->bop_type) {
    case BOP_ADD:
    case BOP_MINUS:
    case BOP_STAR:
    case BOP_DIV:
        return _binary_arith_ir_gen(expr);
    case BOP_GT:
    case BOP_LT:
    case BOP_GE:
    case BOP_LE:
    case BOP_EQU:
    case BOP_NEQ:
        return _binary_relop_ir_gen(expr);
    case BOP_AND:
        return _binary_logic_and_gen(expr);
    case BOP_OR:
        return _binary_logic_or_gen(expr);
    case BOP_ARRAY_ACCESS:
        return _array_access_gen(expr);
    }
    assert(0);
}

static ir_val _unary_negate_ir_gen(Expression *expr) {
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_binary_op(IRBOP_MINUS, dest, ir_make_immd(0), Expression_IR_Generate_Code(expr->rhs)));
    return dest;
}

static ir_val _unary_not_ir_gen(Expression *expr) {
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_if(IRREL_EQU, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _unary_expr_ir_gen(Expression *expr) {
    switch (expr->uop_type) {
    case UOP_NEGATE: return _unary_negate_ir_gen(expr);
    case UOP_NOT: return _unary_not_ir_gen(expr);
    }
    assert(0);
}

static ir_val _assign_expr_ir_gen(Expression *expr) {
    ir_val dest = Expression_IR_Generate_Code(expr->lhs);
    ir_gen_add(ir_make_assign(dest, Expression_IR_Generate_Code(expr->rhs)));
    return dest;
}

static void _arglist_ir_push(ArgList arglist) {
    if (!arglist) return;
    ir_val temp = Expression_IR_Generate_Code(arglist->data);
    _arglist_ir_push(arglist->next);
    if (arglist->data->valtype->typector == TC_STRUCT ||
        arglist->data->valtype->typector == TC_ARRAY) {
        ir_gen_add(ir_make_arg(ir_make_ref(temp)));
    } else {
        ir_gen_add(ir_make_arg(temp));
    }
}

static ir_val _funccall_ir_gen(Expression *expr) {
    ir_val dest = ir_make_var(ir_newvar());
    if (strcmp(expr->func->name, "read") == 0) {
        ir_gen_add(ir_make_read(dest));
    } else if (strcmp(expr->func->name, "write") == 0) {
        ir_gen_add(ir_make_write(Expression_IR_Generate_Code(expr->arglist->data)));
        ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    } else {
        _arglist_ir_push(expr->arglist);
        ir_gen_add(ir_make_call(dest, expr->func->name));
    }
    return dest;
}

static ir_val _member_access_ir_gen(Expression *expr) {
    ir_val val_addr = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_binary_op(
        IRBOP_ADD, val_addr,
        ir_make_ref(Expression_IR_Generate_Code(expr->expr)),
        ir_make_immd((int)expr->member->offset)
    ));
    return ir_make_deref(val_addr.varid);
}

static ir_val _variable_ir_gen(Expression *expr) {
    return ir_make_var(expr->var->ir_id);
}

static ir_val _literal_ir_gen(Expression *expr) {
    assert(Type_Is_Int(expr->valtype));
    return ir_make_immd(expr->lit_int);
}

static ir_val _read_ir_gen(Expression *expr) {
    ir_val dest = ir_make_var(ir_newvar());
    ir_gen_add(ir_make_read(dest));
    return dest;
}

static ir_val _write_ir_gen(Expression *expr) {
    ir_gen_add(ir_make_write(Expression_IR_Generate_Code(expr->rhs)));
    return ir_make_immd(0);
}

void Expression_TailCall_IR_Generate_Code(Expression *expr) {
    _arglist_ir_push(expr->arglist);
    ir_gen_add(ir_make_goto(expr->func->ir_start_label));
}

ir_val Expression_IR_Generate_Code(Expression *expr) {
    switch (expr->type) {
    case EXPR_BINARY_EXPR: return _binary_expr_ir_gen(expr);
    case EXPR_UNARY_EXPR: return _unary_expr_ir_gen(expr);
    case EXPR_ASSIGN: return _assign_expr_ir_gen(expr);
    case EXPR_FUNCCALL: return _funccall_ir_gen(expr);
    case EXPR_MEMBERACCESS: return _member_access_ir_gen(expr);
    case EXPR_VARIABLE: return _variable_ir_gen(expr);
    case EXPR_LITERAL: return _literal_ir_gen(expr);
    case EXPR_READ: return _read_ir_gen(expr);
    case EXPR_WRITE: return _write_ir_gen(expr);
    }
    assert(0);
}