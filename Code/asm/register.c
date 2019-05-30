#include "asm/register.h"

uint32_t asm_free_regs = MIPS_VOLATILE_MASK;

AsmList asm_list = {
    .data = NULL,
    .prev = &asm_list,
    .next = &asm_list
};

size_t asm_allocreg() {
    return 0;
}

void asm_freereg(size_t regid) {

}