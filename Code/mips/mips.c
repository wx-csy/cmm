#include <stdio.h>
#include <stdarg.h>
#include "mips.h"

StrList mips_output;
static char *stack_alloc_instr;
static size_t varptr;

size_t mips_alloc_label() {
    static size_t next_label = 0;
    return ++next_label;
}

size_t mips_alloc_var(size_t size) {
    if (size & 3) size = (size & ~3) + 4;
    return varptr += size;
}

void mips_append(const char *fmt, ...) {
    char *instr = pzalloc(256);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(instr, 256, fmt, ap);
    va_end(ap);
    dlist_insert(&mips_output, instr);
}

void mips_function_enter(const char *funcname) {
    // reset variable pointer
    // -4$(fp)  last $31
    // -8$(fp)  last $fp
    varptr = 8;

    stack_alloc_instr = pzalloc(256);
    mips_append("%s:\t# function '%s'", funcname, funcname);
    mips_append("move $fp, $sp");
    dlist_insert(&mips_output, stack_alloc_instr);  // addiu $sp, $sp, [TBD]
    mips_append("sw $31, -4($fp)");
    mips_append("sw $fp, -8($fp)");
}

void mips_function_leave() {
    if (varptr & 1) varptr += 1;
    sprintf(stack_alloc_instr, "addiu $sp, $sp, -%zu", varptr);
    mips_append("lw $31, -4($fp)");
    mips_append("move $sp, $fp");
    mips_append("lw $fp, -8($fp)");
    mips_append("jr $31");
    mips_append("nop");
}