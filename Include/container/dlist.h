#ifndef __CONTAINER_DLIST_H__
#define __CONTAINER_DLIST_H__

#include "memory.h"

#define declare_dlist_node(tname, tmember)                      \
    struct tname {                                              \
        struct tname *prev, *next;                              \
        tmember data;                                           \
    }

#define dlist_init(plist, elem)                                 \
    do {                                                        \
        typeof(plist) _plist = (plist);                         \
        _plist->prev = _plist;                                  \
        _plist->next = _plist;                                  \
    } while (0)

#endif
