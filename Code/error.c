#include <stdio.h>
#include <stdarg.h>
#include "cmm.h"
#include "error.h"

size_t cmm_nr_error = 0;

static const char *errmsg[1024] = {
    [CMM_ERROR_FILEERROR]   = "unable to open file '%s'",

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

static const char *errfmt[16] = {
    [0]                     = "system error: ",
    [1]                     = "error type A at line %d, col %d: ",
    [2]                     = "error type B at line %d, col %d: ",
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...) {
    va_list ap;
    cmm_nr_error++;
    fprintf(stderr, errfmt[cmm_errno / 100], loc.line, loc.col);
    va_start(ap, loc);
    vfprintf(stderr, errmsg[cmm_errno], ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

