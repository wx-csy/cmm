#line 1 "Include/container/hashmap/impl.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct _hashmap_T0_ccharptr_t_T1_int {
    size_t (*_hash)(ccharptr_t);
    bool (*_kcmp)(ccharptr_t, ccharptr_t);
    size_t _cap;
    size_t _used;
    size_t size;
    struct {
        int tag;
        ccharptr_t key;
        int value;
    } *_data;
};

static inline void _hashmap_T0_ccharptr_t_T1_int_foreach(struct _hashmap_T0_ccharptr_t_T1_int *this, int (*trav)(ccharptr_t, int)) {
    for (size_t i = 0; i < this->_cap; i++)
        if (this->_data[i].tag == _HASHMAP_SLOT_FILLED)
            if (trav(this->_data[i].key, this->_data[i].value))
                break;
}

static inline size_t __hashmap_T0_ccharptr_t_T1_int_find(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key) {
    size_t mask = this->_cap - 1;
    assert((mask & (mask + 1)) == 0);
    for (size_t ptr = this->_hash(key) & mask; ; ptr = (ptr + 1) & mask) {
        if (this->_data[ptr].tag == _HASHMAP_SLOT_EMPTY) 
            return ptr;
        if (this->_data[ptr].tag == _HASHMAP_SLOT_FILLED &&
            this->_kcmp(this->_data[ptr].key, key))
            return ptr;
    }
}

static inline void __hashmap_T0_ccharptr_t_T1_int_insert(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key, int value) {
    size_t pos = __hashmap_T0_ccharptr_t_T1_int_find(this, key);
    this->_data[pos].key = key;
    this->_data[pos].value = value;
    this->_data[pos].tag = _HASHMAP_SLOT_FILLED;
    this->_used++;
    this->size++;
}

static inline void __hashmap_T0_ccharptr_t_T1_int_rehash(struct _hashmap_T0_ccharptr_t_T1_int *this, size_t newcap) {
    struct _hashmap_T0_ccharptr_t_T1_int newmap;
    newmap._hash = this->_hash;
    newmap._kcmp = this->_kcmp;
    newmap._cap = newcap;
    newmap._used = 0;
    newmap.size = 0;
    newmap._data = calloc(newcap, sizeof(*newmap._data));
    int insert_kvp(ccharptr_t key, int value) {
        __hashmap_T0_ccharptr_t_T1_int_insert(&newmap, key, value);
        return 0;
    }
    _hashmap_T0_ccharptr_t_T1_int_foreach(this, insert_kvp);
    free(this->_data);
    *this = newmap;
}

static inline void 
_hashmap_T0_ccharptr_t_T1_int_init(struct _hashmap_T0_ccharptr_t_T1_int *this, size_t (*hash)(ccharptr_t), bool (*kcmp)(ccharptr_t, ccharptr_t)) {
    this->_hash = hash;
    this->_kcmp = kcmp;
    this->_cap = 16;
    this->_used = 0;
    this->size = 0;
    this->_data = calloc(this->_cap, sizeof(*this->_data));
}

static inline bool _hashmap_T0_ccharptr_t_T1_int_exist(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key) {
    size_t pos = __hashmap_T0_ccharptr_t_T1_int_find(this, key);
    return this->_data[pos].tag == _HASHMAP_SLOT_FILLED;
}

static inline int _hashmap_T0_ccharptr_t_T1_int_get(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key) {
    size_t pos = __hashmap_T0_ccharptr_t_T1_int_find(this, key);
    return this->_data[pos].value;
}

static inline void _hashmap_T0_ccharptr_t_T1_int_insert(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key, int value) {
    if (this->_used + (this->_used >> 1) >= this->_cap || (this->size << 1) >= this->_cap) {
        size_t newsize = this->_cap;
        if ((this->size << 1) >= this->_cap) newsize += this->_cap;
        __hashmap_T0_ccharptr_t_T1_int_rehash(this, newsize);
    }
    __hashmap_T0_ccharptr_t_T1_int_insert(this, key, value);
}

static inline void _hashmap_T0_ccharptr_t_T1_int_erase(struct _hashmap_T0_ccharptr_t_T1_int *this, ccharptr_t key) {
    size_t pos = __hashmap_T0_ccharptr_t_T1_int_find(this, key);
    if (this->_data[pos].tag == _HASHMAP_SLOT_FILLED) {
        this->_data[pos].tag = _HASHMAP_SLOT_DELETED;
        this->size --;
    }
}

static inline void _hashmap_T0_ccharptr_t_T1_int_free(struct _hashmap_T0_ccharptr_t_T1_int *this) {
    free(this->_data);
    this->size = this->_cap = this->_used = 0;
    this->_data = NULL;
}

