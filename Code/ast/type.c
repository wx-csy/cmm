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

Type Type_Invalid = { .typector = TC_INVALID };

bool Type_Compatible(Type *type1, Type *type2) {
    if (type1 == type2) return true;
    if (type1->typector == TC_INVALID || type2->typector == TC_INVALID)
        return true;
    if (type1->typector != type2->typector) return false;
    switch (type1->typector) {
    case TC_BASIC:
        return type1->basictype == type2->basictype;
    case TC_ARRAY:
        return Type_Compatible(type1->underlying, type2->underlying) && type1->extent == type2->extent;
    case TC_STRUCT:
        return type1 == type2;
        // structural equivalence (memberwise equivalence)
        /*
        {
            VarList list1 = type1->varlist, list2 = type2->varlist;
            for (; list1 && list2; list1 = list1->next, list2 = list2->next)
                if (!Type_Compatible(list1->data->valtype, list2->data->valtype))
                    return false;
            if (list1 || list2) return false;
            return true;
        }
         */
    default:
        assert(0);
    }
}

Type *Type_Basic_Constructor(enum BasicType basictype) {
    return &basic_type[basictype];
}


Type *Type_Array_Constructor(size_t extent) {
    Type *ret = palloc(sizeof(Type));
    ret->typector = TC_ARRAY;
    ret->extent = extent;
    return ret;
}

void Type_Array_Semantic_Finalize(Type *type) {
    if (type->typector != TC_ARRAY) return;
    Type_Array_Semantic_Finalize(type->underlying);
    type->width = type->extent * type->underlying->width;
}

Type *Type_Struct_Constructor(cmm_loc_t location, const char *name) {
    Type *ret = pzalloc(sizeof(Type));
    ret->typector = TC_STRUCT;
    ret->width = 0;
    ret->name = strpdup(name);
    ret->location = location;
    return ret;
}

void Type_Struct_Semantic_Finalize(Type *type) {
    assert(type->typector == TC_STRUCT);
    type->width = 0;
    for (VarList_node *node = type->varlist; node; node = node->next) {
        if (node->data->initializer)
            cmm_error(CMM_ERROR_INIT_MEMBER, node->data->location);
        node->data->offset = type->width;
        type->width += node->data->valtype->width;
    }
}