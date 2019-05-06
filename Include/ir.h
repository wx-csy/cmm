#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "common.h"
#include "container/dlist.h"

size_t ir_newlabel();
size_t ir_newvar();

typedef enum IRValueType {
    IRVAL_NULL,
    IRVAL_IMMD,
    IRVAL_VARIABLE,
    IRVAL_REF,
    IRVAL_DEREF,
} IRValueType;

typedef struct ir_val {
    IRValueType type;
    union {
        int immd;
        size_t varid;
    };
} ir_val;

typedef enum IRInstrType {
    IRINSTR_FUNCTION,
    IRINSTR_DEC,
    IRINSTR_PARAM,
    IRINSTR_LABEL,
    IRINSTR_ASSIGN,
    IRINSTR_BINARY_OP,
    IRINSTR_GOTO,
    IRINSTR_IF,
    IRINSTR_RETURN,
    IRINSTR_CALL,
    IRINSTR_ARG,
    IRINSTR_READ,
    IRINSTR_WRITE,
} IRInstrType;

typedef enum IRBinaryOperator {
    IRBOP_ADD,
    IRBOP_MINUS,
    IRBOP_STAR,
    IRBOP_DIV,
} IRBinaryOperator;

typedef enum IRRelationalOperator {
    IRREL_GT,
    IRREL_LT,
    IRREL_GE,
    IRREL_LE,
    IRREL_EQU,
    IRREL_NEQ,
} IRRelationalOperator;

typedef struct ir_instr {
    IRInstrType type;
    union {
        IRBinaryOperator bop;
        IRRelationalOperator rop;
    };
    ir_val dest, src1, src2;
    union {
        size_t dec_size;
        size_t label;
        const char *func;
    };
    const char *comment;
} ir_instr;

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

typedef declare_dlist_node(IRList, ir_instr) IRList;
extern IRList ir_list;

void ir_gen_init();
void ir_gen_add(ir_instr instr);
void ir_gen_add_with_comment(ir_instr instr, const char *fmt, ...);
void ir_gen_output(FILE *stream);

#endif