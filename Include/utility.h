#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdlib.h>
#include "memory.h"

/* swap two lvalues */
#define swap(a, b)                                      \
    do {                                                \
        typeof(a) temp = a;                             \
        a = b;                                          \
        b = temp;                                       \
    } while(0);
#endif
