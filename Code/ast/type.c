#include "cmm.h"
#include "ast/type.h"

static Type basic_type[256] = {
    [BT_INT] = {
        .typector = TC_BASIC,
        .width = 4,
        .basictype = BT_INT,
    },
    [BT_FLOAT] = {
        .typector = TC_BASIC,
        .width = 4,
        .basictype = BT_FLOAT,
    },
};


bool Type_Compatible(Type *type1, Type *type2) {
    if (type1 == type2) return true;
    if (type1->typector != type2->typector) return false;
    switch (type1->typector) {
    case TC_BASIC:
        return type1->basictype == type2->basictype;
    case TC_ARRAY:
        return Type_Compatible(type1->underlying, type2->underlying);
    case TC_STRUCT:
        assert(!"TODO: implement TC_STRUCT compare");
    }
}

Type *Type_Basic_Constructor(enum BasicType basictype) {
    return &basic_type[basictype];
};


Type *Type_Array_Constructor(size_t extent, Type *underlying) {
    Type *ret = palloc(sizeof(Type));
    ret->typector = TC_ARRAY;
    ret->width = extent * underlying->width;
    ret->extent = extent;
    ret->underlying = underlying;
    return ret;
}

Type *Type_Struct_Constructor(const char *name) {
    Type *ret = pzalloc(sizeof(Type));
    ret->typector = TC_STRUCT;
    ret->width = 0;
    ret->name = strpdup(name);
    return ret;
}

void Type_Struct_Semantic_Check(Type *type) {
    // TODO: Check if any member is initialized
}