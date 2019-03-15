#ifndef __CMM_ERROR_H__
#define __CMM_ERROR_H__

enum CMM_ERROR_NO {
    CMM_ERROR_MYSCHAR       = 1
};

void cmm_error(int cmm_errno, int line, int col, ...);

#endif

