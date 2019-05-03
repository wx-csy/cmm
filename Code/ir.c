#include "ir.h"
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

int ir_printf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    printf("    ");
    int ret = vprintf(format, ap);
    va_end(ap);
    return ret;
}

void ir_print_function(const char *funcname) {
    printf("\n");
    /* function name must be mangled */
    printf("FUNCTION _%s :\n", funcname);
}