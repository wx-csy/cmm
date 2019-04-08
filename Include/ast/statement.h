#ifndef __AST_STATEMENT_H__
#define __AST_STATEMENT_H__

#include "ast/ast.h"
#include "location.h"

typedef enum StmtType {
    STMT_COMPOUND,
    STMT_EXPRESSION,
    STMT_RETURN,
    STMT_IFTHEN,
    STMT_IFTHENELSE,
    STMT_WHILE,
} StmtType;

typedef struct StmtList {
    size_t nr_stmt;
    Expression **stmts;
} StmtList;

typedef struct Statement {
    enum StmtType type;
    cmm_loc_t location;

    union {
        /* compound statement */
        struct {
            struct VarList varlist;
            struct StmtList stmtlist;
        };
        /* expression statement */
        /* return statement */
        struct Expression *expr;
        /* if-then-(else) statement */
        struct {
            struct Expression *if_cond;
            struct Statement *stat_if_true;
            struct Statement *stat_if_false;
        };
        /* while expression */
        struct {
            struct Expression *while_cond;
            struct Statement *while_body;
        };
    };
} Statement;

Statement *
Compound_Statement_Constructor(cmm_loc_t location, VarList varlist, StmtList stmtlist)

Statement *
Expression_Statement_Constructor(cmm_loc_t location, Expression *expr);

Statement *
Return_Statement_Constructor(cmm_loc_t location, Expression *expr);

Statement *
IfThen_Statement_Constructor(cmm_loc_t location, Expression *if_cond, Statement *stat_if_true);

Statement *
IfThenElse_Statement_Constructor(cmm_loc_t location,
                                 Expression *if_cond, Statement *stat_if_true, Statement *stat_if_false);

Statement *
While_Statement_Constructor(cmm_loc_t location, Expression *while_cond, Statement *while_body);

void Statement_Destructor(Statement *stmt);

#endif
