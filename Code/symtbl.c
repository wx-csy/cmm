#include <string.h>
#include "cmm.h"
#include "symtbl.h"


// zero initialization is enough
void symtbl_init(symtbl *table) {
    memset(table, 0, sizeof(*table));
}

void *symtbl_find(symtbl *table, const char *name) {
    for (symtbl entry = *table; entry; entry = entry->next) {
        if (strcmp(entry->data.name, name) == 0)
            return entry->data.item;
    }
    return NULL;
}

bool symtbl_insert(symtbl *table, const char *name, void *item) {
    if (symtbl_find(table, name)) return false;
    struct symtbl_entry entry = {name, item};
    list_prepend(table, entry);
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

struct symscope *symtbl_scope = NULL;

void symtbl_push_scope(bool is_struct_scope) {
    struct symscope *newscope = pzalloc(sizeof(struct symscope));
    newscope->is_struct_scope = is_struct_scope;
    newscope->prev = symtbl_scope;
    symtbl_scope = newscope;
}

void symtbl_pop_scope() {
    symtbl_scope = symtbl_scope->prev;
}

Function *symtbl_function_find(const char *name) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Function *result = symtbl_find(&cur->functions, name);
        if (result) return result;
    }
    return NULL;
}

bool symtbl_function_insert(const char *name, Function *func) {
    return symtbl_insert(&symtbl_scope->functions, name, func);
}

Variable *symtbl_variable_find(const char *name) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Variable *result = symtbl_find(&cur->variables, name);
        if (result) return result;
    }
    return NULL;
}

bool symtbl_variable_insert(const char *name, Variable *var) {
    return symtbl_insert(&symtbl_scope->variables, name, var);
}

Type *symtbl_struct_find(const char *name) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Type *result = symtbl_find(&cur->structs, name);
        if (result) return result;
    }
    return NULL;
}

bool symtbl_struct_insert(const char *name, Type *type) {
    return symtbl_insert(&symtbl_scope->structs, name, type);
}