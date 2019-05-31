#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "mips.h"
#include "ir.h"
#include "option.h"

StrList mips_output = {
    .data = NULL,
    .prev = &mips_output,
    .next = &mips_output
};

// function value
static size_t func_argsize, func_sp;
static size_t func_retlabel;

static const char *mips_preamble =
    ".data\n"
    "_prompt: .asciiz \"Enter an integer: \"\n"
    "_ret: .asciiz \"\\n\"\n"
    ".globl main\n"
    ".text\n"
    "\n"
    "read:\n"
    "\tli $v0, 4 # syscall: print_string\n"
    "\tla $a0, _prompt\n"
    "\tsyscall\n"
    "\tli $v0, 5 # syscall: read_int\n"
    "\tsyscall\n"
    "\tjr $ra\n"
    "\tnop\n"
    "\n"
    "write:\n"
    "\tli $v0, 1 # syscall: print_int\n"
    "\tlw $a0, 0($sp)\n"
    "\tsyscall\n"
    "\tli $v0, 4 # syscall: print_string\n"
    "\tla $a0, _ret\n"
    "\tsyscall\n"
    "\tmove $v0, $0\n"
    "\taddiu $sp, $sp, 4\n"
    "\tjr $ra\n"
    "\tnop\n"
    "\n"
    ;

void mips_append(const char *fmt, ...)  __attribute__((format(printf, 1, 2)));

void mips_append(const char *fmt, ...) {
    char *instr = pzalloc(256);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(instr, 256, fmt, ap);
    va_end(ap);
    dlist_insert(&mips_output, instr);
}

static void mips_label(size_t label) {
    mips_append("_L%zu:", label);
}

static void mips_pop(size_t dest) {
    func_sp -= 4;
    mips_append("\tlw $%zu, 0($sp)\t# pop", dest);
    mips_append("\taddiu $sp, $sp, 4");
}

static void mips_push(size_t src) {
    func_sp += 4;
    mips_append("\taddiu $sp, $sp, -4\t# push");
    mips_append("\tsw $%zu, 0($sp)", src);
}

static void _ir2mips_getvalue(size_t reg, ir_val val) {
    switch (val.type) {
    case IRVAL_IMMD:
        mips_append("\tli $%zu, %d # immediate number", reg, val.immd);
        break;
    case IRVAL_VARIABLE:
        mips_append("\tlw $%zu, -%zu($fp)", reg, val.varid);
        break;
    case IRVAL_REF:
        mips_append("\taddiu $%zu, $fp, -%zu", reg, val.varid);
        break;
    case IRVAL_DEREF:
        mips_append("\tlw $%zu, -%zu($fp)", reg, val.varid);
        mips_append("\tlw $%zu, 0($%zu)", reg, reg);
        break;
    default: assert(!"unexpected value type");
    }
}

__attribute__((unused))
static void _ir2mips_getaddr(size_t reg, ir_val val)  {
    switch (val.type) {
    case IRVAL_VARIABLE:
        mips_append("\taddiu $%zu, $fp, -%zu", reg, val.varid);
        break;
    case IRVAL_DEREF:
        mips_append("\tlw $%zu, -%zu($fp)", reg, val.varid);
        break;
    default: assert(!"unexpected value type");
    }
}

static void _ir2mips_assignto(size_t reg, ir_val dest) {
    switch (dest.type) {
    case IRVAL_VARIABLE:
        mips_append("\tsw $%zu, -%zu($fp)", reg, dest.varid);
        break;
    case IRVAL_DEREF:
        mips_append("\tlw $24, -%zu($fp)", dest.varid);
        mips_append("\tsw $%zu, 0($24)", reg);
        break;
    default: assert(!"unexpected value type");
    }
}

static void ir2mips_function(const ir_instr *instr) {
    func_argsize = 0;
    func_sp = 0;
    func_retlabel = ir_newlabel();

    mips_append("%s: # function '%s'", instr->func, instr->func);
    mips_push(31);
    mips_push(MIPS_REG_FP);
    mips_append("\taddiu $fp, $sp, 8");
}

static void ir2mips_endfunction(const ir_instr *instr) {
    mips_label(func_retlabel);
    mips_append("\taddiu $sp, $fp, -8");
    mips_pop(MIPS_REG_FP);
    mips_pop(31);
    mips_append("\taddiu $sp, $sp, %zu\t# clear args", func_argsize);
    mips_append("\tjr $31");
    mips_append("\tnop");
    mips_append("%s", "");
}

static void ir2mips_dec(const ir_instr *instr) {
    mips_append("\taddiu $sp, $fp, -%zu\t# dec v%zu", instr->dest.varid, instr->dest.varid);
    func_sp += instr->dec_size;
    // fprintf(stderr, "ir2mips dec : %zu %zu\n", func_sp, instr->dest.varid);
    assert(func_sp == instr->dest.varid);
}

static void ir2mips_param(const ir_instr *instr) {
    mips_append("\tlw $t0, %zu($fp) # param", func_argsize);
    _ir2mips_assignto(MIPS_REG_T0, instr->dest);
    func_argsize += 4;
    // assert(func_argsize == instr->dest.varid - 8);
}

static void ir2mips_label(const ir_instr *instr) {
    mips_label(instr->label);
}

static void ir2mips_assign(const ir_instr *instr) {
    _ir2mips_getvalue(MIPS_REG_T0, instr->src1);
    _ir2mips_assignto(MIPS_REG_T0, instr->dest);
}

static void ir2mips_binary_op(const ir_instr *instr) {
    _ir2mips_getvalue(MIPS_REG_T0, instr->src1);
    _ir2mips_getvalue(MIPS_REG_T1, instr->src2);
    switch (instr->bop) {
    case IRBOP_ADD:
        mips_append("\taddu $8, $8, $9");
        break;
    case IRBOP_MINUS:
        mips_append("\tsubu $8, $8, $9");
        break;
    case IRBOP_STAR:
        mips_append("\tmul $8, $8, $9");
        break;
    case IRBOP_DIV:
        mips_append("\tdiv $8, $9");
        mips_append("\tmflo $8");
        break;
    }
    _ir2mips_assignto(MIPS_REG_T0, instr->dest);
}

static void ir2mips_goto(const ir_instr *instr) {
    mips_append("\tj _L%zu", instr->label);
    mips_append("\tnop");
}

static void ir2mips_if(const ir_instr *instr) {
    _ir2mips_getvalue(MIPS_REG_T0, instr->src1);
    _ir2mips_getvalue(MIPS_REG_T1, instr->src2);
    switch (instr->rop) {
    case IRREL_GT:
        mips_append("\tslt $8, $t1, $t0");
        mips_append("\tbgtz $8, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    case IRREL_LT:
        mips_append("\tslt $8, $t0, $t1");
        mips_append("\tbgtz $8, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    case IRREL_GE:
        mips_append("\tslt $8, $t0, $t1");
        mips_append("\tbeq $8, $0, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    case IRREL_LE:
        mips_append("\tslt $8, $t1, $t0");
        mips_append("\tbeq $8, $0, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    case IRREL_EQU:
        mips_append("\tbeq $t0, $t1, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    case IRREL_NEQ:
        mips_append("\tbne $t0, $t1, _L%zu", instr->label);
        mips_append("\tnop");
        break;
    }

}

static void ir2mips_return(const ir_instr *instr) {
    _ir2mips_getvalue(2, instr->src1);
    mips_append("\tj _L%zu", func_retlabel);
    mips_append("\tnop");
}

static void ir2mips_call(const ir_instr *instr) {
    mips_append("\tjal %s\t# call '%s'", instr->func, instr->func);
    mips_append("\tnop");
    _ir2mips_assignto(2, instr->dest);
}

static void ir2mips_arg(const ir_instr *instr) {
    _ir2mips_getvalue(MIPS_REG_T0, instr->src1);
    mips_push(MIPS_REG_T0);
    func_sp -= 4; // balance stack pointer (decresed by callee)
}

static void (*ir2mips_helper[256])(const ir_instr *instr) = {
    [IRINSTR_FUNCTION] = ir2mips_function,
    [IRINSTR_ENDFUNCTION] = ir2mips_endfunction,
    [IRINSTR_DEC] = ir2mips_dec,
    [IRINSTR_PARAM] = ir2mips_param,
    [IRINSTR_LABEL] = ir2mips_label,
    [IRINSTR_ASSIGN] = ir2mips_assign,
    [IRINSTR_BINARY_OP] = ir2mips_binary_op,
    [IRINSTR_GOTO]      = ir2mips_goto,
    [IRINSTR_IF]      = ir2mips_if,
    [IRINSTR_RETURN]    = ir2mips_return,
    [IRINSTR_CALL] = ir2mips_call,
    [IRINSTR_ARG]       = ir2mips_arg,
};

void ir2mips(IRList *ir_list) {
    dlist_foreach(ir_list, it) {
        if (ir2mips_helper[it->data.type] == NULL) {
            fprintf(stderr, "%d\n", it->data.type);
            assert(0);
        }
        ir2mips_helper[it->data.type](&it->data);
    }
}

void print_mips() {
    fputs(mips_preamble, opt_output_stream);
    dlist_foreach(&mips_output, it) {
        fputs(it->data, opt_output_stream);
        fputc('\n', opt_output_stream);
    }
}