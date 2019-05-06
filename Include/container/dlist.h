#ifndef __CONTAINER_DLIST_H__
#define __CONTAINER_DLIST_H__

#include "memory.h"

#define declare_dlist_node(tname, tmember)                                  \
    struct tname {                                                          \
        tmember data;                                                       \
        struct tname *prev, *next;                                          \
    }

#define define_dlist(name)                                                  \
    name = {.prev = &name, . next = &name}

#define dlist_init(plist)                                                   \
    ((plist)->next = (plist)->prev = (plist))

#define dlist_foreach(plist, iter)                                          \
    for (typeof(plist) iter = (plist)->next; iter != (plist); iter = iter->next)

#define dlist_insert(plist, elem)                                           \
    do {                                                                    \
        typeof(plist) newnode = palloc(sizeof(*plist));                     \
        newnode->data = elem;                                               \
        newnode->next = (plist);                                            \
        newnode->prev = (plist)->prev;                                      \
        (plist)->prev->next = newnode;                                      \
        (plist)->prev = newnode;                                            \
    } while (0)

#define dlist_erase(plist)                                                  \
    do {                                                                    \
        (plist)->prev->next = (plist)->next;                                \
        (plist)->next->prev = (plist)->prev;                                \
    } while (0)

#endif