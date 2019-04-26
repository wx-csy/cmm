#include "cmm.h"
#include "ast/statement.h"
#include "ast/variable.h"
#include "ast/type.h"

Variable Variable_Invalid = {
    .name = "(invalid)",
    .valtype = &Type_Invalid
};

Variable *Variable_Constructor(cmm_loc_t location, const char *name) {
    Variable *ret = pzalloc(sizeof(Variable));
    ret->name = strpdup(name);
    ret->location = location;
    return ret;
}

