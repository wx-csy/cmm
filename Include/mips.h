#ifndef __MIPS_H__
#define __MIPS_H__

#include "container/dlist.h"
#include "common.h"

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

typedef declare_dlist_node(StrList, char *) StrList;
extern StrList mips_output;

size_t mips_alloc_label();
void mips_function_enter();
void mips_append(const char *fmt, ...);
void mips_function_leave();

#endif
