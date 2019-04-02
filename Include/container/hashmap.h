#ifndef __CONTAINER_DICT_H__
#define __CONTAINER_DICT_H__

#include "common.h"

#define _DICT_SLOT_EMPTY        0       ///< indicate an empty slot
#define _DICT_SLOT_FILLED       1       ///< indicate a slot with content
#define _DICT_SLOT_DELETED      2       ///< indicate a slot used but deleted

#define dict(TKey, TVal)                                                    \
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

/// Get key type of a dictionary.
#define _dict_TKey(dict)        typeof((dict)._data->key)

/// Get value type of a dictionary.
#define _dict_TValue(dict)      typeof((dict)._data->value)

/// Get hash function of a dictionary.
#define _dict_hash(dict)        ((dict)._hash)

/// Get key compare function of a dictionary.
#define _dict_kequal(dict)      ((dict)._kequal)

#define _dict_get_insert_pos(dict, _key)                                    \
    ({                                                                      \
        typeof(dict) *this = &(dict);                                       \
        assert((this->_cap & (this->_cap - 1)) == 0);                       \
        size_t mask = this->_cap - 1;                                       \
        size_t ptr;                                                         \
        for (ptr = _dict_hash(this)((_key)) & mask;                         \
            this->_data[ptr]._tag != _DICT_SLOT_EMPTY;                      \
            ptr = (ptr + 1) & mask);                                        \
        ptr;                                                                \
    })

#define _dict_insert(dict, _key, _value)                                    \
    do {                                                                    \
        typeof(dict) *this = &(dict);                                       \
        size_t ptr = _dict_get_insert_pos(*this, key);                      \
        this->_data[ptr]._tag = _DICT_SLOT_FILLED;                          \
        this->_data[ptr].key = _key;                                        \
        this->_data[ptr].value = _value;                                    \
    } while (0);

#define _dict_foreach(dict, _key, _value)                                   \
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
        this->_cap = 4;                                                     \
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
            _dict_insert(newdict, key, value);                              \
        }                                                                   \
        free(this->_data);                                                  \
        this = newdict;                                                     \
    } while (0)

#define _dict_find(dict, _key)                                              \
    ({                                                                      \
        typeof(dict) newdict, *this = &(dict);                              \
        typeof(_key) key = (_key);                                          \
        assert((this->_cap & (this->_cap - 1)) == 0);                       \
        size_t mask = this->_cap - 1;                                       \
        size_t ptr;                                                         \
        for (ptr = _dict_hash(this)((_key)) & mask;                         \
            this->_data[ptr]._tag == _DICT_SLOT_DELETED ||                  \
            this->_data[ptr]._tag == _DICT_SLOT_FILLED  &&                  \
            _dict_kequal(dict)(key, this->_data[ptr].key)) == 0;            \
            ptr = (ptr + 1) & mask);                                        \
        if (this->_data[ptr]._tag == _DICT_SLOT_EMPTY) ptr = -1;            \
        ptr;                                                                \
    })

#define dict_exist(dict, _key)                                              \
    ({                                                                      \
        typeof(dict) *this = &(dict);                                       \
        typeof(_key) key = (_key);                                          \
        _dict_find(*this, key) >= 0;                                        \
    })

#define dict_find(dict, _key)                                               \
    ({                                                                      \
        typeof(dict) *this = &(dict);                                       \
        typeof(_key) key = (_key);                                          \
        dict->data[_dict_find(*this, key)].value;                           \
    })

#endif
