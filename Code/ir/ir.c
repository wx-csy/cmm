#include "ir.h"
#include "symtbl.h"
#include "option.h"
#include "ast/function.h"
#include <stdio.h>
#include <stdarg.h>

size_t ir_nextlabel = 1;
size_t ir_nextval = 0;

size_t ir_newlabel() {
    return ir_nextlabel++;
}

size_t ir_newvar(size_t size) {
    ir_nextval += size;
    ir_gen_add(ir_make_dec(ir_make_var(ir_nextval), size));
    return ir_nextval;
}

#define _IR_COMMENT                                         \
    va_list ap;                                             \
    va_start(ap, fmt);                                      \
    _ir_print_comment(fmt, ap);                             \
    va_end(ap);

ir_val ir_make_immd(int value) {
    ir_val ret = { .type = IRVAL_IMMD, .immd = value };
    return ret;
}

ir_val ir_make_var(size_t varid) {
    ir_val ret = { .type = IRVAL_VARIABLE, .varid = varid };
    return ret;
}

ir_val ir_make_ref(ir_val value) {
    if (value.type == IRVAL_VARIABLE) {
        ir_val ret = {.type = IRVAL_REF, .varid = value.varid};
        return ret;
    } else if (value.type == IRVAL_DEREF) {
        ir_val ret = {.type = IRVAL_VARIABLE, .varid = value.varid};
        return ret;
    } else assert(!"Unsupported value type in make_ref");
}

ir_val ir_make_deref(size_t varid) {
    ir_val ret = { .type = IRVAL_DEREF, .varid = varid };
    return ret;
}

ir_instr ir_make_function(const char *func) {
    ir_instr ret = {.type = IRINSTR_FUNCTION, .func = func};
    return ret;
}

ir_instr ir_make_endfunction(const char *func) {
    ir_instr ret = {.type = IRINSTR_ENDFUNCTION, .func = func};
    return ret;
}

ir_instr ir_make_dec(ir_val declared, size_t size) {
    assert(declared.type == IRVAL_VARIABLE && "DEC instr operand must be variable");
    ir_instr ret = {.type = IRINSTR_DEC, .dest = declared, .dec_size = size};
    return ret;
}

ir_instr ir_make_param(ir_val declared) {
    assert(declared.type == IRVAL_VARIABLE && "PARAM instr operand must be variable");
    ir_instr ret = {.type = IRINSTR_PARAM, .dest = declared};
    return ret;
}

ir_instr ir_make_label(size_t label) {
    ir_instr ret = {.type = IRINSTR_LABEL, .label = label};
    return ret;
}

ir_instr ir_make_assign(ir_val dest, ir_val src) {
    assert(dest.type != IRVAL_REF && dest.type != IRVAL_IMMD && "ASSIGN left operand must be assignable");
    ir_instr ret = {.type = IRINSTR_ASSIGN, .dest = dest, .src1 = src};
    return ret;
}

ir_instr ir_make_binary_op(IRBinaryOperator bop, ir_val dest, ir_val src1, ir_val src2) {
    assert(dest.type != IRVAL_REF && dest.type != IRVAL_IMMD && "BOP left operand must be assignable");
    ir_instr ret = {.type = IRINSTR_BINARY_OP, .bop = bop, .dest = dest, .src1 = src1, .src2 = src2};
    return ret;
}

ir_instr ir_make_goto(size_t label) {
    ir_instr ret = {.type = IRINSTR_GOTO, .label = label};
    return ret;
}

ir_instr ir_make_if(IRRelationalOperator rop, ir_val src1, ir_val src2, size_t label) {
    ir_instr ret = {.type = IRINSTR_IF, .rop = rop, .src1 = src1, .src2 = src2, .label = label};
    return ret;
}

ir_instr ir_make_return(ir_val src) {
    ir_instr ret = {.type = IRINSTR_RETURN, .src1 = src};
    return ret;
}

ir_instr ir_make_call(ir_val dest, const char *func) {
    ir_instr ret = {.type = IRINSTR_CALL, .dest = dest, .func = func};
    return ret;
}

ir_instr ir_make_arg(ir_val src) {
    ir_instr ret = {.type = IRINSTR_ARG, .src1 = src};
    return ret;
}

ir_instr ir_make_read(ir_val dest) {
    ir_instr ret = {.type = IRINSTR_READ, .dest = dest};
    return ret;
}

ir_instr ir_make_write(ir_val src) {
    ir_instr ret = {.type = IRINSTR_WRITE, .src1 = src};
    return ret;
}
