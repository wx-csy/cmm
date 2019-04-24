#ifndef __AST_EXPRESSION_H__
#define __AST_EXPRESSION_H__

#include "ast/ast.h"
#include "ast/type.h"
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


typedef struct ArgList {
    size_t nr_arg;
    Expression **args;
} ArgList;

typedef struct Expression {
    enum ExprType type;
    Type *valtype;
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
            struct Function *func;
            struct ArgList arglist;
        };
        struct {
            /* variable expression */
            struct Variable *var;
            /* member access */
            size_t memberid;
        };
        struct {
            union {
                /* array access */
                struct Expression *arr;
                struct Expression *subscript;
            };
        };
        struct Literal lit;
    };
} Expression;

Expression *
Expression_Binary_Constructor(enum ExprType type, cmm_loc_t location,
                              Expression *lhs, Expression *rhs);

Expression *
Expression_Unary_Constructor(enum ExprType type, cmm_loc_t location,
                             Expression *rhs);

Expression *
Expression_Assign_Constructor(cmm_loc_t location,
                              Expression *lhs, Expression *rhs);

Expression *
Expression_FuncCall_Constructor(cmm_loc_t location,
                                Function *func, Expression *rhs);

Expression *
Expression_ArrayAccess_Constructor(cmm_loc_t location,
                                   Expression *arr, Expression *subscript);

Expression *
Expression_Variable_Constructor(cmm_loc_t location, Variable *var);

Expression *
Expression_Literal_Constructor(cmm_loc_t location, Literal lit);

#endif
