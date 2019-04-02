#ifndef __TYPE_H__
#define __TYPE_H__

#include "common.h"

struct type {
    size_t id;
    size_t rank;
    size_t *extent;
};

#endif
