#include "ast/function.h"
#include "ast/type.h"

Function Function_Invalid = {
    .name = "(invalid)",
    .rettype = &Type_Invalid,
    .paramlist = NULL,
    .stmt = NULL
};

Function *Function_Constructor(const char *name, cmm_loc_t location) {
    Function *ret = pzalloc(sizeof(Function));
    ret->name = strpdup(name);
    ret->location = location;
    return ret;
}
