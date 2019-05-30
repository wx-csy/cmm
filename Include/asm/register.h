#ifndef __ASM_REGISTER_H__
#define __ASM_REGISTER_H__

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

#define MIPS_VOLATILE_MASK  ((uint32_t)(0x00ffff00))

extern uint32_t asm_free_regs;

size_t asm_allocreg();

void asm_freereg(size_t regid);

void asm_precall();

void asm_postcall();

void asm_enter();

void asm_leave();

typedef declare_dlist_node(AsmList, const char *) AsmList;
extern AsmList asm_list;

#endif //CMM_REGISTER_H
