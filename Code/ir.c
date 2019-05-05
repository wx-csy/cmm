#include "ir.h"
#include "symtbl.h"
#include "ast/function.h"
#include <stdio.h>
#include <stdarg.h>

size_t ir_newlabel() {
    static size_t nextlabel = 1;
    return nextlabel++;
}

size_t ir_newval() {
    static size_t nextval = 1;
    return nextval++;
}

#define _IR_COMMENT                                         \
    va_list ap;                                             \
    va_start(ap, fmt);                                      \
    _ir_print_comment(fmt, ap);                             \
    va_end(ap);

#define SHOW_COMMENT 1

static void _ir_print_comment(const char *fmt, va_list arglist) {
#if (defined SHOW_COMMENT) && SHOW_COMMENT
    if (fmt) {
        printf("\t; ");
        vprintf(fmt, arglist);
    }
#endif
    printf("\n");
}

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

void ir_emit_function(const char *funcname, const char *fmt, ...) {
    printf("\n");
    /* function name must be mangled */
    printf("FUNCTION _%s : ", funcname);
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
    printf("LABEL l%zu : ", labelid);
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
    printf("    GOTO l%zu ", labelid);
    _IR_COMMENT
}

void ir_emit_if(const char *relop, const char *src1, const char *src2, size_t labelid, const char *fmt, ...) {
    printf("    IF %s %s %s GOTO %zu ", src1, relop, src2, labelid);
    _IR_COMMENT
}

void ir_emit_return(const char *src, const char *fmt, ...) {
    printf("    RETURN %s ", src);
    _IR_COMMENT
}

void ir_emit_call(const char *dest, const char *funcname, const char *fmt, ...) {
    printf("    %s = CALL %s ", dest, funcname);
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

void ir_finalize() {
    Function *funcmain = symtbl_function_find("main", CMM_LOC_INITIALIZER);
    puts("\nFUNCTION main :");
    ir_emit_goto(funcmain->ir_start_label, NULL);
}
