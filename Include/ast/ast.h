#ifndef __AST_AST_H__
#define __AST_AST_H__

#include "container/list.h"

typedef struct Expression Expression;
typedef struct Statement Statement;
typedef struct Function Function;
typedef struct Variable Variable;
typedef struct Literal Literal;
typedef struct Type Type;

typedef declare_list_node(VarList_node, Variable *) VarList_node, *VarList;
typedef declare_list_node(FuncList_node, Function *) FuncList_node, *FuncList;
typedef declare_list_node(StmtList_node, Statement *) StmtList_node, *StmtList;
typedef declare_list_node(ArgList_node, Expression *) ArgList_node, *ArgList;

struct Program {
    FuncList funclist;
    VarList varlist;
};

#endif
