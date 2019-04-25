#include "cmm.h"
#include "ast/statement.h"

Variable *Variable_Constructor(const char *name, Type *valtype) {
    Variable *ret = pzalloc(sizeof(Variable));
    ret->name = strpdup(name);
    ret->valtype = valtype;
}
