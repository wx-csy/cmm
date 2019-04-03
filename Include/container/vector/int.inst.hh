struct _vector_int {
    size_t _cap;
    size_t size;
    int *data;
};

static inline void 
_vector_int_push(struct _vector_int *vec, int elem) {
    if (vec->size == vec->_cap) {
        vec->_cap += vec->_cap;
        vec->data = realloc(vec->data, vec->cap * sizeof(int));
    }
    vec->data[vec->size ++] = elem;
}

static inline int
_vector_int_top(struct _vector_int *vec) {
    return vec->data[vec->size - 1];
}

static inline void
_vector_int_pop(struct _vector_int *vec) {
    vec->size --;
}

static inline void
_vector_int_free(struct _vector_int *vec) {
    free(vec->data);
    vec->size = vec->cap = 0;
    vec->data = NULL;
}
