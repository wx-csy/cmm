#ifndef __SYMTBL_H__
#define __SYMTBL_H__

struct symtbl_entry {
    const char *name;
    void *item;
};

typedef struct symtbl {
    size_t nr_sym;
    struct symtbl_entry *items;
} symtbl;

/* Initialize a symtbl object. */
void symtbl_init(symtbl *table);

/* Find a member in symtbl. If not found, return NULL. */
void *symtbl_find(symtbl *table, const char *name);

/* Insert an element to symtbl. If name exists, return false. */
bool symtbl_insert(symtbl* table, const char *name, void *item);

/* Erase an element in symtbl. If name does not exist, return false. */
/* Currently, we do not provide this function. */
/*
bool symtbl_erase(symtbl* table, const char *name);
*/

#endif
