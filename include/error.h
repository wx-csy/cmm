#ifndef __ERROR_H__
#define __ERROR_H__

#include "cmm.h"

extern int cmm_nr_error;

enum CMM_ERROR_NO {
    // lexical error
    CMM_ERROR_UNTERMCOMM        = 1,
    CMM_ERROR_MYSCHAR           = 5,
    CMM_ERROR_INVFPLIT          = 11,
    CMM_ERROR_INVHEXLIT         = 12,
    CMM_ERROR_INVOCTLIT         = 13,
    CMM_ERROR_INVDECLIT         = 14,
    CMM_ERROR_FPLIT_OF          = 15,
    CMM_ERROR_INTLIT_OF         = 16,

    // syntax error
    CMM_ERROR_SYNTAX            = 257,
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...);

#endif

