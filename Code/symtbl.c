#include <string.h>
#include <stdio.h>
#include "ast/type.h"
#include "ast/function.h"
#include "ast/variable.h"
#include "cmm.h"
#include "symtbl.h"


// zero initialization is enough
void symtbl_init(symtbl *table) {
    memset(table, 0, sizeof(*table));
}

void *symtbl_find(symtbl *table, const char *name) {
#ifdef DEBUG
    fprintf(stderr, "[symtbl] find in %p for '%s'\n", table, name);
#endif
    for (symtbl entry = *table; entry; entry = entry->next) {
        if (strcmp(entry->data.name, name) == 0)
            return entry->data.item;
    }
    return NULL;
}

bool symtbl_insert(symtbl *table, const char *name, void *item) {
#ifdef DEBUG
    fprintf(stderr, "[symtbl] insert to %p: ('%s', %p)\n", table, name, item);
#endif
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
#ifdef DEBUG
    fprintf(stderr, "[symtbl] function insert: ('%s', %p)\n", name, func);
#endif
    bool ret = symtbl_insert(&symtbl_scope->functions, name, func);
    if (!ret) cmm_error(CMM_ERROR_REDEF_FUNC, func->location, name);
    return ret;
}

Variable *symtbl_variable_find(const char *name, cmm_loc_t location) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Variable *result = symtbl_find(&cur->variables, name);
        if (result) return result;
    }
    cmm_error(CMM_ERROR_UNDEF_VAR, location, name);
    return &Variable_Invalid;
}

bool symtbl_variable_insert(const char *name, Variable *var) {
#ifdef DEBUG
    fprintf(stderr, "[symtbl] variable insert: ('%s', %p)\n", name, var);
#endif
    bool ret = symtbl_insert(&symtbl_scope->variables, name, var);
    if (!ret) {
        if (symtbl_scope->is_struct_scope) {
            cmm_error(CMM_ERROR_REDEF_MEMBER, var->location, name);
        } else {
            cmm_error(CMM_ERROR_REDEF_VAR, var->location, name);
        }
    }
    return ret;
}

Type *symtbl_struct_find(const char *name, cmm_loc_t location) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Type *result = symtbl_find(&cur->structs, name);
        if (result) return result;
    }
    cmm_error(CMM_ERROR_UNDEF_STRUCT, location, name);
    return &Type_Invalid;
}

bool symtbl_struct_insert(const char *name, Type *type) {
    bool ret = symtbl_insert(&symtbl_scope->structs, name, type);
    if (!ret) cmm_error(CMM_ERROR_REDEF_STRUCT, type->location, name);
    return ret;
}