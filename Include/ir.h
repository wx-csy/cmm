#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "common.h"
#include "container/dlist.h"

extern size_t ir_nextlabel;
extern size_t ir_nextval;

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
    IRINSTR_NULL,
    IRINSTR_FUNCTION,
    IRINSTR_ENDFUNCTION,
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

ir_val ir_make_immd(int value);
ir_val ir_make_var(size_t varid);
ir_val ir_make_ref(ir_val value);
ir_val ir_make_deref(size_t varid);

ir_instr ir_make_function(const char *func);
ir_instr ir_make_endfunction(const char *func);
ir_instr ir_make_dec(ir_val declared, size_t size);
ir_instr ir_make_param(ir_val declared);
ir_instr ir_make_label(size_t label);
ir_instr ir_make_assign(ir_val dest, ir_val src);
ir_instr ir_make_binary_op(IRBinaryOperator bop, ir_val dest, ir_val src1, ir_val src2);
ir_instr ir_make_goto(size_t label);
ir_instr ir_make_if(IRRelationalOperator rop, ir_val src1, ir_val src2, size_t label);
ir_instr ir_make_return(ir_val src);
ir_instr ir_make_call(ir_val dest, const char *func);
ir_instr ir_make_arg(ir_val src);
ir_instr ir_make_read(ir_val dest);
ir_instr ir_make_write(ir_val src);

typedef declare_dlist_node(IRList, ir_instr) IRList;
extern IRList ir_list;

void ir_gen_add(ir_instr instr);
void ir_gen_add_with_comment(ir_instr instr, const char *fmt, ...);
void ir_gen_output(void);
void ir_optimize(void);

#endif