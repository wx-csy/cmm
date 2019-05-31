#ifndef __MIPS_H__
#define __MIPS_H__

#include "container/dlist.h"
#include "common.h"
#include "ir.h"

/*
 * MIPS register convention
 *
 * reg      usage
 * $0       zero register
 * $1       reserved for assembler
 * $2-$3    return value
 * $4-$7    arguments
 * $8-$15   volatile temporary variables
 * $16-$23  non-volatile temporary variables
 * $24-$25  volatile temporary variables
 * $28      global pointer
 * $29      stack pointer
 * $30      frame pointer
 * $31      return address
 */

#define MIPS_REG_SP 29
#define MIPS_REG_FP 30

#define MIPS_REG_T0 8
#define MIPS_REG_T1 9

/*
 * Calling Convention
 * 1. arguments are pushed from right to left to the stack
 * 2. the callee is responsible for clearing the stack
 */

typedef declare_dlist_node(StrList, char *) StrList;
extern StrList mips_output;
void ir2mips(IRList *ir_list);
void print_mips();

#endif
