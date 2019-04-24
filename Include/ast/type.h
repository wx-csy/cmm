#ifndef __AST_TYPE_H__
#define __AST_TYPE_H__
#include "common.h"

enum TypeCtor {
    TC_BASIC,      // basic type
    TC_ARRAY,      // array of some type
    TC_STRUCT      // struct type
};

enum BasicType {
    BT_INT,
    BT_FLOAT
};

typedef struct Type {
    enum TypeCtor typector;

    size_t width;

    union {
        // basic type
        enum BasicType basictype;

        // array of type;
        struct {
            size_t extent;
            struct Type *underlying;
        };
    };

} Type;

bool Type_Compatible(Type *type1, Type *type2);
Type *Type_Basic_Constructor(enum BasicType basictype);
Type *Type_Array_Constructor(size_t extent, Type *underlying);

#endif
