#define vector(t0) \
   _vector_T0##_##t0

#include "container/vector/T0_int.inst.hh"

#define vector_push(a0, a1) \
    _Generic((a0) \
        , struct _vector_T0_int: _vector_T0_int_push \
    )(&(a0), (a1))

#define vector_pop(a0) \
    _Generic((a0) \
        , struct _vector_T0_int: _vector_T0_int_pop \
    )(&(a0))

#define vector_clear(a0) \
    _Generic((a0) \
        , struct _vector_T0_int: _vector_T0_int_clear \
    )(&(a0))

#define vector_back(a0) \
    _Generic((a0) \
        , struct _vector_T0_int: _vector_T0_int_back \
    )(&(a0))

#define vector_free(a0) \
    _Generic((a0) \
        , struct _vector_T0_int: _vector_T0_int_free \
    )(&(a0))

