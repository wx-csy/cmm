#ifndef __CONTAINER_HASHMAP_H__
#define __CONTAINER_HASHMAP_H__

#include "common.h"

#define _HASHMAP_SLOT_EMPTY     0
#define _HASHMAP_SLOT_FILLED    1
#define _HASHMAP_SLOT_DELETED   2

#define hashmap(TKey, TVal)                                                 \
    struct {                                                                \
        size_t (*_hash)(TKey);                                              \
        int (*_kequal)(TKey, TKey);                                         \
        size_t _cap;                                                        \
        size_t _used;                                                       \
        size_t size;                                                        \
        struct {                                                            \
            int _tag;                                                       \
            TKey key;                                                       \
            TVal value;                                                     \
        } *_data;                                                           \
    }                                    


#define _hashmap_TKey(map)        typeof((map)._data->key)

#define _hashmap_TValue(map)      typeof((map)._data->value)

#define _hashmap_hash(map)        ((map)._hash)

#define _hashmap_kequal(map)      ((map)._kequal)

#define _hashmap_get_insert_pos(map, _key)                                  \
    ({                                                                      \
        typeof(map) *this = &(map);                                         \
        assert((this->_cap & (this->_cap - 1)) == 0);                       \
        size_t mask = this->_cap - 1;                                       \
        size_t ptr;                                                         \
        for (ptr = _hashmap_hash(this)((_key)) & mask;                      \
            this->_data[ptr]._tag != _HASHMAP_SLOT_EMPTY;                   \
            ptr = (ptr + 1) & mask);                                        \
        ptr;                                                                \
    })

#define _hashmap_insert(map, _key, _value)                                  \
    do {                                                                    \
        typeof(map) *this = &(map);                                         \
        size_t ptr = _hashmap_get_insert_pos(*this, key);                   \
        this->_data[ptr]._tag = _DICT_SLOT_FILLED;                          \
        this->_data[ptr].key = _key;                                        \
        this->_data[ptr].value = _value;                                    \
    } while (0);

#define _hashmap_foreach(map, _key, _value)                                 \
    for (typeof(dict) *_dict_this = &(dict); _dict_this; _dict_this = NULL) \
        for (size_t _dict_iter = 0; _dict_iter < _dict_this._cap;           \
            _dict_iter++)                                                   \
            if (_dict_this->_data[_dict_iter]._tag == _DICT_SLOT_FILLED &&  \
                ((key) = _dict_this._data[_dict_iter].key,                  \
                 (value) = _dict_this._data[_dict_iter].value, 1))

#define dict_foreach(dict, key, value)                                      \
    _dict_foreach(dict, key, value)

#define dict_initialize(dict, hash, kequal)                                 \
    do {                                                                    \
        typeof(dict) *this = &(dict);                                       \
        this->_hash = hash;                                                 \
        this->_kequal = kequal;                                             \
        this->_cap = 16;                                                    \
        this->_used = 0;                                                    \
        this->size = 0;                                                     \
        this->_data = calloc(this->_cap, sizeof(*this->data));              \
    } while (0)

#define dict_free(dict)                                                     \
    do {                                                                    \
        typeof(dict) *this = &(dict);                                       \
        free(this->_data);                                                  \
    } while (0)


#define _dict_rehash(dict, newcap)                                          \
    do {                                                                    \
        typeof(dict) newdict, *this = &(dict);                              \
        dict_initialize(newdict, this->_hash, this->_kequal);               \
        _dict_TKey key;                                                     \
        _dict_TValue value;                                                 \
        dict_for_each(*this, key, value) {                                  \
            size_t pos = _dict_get_insert_pos(newdict, key);                \
        }                                                                   \
    }

#endif
