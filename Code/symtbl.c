#include <string.h>
#include "cmm.h"
#include "symtbl.h"

void symtbl_init(symtbl *table) {
    memset(table, 0, sizeof(*table));
}

void *symtbl_find(symtbl *table, const char *name) {
    for (size_t i = 0; i < table->nr_sym; i++)
        if (strcmp(table->items[i].name, name) == 0)
            return table->items[i].item;
    return NULL;
};

bool symtbl_insert(symtbl* table, const char *name, void *item) {
    if (symtbl_find(table, name)) return false;
    struct symtbl_entry entry = {strpdup(name), item};
    array_append(table->items, table->nr_sym, entry);
    return true;
}

/*
bool symtbl_erase(symtbl* table, const char *name) {
    for (size_t i = 0; i < table->nr_sym; i++)
        if (strcmp(table->items[i].name, name) == 0) {
            swap(table->items[i], table->items[table->nr_sym - 1]);
            table->nr_sym--;
            return true;
        }
    return false;
}
*/