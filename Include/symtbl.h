/*
 *  This module implements data structures for symbol table.
 *  It also provides global function name lookup and maintains name
 * lookup scope.
 */
#ifndef __SYMTBL_H__
#define __SYMTBL_H__
#include "ast/ast.h"
#include "location.h"

struct symtbl_entry {
    const char *name;
    void *item;
};

typedef declare_list_node(symtbl_node, struct symtbl_entry)
    symtbl_node, *symtbl;

/* Initialize a symtbl object. */
void symtbl_init(symtbl *table);

/* Find a member in symtbl. If not found, return NULL. */
void *symtbl_find(symtbl *table, const char *name);

/* Insert an element to symtbl. If name exists, return false. */
bool symtbl_insert(symtbl *table, const char *name, void *item);

/* Erase an element in symtbl. If name does not exist, return false. */
/* Currently, we do not provide this function. */
/*
bool symtbl_erase(symtbl* table, const char *name);
*/

struct symscope {
    bool is_struct_scope;
    symtbl variables;
    symtbl structs;
    struct symscope *prev;
};

extern struct symscope *symtbl_scope;
extern symtbl symtbl_functions;

/* Create a new scope for name lookup. */
void symtbl_push_scope(bool is_struct_scope);

/* Restore the old scope for name lookup. */
void symtbl_pop_scope();

/* Check if 'name' exists in current scope. */
bool symtbl_current_exist(const char *name);
Function *symtbl_function_try_find(const char *name);
Function *symtbl_function_find(const char *name, cmm_loc_t location);
/* Declare a function named 'name'. */
bool symtbl_declare_function(const char *name, Function *func);
/* Define a function named 'name'. */
bool symtbl_define_function(Function *func);
bool symtbl_function_insert(const char *name, Function *func);
bool symtbl_function_finalize(void);
Variable *symtbl_variable_try_find(const char *name);
Variable *symtbl_variable_find(const char *name, cmm_loc_t location);
bool symtbl_variable_insert(const char *name, Variable *var);
Type *symtbl_struct_try_find(const char *name);
Type *symtbl_struct_find(const char *name, cmm_loc_t location);
bool symtbl_struct_insert(const char *name, Type *type);

#endif
