#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "utility.h"
#include "oop.h"

typedef char *charptr_t;
typedef const char *ccharptr_t;

static inline size_t strhash(const char* str) {
    size_t ret = 55834;
    while (*str) {
        ret += (ret << 5) + (unsigned char)(*str);
        str++;
    }
    return ret;
}

#endif
