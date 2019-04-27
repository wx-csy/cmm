#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

static struct mempool {
    void *ptr;
    size_t size;
    size_t remain;
    struct mempool *prev;
} *pool = NULL;

#ifdef DEBUG
static size_t poolcnt = 0, tot_size = 0;
#endif

struct memchunk {
    size_t size;
    char data[];
};

#define POOL_SIZE       ((size_t)0x400000)

static void __free() {
    while (pool) {
        free(pool->ptr + pool->remain - pool->size);
        struct mempool *tmp = pool;
        pool = pool->prev;
        free(tmp);
    }
#ifdef DEBUG
    fprintf(stderr, "[memory] a total of %ld pools (%ld bytes) allocated\n", poolcnt, tot_size);
#endif
}

static void __newpool(size_t min_size) {
    size_t size = min_size;
    if (size < POOL_SIZE) size = POOL_SIZE;
#ifdef DEBUG
    fprintf(stderr, "[memory] allocating new pool of size %ld\n", min_size);
    poolcnt++;
    tot_size += size;
#endif
    struct mempool *newpool = calloc(1, sizeof(struct mempool));
    newpool->ptr = malloc(size);
    newpool->size = size;
    newpool->remain = size;
    newpool->prev = pool;
    pool = newpool;
}

static void __init() {
    atexit(__free); // register cleanup function on exit
    __newpool(0);
}

static void *__alloc(size_t size) {
    if (!pool) __init();
    size_t chunk_size = sizeof(struct memchunk) + size;
    if (chunk_size & 7) chunk_size = (chunk_size | 7) + 1;
    if (chunk_size > pool->remain) __newpool(chunk_size);
    struct memchunk *chunk = pool->ptr;
    chunk->size = size;
    pool->remain -= chunk_size;
    pool->ptr += chunk_size;
    return chunk->data;
}

static void *__realloc(void *ptr, size_t newsize) {
    // void pointer arithmetic is a GCC extension
    struct memchunk *chunk = ptr - sizeof(struct memchunk);
    if (chunk->size >= newsize) {
        chunk->size = newsize;
    } else {
        ptr = __alloc(newsize);
        memcpy(ptr, chunk->data, chunk->size);
    }
    return ptr;
}

void *palloc(size_t size) {
    if (size == 0) return NULL;
    return __alloc(size);
}

void *pzalloc(size_t size) {
    if (size == 0) return NULL;
    void *ptr = __alloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void *pcalloc(size_t nmemb, size_t size) {
    return pzalloc(nmemb * size);
}

void *prealloc(void *ptr, size_t newsize) {
    if (!ptr) {
        return __alloc(newsize);
    } else {
        return __realloc(ptr, newsize);
    }
}

char *strpdup(const char *str) {
    char *ret = palloc(strlen(str) + 1);
    strcpy(ret, str);
    return ret;
}
