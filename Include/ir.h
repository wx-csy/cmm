#ifndef __IR_H__
#define __IR_H__

#include "common.h"

size_t ir_newlabel();
size_t ir_newval();

int ir_printf(const char *format, ...);
void ir_print_function(const char *funcname);
#endif