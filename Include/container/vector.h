#ifndef __CONTAINER_VECTOR_H__
#define __CONTAINER_VECTOR_H__

#include "common.h"

#define vector(T)                                                   \
    struct {                                                        \
        size_t _cap;                                                \
        size_t size;                                                \
        T *data;                                                    \
    }                                    

#define vector_initializer()                                        \
    { 0, 0, NULL }

#define vector_push(vec, elem)                                      \
    do {                                                            \
        typeof(vec) *this = &(vec);                                 \
        if (this->size == this->_cap) {                             \
            this->_cap += this->_cap;                               \
            this->data = realloc(this->data,                        \
                this->cap * sizeof(*this->data));                   \
        }                                                           \
        this->data[this.size ++] = (elem);                          \
    } while (0)

#define vector_top(vec)                                             \
    ({ typeof(vec) *this = &(vec); this->data[this->size - 1]; })   \

#define vector_pop(vec)                                             \
    do {                                                            \
        typeof(vec) *this = &(vec);                                 \
        this->size --;                                              \
        if (this->_Tdtor) this->_Tdtor(this->data[this->size]);     \
    while (0);

#define vector_clear(vec)                                           \
    do {                                                            \
        typeof(vec) *this = &(vec);                                 \
        if (this->_Tdtor) {                                         \
            for (size_t i = this->size; i; i--)                     \
                this->Tdtor(this->data[i - 1]);                     \
        }                                                           \
        this->size = 0;                                             \
    } while (0)

#define vector_clear(vec)                                           \
    do {                                                            \
        typeof(vec) *this = &(vec);                                 \
        if (this->_Tdtor) {                                         \
            for (size_t i = this->size; i; i--)                     \
                this->Tdtor(this->data[i - 1]);                     \
        }                                                           \
        this.size = 0;                                              \
        free(this->data);                                           \
    } while (0)

#endif
