#ifndef __CONTAINER_DLIST_H__
#define __CONTAINER_DLIST_H__

#include "memory.h"
#include "assert.h"

#define declare_dlist_node(tname, tmember)                                  \
    struct tname {                                                          \
        tmember data;                                                       \
        struct tname *prev, *next;                                          \
    }

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

#define dlist_splice(first, second)                                         \
    do {                                                                    \
        typeof(first) p1 = first;                                           \
        typeof(second) p2 = second;                                         \
        p1->prev->next = p2->next;                                          \
        p2->next->prev = p1->prev;                                          \
        p2->prev->next = p1;                                                \
        p1->prev = p2->prev;                                                \
    } while (0)

#define dlist_erase(plist)                                                  \
    do {                                                                    \
        typeof(plist) _plist = (plist);                                     \
        (_plist)->prev->next = (_plist)->next;                              \
        (_plist)->next->prev = (_plist)->prev;                              \
    } while (0)

#endif