#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "common.h"

/* location type */
typedef struct cmm_loc {
    size_t line, col;
} cmm_loc_t;

#define CMM_LOC_INITIALIZER ((cmm_loc_t) {1, 1})

#endif
