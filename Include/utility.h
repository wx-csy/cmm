#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdlib.h>

/* append an element to the end of the array */
#define array_append(pointer, size, elem)               \
    do {                                                \
        size_t *psz = &(size);                          \
        typeof(pointer) *pptr = &(pointer);             \
        if ((*psz) & (*psz) - 1) {                      \
        } else if (psz) {                               \
            /* double the size of array */              \
            *pptr = realloc(*pptr, (psz + psz) *        \
                sizeof(**pptr));                        \
        } else {                                        \
            /* the array is empty */                    \
            *pptr = malloc(sizeof(**pptr));             \
        }                                               \
        (*pptr)[*psz] = elem;                           \
        (*psz)++;                                       \
    } while (0) 

#endif
