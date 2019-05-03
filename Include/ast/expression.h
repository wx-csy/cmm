#ifndef __AST_EXPRESSION_H__
#define __AST_EXPRESSION_H__

#include "ast/ast.h"
#include "ast/type.h"
#include "location.h"

typedef enum UnaryOperator {
    UOP_NEGATE,
    UOP_NOT,
} UnaryOperator;

typedef enum BinaryOperator {
    BOP_ADD,
    BOP_MINUS,
    BOP_STAR,
    BOP_DIV,
    BOP_GT,
    BOP_LT,
    BOP_GE,
    BOP_LE,
    BOP_EQU,
    BOP_NEQ,
    BOP_AND,
    BOP_OR,
    BOP_ARRAY_ACCESS,
} BinaryOperator;

typedef enum ExprType {
    EXPR_BINARY_EXPR,
    EXPR_UNARY_EXPR,
    EXPR_ASSIGN,
    EXPR_FUNCCALL,
    EXPR_MEMBERACCESS,
    EXPR_VARIABLE,
    EXPR_LITERAL
} ExprType;

typedef struct Expression {
    enum ExprType type;
    Type *valtype;
    bool lvalue;
    cmm_loc_t location;

    union {
        /* unary expression */
        /* binary expression */
        /* assign expression */
        struct {
            union {
                enum UnaryOperator uop_type;
                enum BinaryOperator bop_type;
            };
            Expression *lhs, *rhs;
        };
        /* function call */
        struct {
            Function *func;
            ArgList arglist;
        };
        /* variable expression */
        Variable *var;
        /* member access */
        struct {
            Expression *expr;
            Variable *member;
        };
        /* literal value */
        union {
            int lit_int;
            float lit_float;
        };
    };
} Expression;

Expression *
Expression_Binary_Constructor(enum BinaryOperator optype, cmm_loc_t location,
                              Expression *lhs, Expression *rhs);

Expression *
Expression_Unary_Constructor(enum UnaryOperator optype, cmm_loc_t location,
                             Expression *rhs);

Expression *
Expression_Assign_Constructor(cmm_loc_t location, Expression *lhs, Expression *rhs);

Expression *
Expression_FuncCall_Constructor(cmm_loc_t location, const char *funcname, ArgList args);

Expression *
Expression_MemberAccess_Constructor(cmm_loc_t location, Expression *expr, const char *memname);

Expression *
Expression_Variable_Constructor(cmm_loc_t location, const char *varname);

Expression *
Expression_Literal_int_Constructor(cmm_loc_t location, int value);

Expression *
Expression_Literal_float_Constructor(cmm_loc_t location, float value);

void Expression_TailCall_IR_Generate_Code(Expression *expr);
const char *Expression_IR_Generate_Code(Expression *expr);
#endif
