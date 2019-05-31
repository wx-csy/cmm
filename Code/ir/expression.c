#include <stdio.h>
#include <string.h>
#include "ir.h"
#include "cmm.h"
#include "ast/expression.h"
#include "ast/function.h"
#include "ast/variable.h"

static ir_val _binary_arith_ir_gen(Expression *expr) {
    IRBinaryOperator arith_op;
    switch (expr->bop_type) {
    case BOP_ADD: arith_op = IRBOP_ADD; break;
    case BOP_MINUS: arith_op = IRBOP_MINUS; break;
    case BOP_STAR: arith_op = IRBOP_STAR; break;
    case BOP_DIV: arith_op = IRBOP_DIV; break;
    default: assert(0);
    }
    ir_val dest = ir_make_var(ir_newvar(4));
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
    ir_val dest = ir_make_var(ir_newvar(4));
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
    ir_val dest = ir_make_var(ir_newvar(4));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_if(IRREL_EQU, Expression_IR_Generate_Code(expr->lhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_if(IRREL_EQU, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _binary_logic_or_gen(Expression *expr) {
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar(4));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(1)));
    ir_gen_add(ir_make_if(IRREL_NEQ, Expression_IR_Generate_Code(expr->lhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_if(IRREL_NEQ, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_label(tmplabel));
    return dest;
}

static ir_val _array_access_gen(Expression *expr) {
    ir_val val_addr = ir_make_var(ir_newvar(4)), index = ir_make_var(ir_newvar(4));
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
    ir_val dest = ir_make_var(ir_newvar(4));
    ir_gen_add(ir_make_binary_op(IRBOP_MINUS, dest, ir_make_immd(0), Expression_IR_Generate_Code(expr->rhs)));
    return dest;
}

static ir_val _unary_not_ir_gen(Expression *expr) {
    size_t tmplabel = ir_newlabel();
    ir_val dest = ir_make_var(ir_newvar(4));
    ir_gen_add(ir_make_assign(dest, ir_make_immd(0)));
    ir_gen_add(ir_make_if(IRREL_NEQ, Expression_IR_Generate_Code(expr->rhs), ir_make_immd(0), tmplabel));
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
    assert(Type_Is_Int(expr->valtype));
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
    ir_val dest = ir_make_var(ir_newvar(4));

    _arglist_ir_push(expr->arglist);
    ir_gen_add(ir_make_call(dest, expr->func->name));

    return dest;
}

static ir_val _member_access_ir_gen(Expression *expr) {
    ir_val val_addr = ir_make_var(ir_newvar(4));
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
    ir_val dest = ir_make_var(ir_newvar(4));
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

void Cond_IR_Gen(Expression *expr, size_t label_true, size_t label_false) {
    if (expr->type == EXPR_UNARY_EXPR && expr->uop_type == UOP_NOT) {
        Cond_IR_Gen(expr->rhs, label_false, label_true);
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_AND) {
        size_t tmplabel = ir_newlabel();
        Cond_IR_Gen(expr->lhs, tmplabel, label_false);
        ir_gen_add(ir_make_label(tmplabel));
        Cond_IR_Gen(expr->rhs, label_true, label_false);
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_OR) {
        size_t tmplabel = ir_newlabel();
        Cond_IR_Gen(expr->lhs, label_true, tmplabel);
        ir_gen_add(ir_make_label(tmplabel));
        Cond_IR_Gen(expr->rhs, label_true, label_false);
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_GE) {
        ir_gen_add(ir_make_if(IRREL_GE,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_LE) {
        ir_gen_add(ir_make_if(IRREL_LE,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_GT) {
        ir_gen_add(ir_make_if(IRREL_GT,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_LT) {
        ir_gen_add(ir_make_if(IRREL_LT,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_EQU) {
        ir_gen_add(ir_make_if(IRREL_EQU,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else if (expr->type == EXPR_BINARY_EXPR && expr->bop_type == BOP_NEQ) {
        ir_gen_add(ir_make_if(IRREL_NEQ,
                              Expression_IR_Generate_Code(expr->lhs),
                              Expression_IR_Generate_Code(expr->rhs),
                              label_true));
        ir_gen_add(ir_make_goto(label_false));
    } else {
        ir_gen_add(ir_make_if(IRREL_EQU,
                              Expression_IR_Generate_Code(expr), ir_make_immd(0), label_false));
        ir_gen_add(ir_make_goto(label_true));
    }
}