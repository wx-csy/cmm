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
    symtbl functions;
    symtbl structs;
    struct symscope *prev;
};

extern struct symscope *symtbl_scope;

/* Create a new scope for name lookup. */
void symtbl_push_scope(bool is_struct_scope);

/* Restore the old scope for name lookup */
void symtbl_pop_scope();

Function *symtbl_function_find(const char *name);
bool symtbl_function_insert(const char *name, Function *func);
Variable *symtbl_variable_find(const char *name, cmm_loc_t location);
bool symtbl_variable_insert(const char *name, Variable *var);
Type *symtbl_struct_find(const char *name, cmm_loc_t location);
bool symtbl_struct_insert(const char *name, Type *type);

#endif
