#ifndef __CMM_ERROR_H__
#define __CMM_ERROR_H__

enum CMM_ERROR_NO {
    // lexical error
    CMM_ERROR_MYSCHAR       = 1,

    // syntax error
    CMM_ERROR_SYNTAX        = 257,
};

void cmm_error(int cmm_errno, int line, int col, ...);

#endif

