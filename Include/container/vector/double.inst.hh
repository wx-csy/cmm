struct _vector_double {
    size_t _cap;
    size_t size;
    double *data;
};

static inline void 
_vector_double_push(struct _vector_double *vec, double elem) {
    if (vec->size == vec->_cap) {
        vec->_cap += vec->_cap;
        vec->data = realloc(vec->data, vec->cap * sizeof(double));
    }
    vec->data[vec->size ++] = elem;
}

static inline double
_vector_double_top(struct _vector_double *vec) {
    return vec->data[vec->size - 1];
}

static inline void
_vector_double_pop(struct _vector_double *vec) {
    vec->size --;
}

static inline void
_vector_double_free(struct _vector_double *vec) {
    free(vec->data);
    vec->size = vec->cap = 0;
    vec->data = NULL;
}
