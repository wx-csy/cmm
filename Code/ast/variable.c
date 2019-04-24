#include "cmm.h"
#include "ast/statement.h"

Variable *
Variable_Constructor(enum VariableType type, Type *valtype) {
    Variable *ret = pzalloc(sizeof(Variable));
    ret->type = type;
    ret->valtype = valtype;
}
