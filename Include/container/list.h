#ifndef __CONTAINER_LIST_H__
#define __CONTAINER_LIST_H__

#include "memory.h"

#define declare_list_node(tname, tmember)                                   \
    struct tname {                                                          \
        tmember data;                                                       \
        struct tname *next;                                                 \
    }

#define list_foreach(list, iter)                                            \
    for (typeof(list) iter = (list); iter; iter = iter->next)

#define list_prepend(plist, elem)                                           \
    do {                                                                    \
        typeof(plist) _plist = (plist);                                     \
        typeof(*_plist) newlist = palloc(sizeof(**_plist));                 \
        newlist->data = elem;                                               \
        newlist->next = *_plist;                                            \
        *_plist = newlist;                                                  \
    } while (0)

// append list2 to list1
#define list_join(plist1, list2)                                            \
    do {                                                                    \
        typeof(plist1) _plist = (plist1);                                   \
        while (*_plist) _plist = &((*_plist)->next);                        \
        *_plist = list2;                                                    \
    } while (0)
#endif
