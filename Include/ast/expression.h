#ifndef __AST_EXPRESSION_H__
#define __AST_EXPRESSION_H__

#include "ast/ast.h"
#include "location.h"

typedef enum ExprType {
    EXPR_BINARY_ADD,
    EXPR_BINARY_MINUS,
    EXPR_BINARY_STAR,
    EXPR_BINARY_DIV,
    EXPR_BINARY_GT,
    EXPR_BINARY_LT,
    EXPR_BINARY_GE,
    EXPR_BINARY_LE,
    EXPR_BINARY_EQU,
    EXPR_BINARY_NEQ,
    EXPR_BINARY_AND,
    EXPR_BINARY_OR,
    EXPR_UNARY_NEGATE,
    EXPR_UNARY_NOT,
    EXPR_ASSIGN,
    EXPR_FUNCCALL,
    EXPR_ARRAYACCESS,
    EXPR_VARIABLE,
    EXPR_LITERAL
} ExprType;

#define _EXPR_BINARY_BEGIN      EXPR_BINARY_ADD
#define _EXPR_BINARY_END        EXPR_BINARY_OR
#define _EXPR_UNARY_BEGIN       EXPR_UNARY_NEGATE
#define _EXPR_UNARY_END         EXPR_UNARY_NOT

typedef struct ArgList {
    size_t nr_arg;
    Expression **args;
} ArgList;

typedef struct Expression {
    enum ExprType exprtype;
    Type __ref *type;
    cmm_loc_t location;

    union {
        /* unary expression */
        /* binary expression */
        /* assign expression */
        struct {
            struct Expression *lhs, *rhs;
        };
        /* function call */
        struct {
            struct Function __ref *func;
            struct ArgList arglist;
        };
        struct {
            /* variable expression */
            struct Variable __ref *var;
            union {
                /* array access */
                struct ArgList sublist;
                /* member access */
                size_t memberid;
            };
        };
        struct Literal lit;
    };
} Expression;

Expression *
Binary_Expression_Constructor(enum ExprType type, cmm_loc_t location,
                              Expression *lhs, Expression *rhs);

Expression *
Unary_Expression_Constructor(enum ExprType type, cmm_loc_t location,
                             Expression *rhs);

Expression *
Assign_Expression_Constructor(cmm_loc_t location,
                              Expression *lhs, Expression *rhs);

Expression *
FuncCall_Expression_Constructor(cmm_loc_t location,
                                Function *func, Expression *rhs);

Expression *
ArrayAccess_Expression_Constructor(cmm_loc_t location,
                                   Variable *var, SubList sublist);


Expression *
Variable_Expression_Constructor(cmm_loc_t location, Variable *var);

Expression *
Literal_Expression_Constructor(cmm_loc_t location, Literal lit);

void Expression_Destructor(Expression *expr);

#endif
