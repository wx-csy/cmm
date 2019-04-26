#include "ast/ast.h"
#include "cmm.h"

Program *Program_Constructor(FuncList funclist, VarList varlist) {
    Program *ret = palloc(sizeof(Program));
    ret->funclist = funclist;
    ret->varlist = varlist;
    return ret;
}