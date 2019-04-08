#ifndef __AST_TYPE_H__
#define __AST_TYPE_H__
#include "common.h"

typedef struct Type {
    size_t id;
    const char *name;
    size_t size;
} Type;

#endif
