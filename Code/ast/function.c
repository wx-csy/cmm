#include "ast/function.h"

Function *Function_Constructor(const char *name, cmm_loc_t location) {
    Function *ret = pzalloc(sizeof(Function));
    ret->name = strpdup(name);
    ret->location = location;
    return ret;
}
