#include <stdlib.h>
#include <stdbool.h>

struct @(MANGLE) {
    size_t _cap;
    size_t size;
    @(T) *data;
};

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

