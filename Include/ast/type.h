#ifndef __AST_TYPE_H__
#define __AST_TYPE_H__
#include "common.h"
#include "symtbl.h"
#include "ast/ast.h"
#include "ast/variable.h"

enum TypeCtor {
    TC_INVALID,    // invalid type
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

        // struct type
        struct {
            const char *name;
            cmm_loc_t location;
            VarList varlist;
            symtbl symtable;
        };
    };
} Type;

extern Type Type_Invalid;

static inline bool Type_Is_Basic(Type *type) {
    return type->typector == TC_BASIC;
}

static inline bool Type_Is_Int(Type *type) {
    return Type_Is_Basic(type) && type->basictype == BT_INT;
}

static inline bool Type_Is_Array(Type *type) {
        return type->typector == TC_ARRAY;
}

bool Type_Compatible(Type *type1, Type *type2);
Type *Type_Basic_Constructor(enum BasicType basictype);
Type *Type_Array_Constructor(size_t extent);
void Type_Array_Semantic_Finalize(Type *type);
Type *Type_Struct_Constructor(cmm_loc_t location, const char *name);
void Type_Struct_Semantic_Finalize(Type *type);

#endif
