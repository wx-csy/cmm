#ifndef __ERROR_H__
#define __ERROR_H__

#include "cmm.h"

extern int cmm_nr_error;

enum CMM_ERROR_NO {
    // system error
    CMM_ERROR_FILEERROR         =   1,

    // lexical error
    CMM_ERROR_UNTERMCOMM        = 101,
    CMM_ERROR_MYSCHAR           = 105,
    CMM_ERROR_INVFPLIT          = 111,
    CMM_ERROR_INVHEXLIT         = 112,
    CMM_ERROR_INVOCTLIT         = 113,
    CMM_ERROR_INVDECLIT         = 114,
    CMM_ERROR_FPLIT_OF          = 115,
    CMM_ERROR_INTLIT_OF         = 116,

    // syntax error
    CMM_ERROR_SYNTAX            = 201,
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...);

#endif

