#ifndef __AST_STATEMENT_H__
#define __AST_STATEMENT_H__

#include "ast/ast.h"
#include "ast/variable.h"
#include "location.h"

typedef enum StmtType {
    STMT_INVALID,
    STMT_COMPOUND,
    STMT_EXPRESSION,
    STMT_RETURN,
    STMT_IFTHEN,
    STMT_IFTHENELSE,
    STMT_WHILE,
} StmtType;

typedef struct Statement {
    enum StmtType type;
    cmm_loc_t location;

    union {
        /* compound statement */
        struct {
            VarList varlist;
            StmtList stmtlist;
        };
        /* expression statement */
        /* return statement */
        Expression *expr;
        /* if-then-(else) statement */
        struct {
            Expression *if_cond;
            Statement *stat_if_true;
            Statement *stat_if_false;
        };
        /* while expression */
        struct {
            Expression *while_cond;
            Statement *while_body;
        };
    };
} Statement;

extern Statement Statement_Invalid;

Statement *
Statement_Compound_Constructor(cmm_loc_t location, VarList varlist, StmtList stmtlist);

Statement *
Statement_Expression_Constructor(cmm_loc_t location, Expression *expr);

Statement *
Statement_Return_Constructor(cmm_loc_t location, Expression *expr);

Statement *
Statement_IfThen_Constructor(cmm_loc_t location, Expression *if_cond, Statement *stat_if_true);

Statement *
Statement_IfThenElse_Constructor(cmm_loc_t location,
                                 Expression *if_cond, Statement *stat_if_true, Statement *stat_if_false);

Statement *
Statement_While_Constructor(cmm_loc_t location, Expression *while_cond, Statement *while_body);

#endif
