#include "container/vector/int.inst.hh"
#include "container/vector/double.inst.hh"

#define vector_push(a0, a1) \
    _Generic((a0), \
        int: _vector_int_push, \
        double: _vector_double_push, \
    )(a0, a1)

#define vector_clear(a0) \
    _Generic((a0), \
        int: _vector_int_clear, \
        double: _vector_double_clear, \
    )(a0)

