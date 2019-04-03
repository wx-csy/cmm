#define hashmap(t0, t1) \
   _hashmap_T0##_##t0##_T1##_##t1

#include "T0_ccharptr_t_T1_int.inst.hh"

#define hashmap_insert(a0, a1, a2) \
    _Generic((a0) \
        , struct _hashmap_T0_ccharptr_t_T1_int : _hashmap_T0_ccharptr_t_T1_int_insert \
    )(&(a0), (a1), (a2))

#define hashmap_init(a0, a1, a2) \
    _Generic((a0) \
        , struct _hashmap_T0_ccharptr_t_T1_int : _hashmap_T0_ccharptr_t_T1_int_init \
    )(&(a0), (a1), (a2))

#define hashmap_erase(a0, a1) \
    _Generic((a0) \
        , struct _hashmap_T0_ccharptr_t_T1_int : _hashmap_T0_ccharptr_t_T1_int_erase \
    )(&(a0), (a1))

#define hashmap_exist(a0, a1) \
    _Generic((a0) \
        , struct _hashmap_T0_ccharptr_t_T1_int : _hashmap_T0_ccharptr_t_T1_int_exist \
    )(&(a0), (a1))

#define hashmap_free(a0) \
    _Generic((a0) \
        , struct _hashmap_T0_ccharptr_t_T1_int : _hashmap_T0_ccharptr_t_T1_int_free \
    )(&(a0))

