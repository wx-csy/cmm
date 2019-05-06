#include "ir.h"
#include "symtbl.h"
#include "option.h"
#include "ast/function.h"
#include <stdio.h>
#include <stdarg.h>

size_t ir_newlabel() {
    static size_t nextlabel = 1;
    return nextlabel++;
}

size_t ir_newvar() {
    static size_t nextval = 1;
    return nextval++;
}

#define _IR_COMMENT                                         \
    va_list ap;                                             \
    va_start(ap, fmt);                                      \
    _ir_print_comment(fmt, ap);                             \
    va_end(ap);

// TODO: change ir API to new version
const char *ir_make_immd(int value) {
    char *ret = palloc(32);
    sprintf(ret, "#%d", value);
    return ret;
}

const char *ir_make_var(size_t varid) {
    char *ret = palloc(32);
    sprintf(ret, "v%zu", varid);
    return ret;
}

const char *ir_make_ref(size_t varid) {
    char *ret = palloc(32);
    sprintf(ret, "&v%zu", varid);
    return ret;
}

const char *ir_make_deref(size_t varid) {
    char *ret = palloc(32);
    sprintf(ret, "*v%zu", varid);
    return ret;
}

ir_instr ir_make_function(const char *func) {
    ir_instr ret = {.type = IRINSTR_FUNCTION, .func = func};
    return ret;
}

ir_instr ir_make_dec(ir_val declared, size_t size) {
    assert(declared.type != IRVAL_VARIABLE && "DEC instr operand must be variable");
    ir_instr ret = {.type = IRINSTR_DEC, .dest = declared, .dec_size = size};
    return ret;
}

ir_instr ir_make_param(ir_val declared) {
    assert(declared.type != IRVAL_VARIABLE && "PARAM instr operand must be variable");
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

ir_instr ir_make_call(const char *func) {
    ir_instr ret = {.type = IRINSTR_CALL, .func = func};
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

ir_instr ir_make_write(ir_val dest) {
    ir_instr ret = {.type = IRINSTR_READ, .dest = dest};
    return ret;
}

static void _ir_print_comment(const char *fmt, va_list arglist) {
    if (opt_show_comment) {
        if (fmt) {
            printf("\t; ");
            vprintf(fmt, arglist);
        }
    }
    printf("\n");
}



void ir_emit_function(const char *funcname, const char *fmt, ...) {
    printf("\n");
    /* function name must be mangled */
    printf("FUNCTION %s : ", funcname);
    _IR_COMMENT
}

void ir_emit_dec(size_t varid, size_t size, const char *fmt, ...) {
    if (size != 4) printf("    DEC v%zu %zu ", varid, size);
    _IR_COMMENT
}

void ir_emit_param(size_t varid, const char *fmt, ...) {
    printf("    PARAM v%zu ", varid);
    _IR_COMMENT
}

void ir_emit_label(size_t labelid, const char *fmt, ...) {
    printf("LABEL _L%zu : ", labelid);
    _IR_COMMENT
}

void ir_emit_assign(const char *dest, const char *src, const char *fmt, ...) {
    printf("    %s := %s ", dest, src);
    _IR_COMMENT
}

void ir_emit_binaryop(const char *dest, const char *op, const char *src1, const char *src2, const char *fmt, ...) {
    printf("    %s := %s %s %s ", dest, src1, op, src2);
    _IR_COMMENT
}

void ir_emit_addressof(const char *dest, const char *src, const char *fmt, ...) {
    printf("    %s := &%s ", dest, src);
    _IR_COMMENT
}

void ir_emit_dereference(const char *dest, const char *src, const char *fmt, ...) {
    printf("    %s := *%s ", dest, src);
    _IR_COMMENT
}

void ir_emit_assign_address(const char *dest, const char *src, const char *fmt, ...) {
    printf("    *%s := %s ", dest, src);
    _IR_COMMENT
}

void ir_emit_goto(size_t labelid, const char *fmt, ...) {
    printf("    GOTO _L%zu ", labelid);
    _IR_COMMENT
}

void ir_emit_if(const char *relop, const char *src1, const char *src2, size_t labelid, const char *fmt, ...) {
    printf("    IF %s %s %s GOTO _L%zu ", src1, relop, src2, labelid);
    _IR_COMMENT
}

void ir_emit_return(const char *src, const char *fmt, ...) {
    printf("    RETURN %s ", src);
    _IR_COMMENT
}

void ir_emit_call(const char *dest, const char *funcname, const char *fmt, ...) {
    printf("    %s := CALL %s ", dest, funcname);
    _IR_COMMENT
}

void ir_emit_arg(const char *arg, const char *fmt, ...) {
    printf("    ARG %s ", arg);
    _IR_COMMENT
}

void ir_emit_read(const char * dest, const char *fmt, ...) {
    printf("    READ %s", dest);
    _IR_COMMENT
}

void ir_emit_write(const char *src, const char *fmt, ...) {
    printf("    WRITE %s ", src);
    _IR_COMMENT
}
