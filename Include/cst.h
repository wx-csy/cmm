#ifndef __CST_H__
#define __CST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cmm.h"

typedef struct cst_node {
    char *buf;
    int nr_child;
    cmm_loc_t loc;
    struct cst_node **child;
} cst_node_t;

cst_node_t *cst;

static inline cst_node_t
*cst_node_ctor(cmm_loc_t loc, int nr_child, const char *fmt, ...) {
    va_list args1, args2;
    va_start(args1, fmt); va_copy(args2, args1);
    cst_node_t *ret = (cst_node_t *)malloc(sizeof(cst_node_t));
    ret->loc = loc;
    ret->buf = (char *)malloc(1 + vsnprintf(NULL, 0, fmt, args1));
    vsprintf(ret->buf, fmt, args2);
//    printf("[CST_NODE] %s\n", ret->buf);
    ret->nr_child = nr_child;
    ret->child = (struct cst_node **)calloc(nr_child, sizeof(cst_node_t *));
    va_end(args1); va_end(args2);
    return ret;
}

static inline void cst_node_print(cst_node_t *cst, int indent) {
    if (cst == NULL) return; 
    for (int i = 0; i < indent; i++) printf("  ");
    puts(cst->buf);
    for (int i = 0; i < cst->nr_child; i++)
        cst_node_print(cst->child[i], indent + 1);
}

static inline void cst_node_dtor(cst_node_t *cst) {
    if (cst == NULL) return;
    for (int i = 0; i < cst->nr_child; i++) 
        cst_node_dtor(cst->child[i]);
    free(cst->child);
    free(cst->buf);
    free(cst);
}

#endif

