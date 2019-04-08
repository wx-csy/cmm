#line 1 "Include/container/vector/impl.h"
#include <stdlib.h>
#include <stdbool.h>

struct _vector_T0_int {
    size_t _cap;
    size_t size;
    int *data;
};

static inline void _vector_T0_int_push(struct _vector_T0_int *this, int elem) {
    if (this->size == this->_cap) {
        this->_cap += this->_cap;
        this->data = realloc(this->data, this->_cap * sizeof(int));
    }
    this->data[this->size ++] = elem;
}

static inline int _vector_T0_int_back(struct _vector_T0_int *this) {
    return this->data[this->size - 1];
}

static inline void _vector_T0_int_pop(struct _vector_T0_int *this) {
    this->size --;
}

static inline void _vector_T0_int_clear(struct _vector_T0_int *this) {
    this->size = 0;
}

static inline void _vector_T0_int_free(struct _vector_T0_int *this) {
    free(this->data);
    this->size = this->_cap = 0;
    this->data = NULL;
}

