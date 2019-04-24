#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdlib.h>
#include "memory.h"

/* append an element to the end of the array */
#define array_append(pointer, size, elem)               \
    do {                                                \
        size_t *psz = &(size), sz = *psz;               \
        typeof(pointer) *pptr = &(pointer);             \
        if (sz & sz - 1) {                              \
        } else if (sz) {                                \
            /* double the size of array */              \
            *pptr = prealloc(*pptr, (sz + sz) *         \
                sizeof(**pptr));                        \
        } else {                                        \
            /* the array is empty */                    \
            *pptr = palloc(sizeof(**pptr));             \
        }                                               \
        (*pptr)[*psz] = elem;                           \
        (*psz)++;                                       \
    } while (0) 

/* swap two lvalues */
#define swap(a, b)                                      \
    do {                                                \
        typeof(a) temp = a;                             \
        a = b;                                          \
        b = temp;                                       \
    } while(0);
#endif
