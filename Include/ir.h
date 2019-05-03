#ifndef __IR_H__
#define __IR_H__

#include "common.h"

size_t ir_newlabel();
size_t ir_newval();

const char *ir_make_immd(int value);
const char *ir_make_var(size_t varid);
const char *ir_make_ref(size_t varid);
const char *ir_make_deref(size_t varid);

void ir_emit_function(const char *funcname, const char *fmt, ...);
void ir_emit_dec(size_t varid, size_t size, const char *fmt, ...);
void ir_emit_param(size_t varid, const char *fmt, ...);
void ir_emit_label(size_t labelid, const char *fmt, ...);
void ir_emit_assign(const char *dest, const char *src, const char *fmt, ...);
void ir_emit_binaryop(const char *dest, const char *op, const char *src1, const char *src2, const char *fmt, ...);
void ir_emit_addressof(const char *dest, const char *src, const char *fmt, ...);
void ir_emit_dereference(const char *dest, const char *src, const char *fmt, ...);
void ir_emit_assign_address(const char *dest, const char *src, const char *fmt, ...);
void ir_emit_goto(size_t labelid, const char *fmt, ...);
void ir_emit_if(const char *relop, const char *src1, const char *src2, size_t labelid, const char *fmt, ...);
void ir_emit_return(const char *src, const char *fmt, ...);
void ir_emit_call(const char *dest, const char *funcname, const char *fmt, ...);
void ir_emit_arg(const char *arg, const char *fmt, ...);
void ir_emit_read(const char *dest, const char *fmt, ...);
void ir_emit_write(const char *src, const char *fmt, ...);

#endif