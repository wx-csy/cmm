struct _hashmap_@(TYPENAME) {
    size_t (*_hash)(@(TYPENAME));
    int _used;
    size_t size;
    @(TYPENAME) *data;
};

static inline void 
_vector_@(TYPENAME)_push(struct _vector_@(TYPENAME) *vec, @(TYPENAME) elem) {
    if (vec->size == vec->_cap) {
        vec->_cap += vec->_cap;
        vec->data = realloc(vec->data, vec->cap * sizeof(@(TYPENAME)));
    }
    vec->data[vec->size ++] = elem;
}

static inline @(TYPENAME)
_vector_@(TYPENAME)_top(struct _vector_@(TYPENAME) *vec) {
    return vec->data[vec->size - 1];
}

static inline void
_vector_@(TYPENAME)_pop(struct _vector_@(TYPENAME) *vec) {
    vec->size --;
}

static inline void
_vector_@(TYPENAME)_free(struct _vector_@(TYPENAME) *vec) {
    free(vec->data);
    vec->size = vec->cap = 0;
    vec->data = NULL;
}
