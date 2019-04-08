#ifndef __AST_AST_H__
#define __AST_AST_H__

typedef struct Expression Expression;
typedef struct Statement Statement;
typedef struct Function Function;
typedef struct Variable Variable;
typedef struct Literal Literal

typedef struct VarList {
    size_t nr_var;
    Variable **vars;
} VarList;


#endif
