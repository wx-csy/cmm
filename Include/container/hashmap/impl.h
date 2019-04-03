#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct @(MANGLE) {
    size_t (*_hash)(@(TKey));
    int (*_kcmp)(@(TKey), @(TKey));
    size_t _cap;
    size_t _used;
    size_t size;
    struct {
        int tag;
        @(TKey) key;
        @(TValue) value;
    } *_data;
};

static inline void @(MANGLE)_foreach(struct @(MANGLE) *this, int (*trav)(@(TKey), @(TVal))) {
    for (size_t i = 0; i < this->_cap; i++)
        if (this->_data[i].tag == _HASHMAP_SLOT_FILLED)
            if (trav(this->_data[i].key, this->_data[i].value))
                break;
}

static inline size_t _@(MANGLE)_find(struct @(MANGLE) *this, @(TKey) key) {
    size_t mask = this->_cap - 1;
    assert((mask & (mask + 1)) == 0);
    for (size_t ptr = this->_hash(key) & mask; ; ptr = (ptr + 1) & mask) {
        if (this->_data[ptr].tag == _HASHMAP_SLOT_EMPTY) 
            return ptr;
        if (this->_data[ptr].tag == _HASHMAP_SLOT_FILLED &&
            this->_hash(this->_data[ptr].key, key) == 0)
            return ptr
    }
}

static inline void _@(MANGLE)_insert(struct @(MANGLE) *this, @(TKey) key, @(TVal) value) {
    size_t pos = _@(MANGLE)_find(this, key);
    this->_data[pos].key = key;
    this->_data[pos].value = value;
    this->_data[pos].tag = _HASHMAP_SLOT_FILLED;
    this->_used++;
    this->size++;
}

static inline void _@(MANGLE)_rehash(struct @(MANGLE) *this, size_t newcap) {
    struct @(MANGLE) newmap;
    newmap._cap = newcap;
    newmap._used = 0;
    newmap.size = 0;
    newmap._data = calloc(newcap, sizeof(*newmap._data));
    int insert_kvp(@(TKey) key, @(TVal) value) {
        _@(MANGLE)_insert(&newmap, key, value);
        return 0;
    }
    @(MANGLE)_foreach(this, insert_kvp);
    free(this->_data);
    *this = newmap
}

static inline void @(MANGLE)_push(struct @(MANGLE) *this, @(T) elem) {
    if (this->size == this->_cap) {
        this->_cap += this->_cap;
        this->data = realloc(this->data, this->_cap * sizeof(@(T)));
    }
    this->data[this->size ++] = elem;
}

static inline @(T) @(MANGLE)_back(struct @(MANGLE) *this) {
    return this->data[this->size - 1];
}

static inline void @(MANGLE)_pop(struct @(MANGLE) *this) {
    this->size --;
}

static inline void @(MANGLE)_clear(struct @(MANGLE) *this) {
    this->size = 0;
}

static inline void @(MANGLE)_free(struct @(MANGLE) *this) {
    free(this->data);
    this->size = this->_cap = 0;
    this->data = NULL;
}

