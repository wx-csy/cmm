#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cmm/error.h>

static const char *errmsg[256] = {
    [CMM_ERROR_MYSCHAR] = "mysterious character '%s'",
};

void cmm_error(int cmm_errno, int line, int col, ...) {
    va_list ap;
    fprintf(stderr, "error type %c at line %d, col %d: ", 
        cmm_errno < 256 ? 'A' : 'B', line, col);
    va_start(ap, col);
    vfprintf(stderr, errmsg[cmm_errno], ap);
    va_end(ap);
    fprintf(stderr, "\n");
}
