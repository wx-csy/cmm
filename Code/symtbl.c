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
    list_foreach(*table, entry)
        if (strcmp(entry->data.name, name) == 0)
            return entry->data.item;
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
symtbl symtbl_functions;

void symtbl_push_scope(bool is_struct_scope) {
    struct symscope *newscope = pzalloc(sizeof(struct symscope));
    newscope->is_struct_scope = is_struct_scope;
    newscope->prev = symtbl_scope;
    symtbl_scope = newscope;
}

void symtbl_pop_scope() {
    symtbl_scope = symtbl_scope->prev;
}

bool symtbl_current_exist(const char *name) {
    return symtbl_find(&symtbl_scope->variables, name) ||
        symtbl_find(&symtbl_functions, name) ||
        symtbl_find(&symtbl_scope->structs, name);
}

Function *symtbl_function_try_find(const char *name) {
    return symtbl_find(&symtbl_functions, name);
}


Function *symtbl_function_find(const char *name, cmm_loc_t location) {
    Function *res = symtbl_function_try_find(name);
    if (res) return res;
    if (symtbl_variable_try_find(name)) {
        cmm_error(CMM_ERROR_INVCALL, location, name);
    } else {
        cmm_error(CMM_ERROR_UNDEF_FUNC, location, name);
    }
    return &Function_Invalid;
}

bool symtbl_declare_function(const char *name, Function *func) {
#ifdef DEBUG
    fprintf(stderr, "declare function name '%s'\n", name);
#endif
    Function *old_func = symtbl_function_try_find(name);
    if (old_func) {
        if (!Function_Declaration_Compatible(func, old_func)) {
            cmm_error(CMM_ERROR_FUNC_DEC_MISMATCH, func->location, name);
            return false;
        } else {
            return true;
        }
    } else {
        symtbl_function_insert(name, func);
        return true;
    }
}

bool symtbl_define_function(Function *func) {
#ifdef DEBUG
    fprintf(stderr, "define function name '%s'\n", func->name);
#endif
    Function *old_func = symtbl_function_try_find(func->name);
    assert(old_func);
    if (old_func->stmt) {
        cmm_error(CMM_ERROR_REDEF_FUNC, func->location, func->name);
        return false;
    } else {
        *old_func = *func;
        return true;
    }
}

bool symtbl_function_insert(const char *name, Function *func) {
#ifdef DEBUG
    fprintf(stderr, "[symtbl] function insert: ('%s', %p)\n", name, func);
#endif
    if (symtbl_current_exist(name)) {
        cmm_error(CMM_ERROR_REDEF_FUNC, func->location, name);
        return false;
    } else {
        symtbl_insert(&symtbl_functions, name, func);
        return true;
    }
}

bool symtbl_function_finalize(void) {
    bool ret = true;
    for (symtbl funcnode = symtbl_functions; funcnode; funcnode = funcnode->next) {
        Function *func = funcnode->data.item;
        if (func->stmt == NULL) {
            ret = false;
            cmm_error(CMM_ERROR_DECFUNC_UNDEF, func->location, func->name);
        }
    }
    return ret;
}

Variable *symtbl_variable_try_find(const char *name) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Variable *result = symtbl_find(&cur->variables, name);
        if (result) return result;
    }
    return NULL;
}

Variable *symtbl_variable_find(const char *name, cmm_loc_t location) {
    Variable *ret = symtbl_variable_try_find(name);
    if (ret) return ret;
    cmm_error(CMM_ERROR_UNDEF_VAR, location, name);
    return &Variable_Invalid;
}

bool symtbl_variable_insert(const char *name, Variable *var) {
#ifdef DEBUG
    fprintf(stderr, "[symtbl] variable insert: ('%s', %p)\n", name, var);
#endif
    if (symtbl_current_exist(name)) {
        if (symtbl_scope->is_struct_scope) {
            cmm_error(CMM_ERROR_REDEF_MEMBER, var->location, name);
        } else {
            cmm_error(CMM_ERROR_REDEF_VAR, var->location, name);
        }
        return false;
    } else {
        symtbl_insert(&symtbl_scope->variables, name, var);
        return true;
    }
}

Type *symtbl_struct_try_find(const char *name) {
    for (struct symscope *cur = symtbl_scope; cur; cur = cur->prev) {
        struct Type *result = symtbl_find(&cur->structs, name);
        if (result) return result;
    }
    return NULL;
}

Type *symtbl_struct_find(const char *name, cmm_loc_t location) {
    Type *ret = symtbl_struct_try_find(name);
    if (ret) return ret;
    cmm_error(CMM_ERROR_UNDEF_STRUCT, location, name);
    return &Type_Invalid;
}

bool symtbl_struct_insert(const char *name, Type *type) {
    if (symtbl_current_exist(name)) {
        cmm_error(CMM_ERROR_REDEF_STRUCT, type->location, name);
        return false;
    } else {
        symtbl_insert(&symtbl_scope->structs, name, type);
        return true;
    }
}