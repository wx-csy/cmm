/*
 * This is a pool-based memory management library.
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>

void *palloc(size_t size);
void *pzalloc(size_t size);
void *pcalloc(size_t nmemb, size_t size);
void *prealloc(void *ptr, size_t newsize);
char *strpdup(const char *str);

#endif
