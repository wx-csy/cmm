#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cmm/error.h>

int cmm_nr_error = 0;

static const char *errmsg[1024] = {
    [CMM_ERROR_UNTERMCOMM]  = "unterminated comment",
    [CMM_ERROR_MYSCHAR]     = "mysterious character '%s'",
    [CMM_ERROR_INVFPLIT]    = "invalid floating-point literal '%s'",
    [CMM_ERROR_INVHEXLIT]   = "invalid hexadecimal literal '%s'",
    [CMM_ERROR_INVOCTLIT]   = "invalid octal literal '%s'",
    [CMM_ERROR_INVDECLIT]   = "invalid decimal literal '%s'",
    [CMM_ERROR_FPLIT_OF]    = "floating-point literal '%s' overflow",
    [CMM_ERROR_INTLIT_OF]   = "integer literal '%s' overflow",

    [CMM_ERROR_SYNTAX]      = "%s",
};

void cmm_error(int cmm_errno, int line, int col, ...) {
    va_list ap;
    cmm_nr_error++;
    fprintf(stderr, "error type %c at line %d, col %d: ", 
        cmm_errno < 256 ? 'A' : 'B', line, col);
    va_start(ap, col);
    vfprintf(stderr, errmsg[cmm_errno], ap);
    va_end(ap);
    fprintf(stderr, "\n");
}
