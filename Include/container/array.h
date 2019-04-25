#ifndef __CONTAINER_ARRAY__
#define __CONTAINER_ARRAY__

#include "memory.h"

#define declare_array(tname, tmember)                                       \
    struct tname {                                                          \
        size_t size;                                                        \
        tmember *data;                                                      \
    }

/* append an element to the end of the array */
/*
#define array_append(array, elem)                                           \
    do {                                                                    \
        typeof(array) *parr = &(array);                                     \
        if (parr->size & (parr->size - 1)) {                                \
        } else if (parr->size) {                                            \
            parr->data = prealloc(parr->data,                               \
                (parr->size << 1) * sizeof(*parr->data));                   \
        } else {                                                            \
            parr->data = palloc(sizeof(*parr->data));                       \
        }                                                                   \
        parr->data[parr->size] = elem;                                      \
        parr->size++;                                                       \
    } while (0);
*/

#endif
