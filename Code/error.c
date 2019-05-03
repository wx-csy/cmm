#include <stdio.h>
#include <stdarg.h>
#include "cmm.h"
#include "error.h"

size_t cmm_nr_error = 0;

static const char *errmsg[65536] = {
    [CMM_ERROR_FILEERROR]   = "cannot open file '%s'",

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
    [CMM_ERROR_UNDEF_FUNC]  = "undeclared function '%s'",
    [CMM_ERROR_REDEF_VAR]   = "duplicated definition of '%s' when defining as variable",
    [CMM_ERROR_REDEF_FUNC]  = "duplicated definition of '%s' when declaring as function",
    [CMM_ERROR_ASSIGN_TYPE_MISMATCH] = "assignment type mismatch",
    [CMM_ERROR_INIT_TYPE_MISMATCH] = "type mismatch in initializer",
    [CMM_ERROR_ASSIGN_TO_RVALUE]  = "lvalue required as left operand of assignment",
    [CMM_ERROR_OPERAND_TYPE_MISMATCH] = "operand type mismatch",
    [CMM_ERROR_IF_TYPE_MISMATCH] = "if condition must be integer",
    [CMM_ERROR_WHILE_TYPE_MISMATCH] = "while condition must be integer",
    [CMM_ERROR_RETURN_TYPE_MISMATCH] = "function return type mismatch",
    [CMM_ERROR_ARG_TYPE_MISMATCH] = "function argument type mismatch",
    [CMM_ERROR_ARG_NUMBER_MISMATCH] = "function argument number mismatch",
    [CMM_ERROR_INVSUB]      = "subscript to non-array type",
    [CMM_ERROR_INVCALL]     = "undeclared function '%s' (maybe misdefined as variable?)",
    [CMM_ERROR_INVSUBTYPE]  = "array subscript is not an integer",
    [CMM_ERROR_MEMBER_NONSTRUCT] = "member access of non-struct type",
    [CMM_ERROR_UNDEF_MEMBER] = "'struct %s' has no member named '%s'",
    [CMM_ERROR_REDEF_MEMBER] = "duplicated definition of '%s' when defining as member",
    [CMM_ERROR_INIT_MEMBER]  = "initialization within struct not allowed",
    [CMM_ERROR_REDEF_STRUCT] = "duplicated definition of 'struct %s' when defining as struct",
    [CMM_ERROR_UNDEF_STRUCT] = "undefined 'struct %s'",

    [CMM_ERROR_DECFUNC_UNDEF] = "function '%s' declared but not defined",
    [CMM_ERROR_FUNC_DEC_MISMATCH] = "incompatible function declaration of '%s' with previous one",
};

static const char *errfmt[16] = {
    [0]                     = "system error: ",
    [1]                     = "error type A at Line %d, Col %d: ",
    [2]                     = "error type B at Line %d, Col %d: ",
    [3]                     = "error type %d at Line %d, Col %d: ",
};

void cmm_error(int cmm_errno, cmm_loc_t loc, ...) {
    va_list ap;
    cmm_nr_error++;
    switch (cmm_errno / 1000) {
    case 0: /* system error */
        fputs(errfmt[0], stderr);
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

