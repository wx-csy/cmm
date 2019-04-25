#include "ast/function.h"

Function *Function_Constructor(const char *name, cmm_loc_t location,
    Type *rettype, VarList paramlist, Statement *stmt) {
    Function *ret = palloc(sizeof(Function));
    ret->name = strpdup(name);
    ret->location = location;
    ret->rettype = rettype;
    ret->paramlist = paramlist;
    ret->stmt = stmt;
}
