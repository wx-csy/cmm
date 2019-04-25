#ifndef __CONTAINER_LIST__
#define __CONTAINER_LIST__

#include "memory.h"

#define declare_list_node(tname, tmember)                                        \
    struct tname {                                                          \
        tmember data;                                                       \
        struct tname *next;                                                 \
    }

#define list_prepend(plist, elem)                                           \
    do {                                                                    \
        typeof(plist) _plist = (plist);                                     \
        typeof(*_plist) newlist = palloc(sizeof(**_plist));                 \
        newlist->data = elem;                                               \
        newlist->next = *_plist;                                            \
        *_plist = newlist;                                                  \
    } while (0)

// append list2 to list1
#define list_join(list1, list2)                                             \
    do {                                                                    \
        typeof(list) *plist = &(list1);                                     \
        while (*plist) plist = &(*plist->next);                             \
        *plist = &(list2);                                                  \
    } while (0)
#endif
