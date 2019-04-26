#ifndef __ERROR_H__
#define __ERROR_H__

#include "common.h"
#include "location.h"

extern size_t cmm_nr_error;

enum CMM_ERROR_NO {
    // system error
    CMM_ERROR_FILEERROR         = 0001,

    // lexical error
    CMM_ERROR_UNTERMCOMM        = 1010,
    CMM_ERROR_MYSCHAR           = 1050,
    CMM_ERROR_INVFPLIT          = 1110,
    CMM_ERROR_INVHEXLIT         = 1120,
    CMM_ERROR_INVOCTLIT         = 1130,
    CMM_ERROR_INVDECLIT         = 1140,
    CMM_ERROR_FPLIT_OF          = 1150,
    CMM_ERROR_INTLIT_OF         = 1160,

    // syntax error
    CMM_ERROR_SYNTAX            = 2010,

    // semantic error
    CMM_ERROR_UNDEF_VAR     = 3010,
    CMM_ERROR_UNDEF_FUNC    = 3020,
    CMM_ERROR_REDEF_VAR     = 3030,
    CMM_ERROR_REDEF_FUNC    = 3040,
    CMM_ERROR_ASSIGN_TYPE_MISMATCH  = 3050,
    CMM_ERROR_ASSIGN_TO_RVALUE  = 3060,
    CMM_ERROR_OPERAND_TYPE_MISMATCH = 3070,
    CMM_ERROR_RETURN_TYPE_MISMATCH = 3080,
    CMM_ERROR_ARG_TYPE_MISMATCH = 3090,
    CMM_ERROR_ARG_NUMBER_MISMATCH = 3091,
    CMM_ERROR_INVSUB        = 3100,
    CMM_ERROR_INVCALL       = 3110,
    CMM_ERROR_INVSUBTYPE    = 3120,
    CMM_ERROR_MEMBER_NONSTRUCT  = 3130,
    CMM_ERROR_UNDEF_MEMBER  = 3140,
    CMM_ERROR_REDEF_MEMBER  = 3150,
    CMM_ERROR_INIT_MEMBER   = 3151,
    CMM_ERROR_REDEF_STRUCT  = 3160,
    CMM_ERROR_UNDEF_STRUCT  = 3170,
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...);

#endif

