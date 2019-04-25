#include <stdio.h>
#include <stdarg.h>
#include "cmm.h"
#include "error.h"

size_t cmm_nr_error = 0;

static const char *errmsg[65536] = {
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

    [CMM_ERROR_UNDEF_VAR]   = "undefined variable '%s'",
    [CMM_ERROR_UNDEF_FUNC]  = "undefined function '%s'",
    [CMM_ERROR_REDEF_VAR]   = "redefinition of variable '%s'",
    [CMM_ERROR_REDEF_FUNC]  = "redefinition of function '%s'",
    [CMM_ERROR_ASSIGN_TYPE_MISMATCH] = "assignment type mismatch",
    [CMM_ERROR_ASSIGN_TO_LVALUE]  = "assignment to lvalue",
    [CMM_ERROR_OPERAND_TYPE_MISMATCH] = "operand type mismatch",
    [CMM_ERROR_RETURN_TYPE_MISMATCH] = "function return type mismatch",
    [CMM_ERROR_ARG_TYPE_MISMATCH] = "function argument type mismatch",
    [CMM_ERROR_INVSUB]      = "subscription to non-array type",
    [CMM_ERROR_INVCALL]     = "call to non-function object",
    [CMM_ERROR_INVSUBTYPE]  = "subscription type mismatch",
    [CMM_ERROR_MEMBER_NONSTRUCT] = "member access to non-struct type",
    [CMM_ERROR_UNDEF_MEMBER] = "undefined struct member '%s'",
    [CMM_ERROR_REDEF_MEMBER] = "redefition of member '%s'",
    [CMM_ERROR_INIT_MEMBER]  = "initialization within struct not allowed",
    [CMM_ERROR_REDEF_STRUCT] = "redefinition of struct '%s'",
    [CMM_ERROR_UNDEF_STRUCT] = "undefined struct '%s'"
 };

static const char *errfmt[16] = {
    [0]                     = "system error: ",
    [1]                     = "error type A at Line %d:%d: ",
    [2]                     = "error type B at Line %d:%d: ",
    [3]                     = "error type %d at Line %d:%d: ",
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...) {
    va_list ap;
    cmm_nr_error++;
    switch (cmm_errno / 1000) {
    case 0: /* system error */
        fprintf(stderr, errfmt[0]);
        break;
    case 1: /* lexical error */
        fprintf(stderr, errfmt[1], loc.line, loc.col);
        break;
    case 2: /* syntax error */
        fprintf(stderr, errfmt[2], loc.line, loc.col);
        break;
    case 3: /* semantic error */
        fprintf(stderr, errfmt[3], cmm_errno % 1000 / 10, loc.line, loc.col);
        break;
    default:
        assert(0);
    }
    va_start(ap, loc);
    vfprintf(stderr, errmsg[cmm_errno], ap);
    va_end(ap);
    fprintf(stderr, " (E%04d)\n", cmm_errno);
}

