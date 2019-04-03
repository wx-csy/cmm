#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct @(MANGLE) {
    size_t (*_hash)(@(TKey));
    bool (*_kcmp)(@(TKey), @(TKey));
    size_t _cap;
    size_t _used;
    size_t size;
    struct {
        int tag;
        @(TKey) key;
        @(TVal) value;
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
            this->_kcmp(this->_data[ptr].key, key))
            return ptr;
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
    newmap._hash = this->_hash;
    newmap._kcmp = this->_kcmp;
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
    *this = newmap;
}

static inline void 
@(MANGLE)_init(struct @(MANGLE) *this, size_t (*hash)(@(TKey)), bool (*kcmp)(@(TKey), @(TKey))) {
    this->_hash = hash;
    this->_kcmp = kcmp;
    this->_cap = 16;
    this->_used = 0;
    this->size = 0;
    this->_data = calloc(this->_cap, sizeof(*this->_data));
}

static inline bool @(MANGLE)_exist(struct @(MANGLE) *this, @(TKey) key) {
    size_t pos = _@(MANGLE)_find(this, key);
    return this->_data[pos].tag == _HASHMAP_SLOT_FILLED;
}

static inline @(TVal) @(MANGLE)_get(struct @(MANGLE) *this, @(TKey) key) {
    size_t pos = _@(MANGLE)_find(this, key);
    return this->_data[pos].value;
}

static inline void @(MANGLE)_insert(struct @(MANGLE) *this, @(TKey) key, @(TVal) value) {
    if (this->_used + (this->_used >> 1) >= this->_cap || (this->size << 1) >= this->_cap) {
        size_t newsize = this->_cap;
        if ((this->size << 1) >= this->_cap) newsize += this->_cap;
        _@(MANGLE)_rehash(this, newsize);
    }
    _@(MANGLE)_insert(this, key, value);
}

static inline void @(MANGLE)_erase(struct @(MANGLE) *this, @(TKey) key) {
    size_t pos = _@(MANGLE)_find(this, key);
    if (this->_data[pos].tag == _HASHMAP_SLOT_FILLED) {
        this->_data[pos].tag = _HASHMAP_SLOT_DELETED;
        this->size --;
    }
}

static inline void @(MANGLE)_free(struct @(MANGLE) *this) {
    free(this->_data);
    this->size = this->_cap = this->_used = 0;
    this->_data = NULL;
}

