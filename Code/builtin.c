#include "symtbl.h"
#include "ast/ast.h"
#include "ast/function.h"
#include "ast/statement.h"
#include "ast/expression.h"
#include "ast/variable.h"

static Function *builtin_func_read;
static Function *builtin_func_write;

void builtin_declare() {
    /* int read() */
    builtin_func_read =  Function_Constructor("read",
        CMM_LOC_INITIALIZER,
        Type_Basic_Constructor(BT_INT));
    builtin_func_read->stmt = Statement_Return_Constructor(
        CMM_LOC_INITIALIZER,
        Expression_Read_Constructor(CMM_LOC_INITIALIZER),
        builtin_func_read
    );
    symtbl_insert(&symtbl_functions, "read", builtin_func_read);

    /* int write(int) */
    builtin_func_write = Function_Constructor("write",
        CMM_LOC_INITIALIZER,
        Type_Basic_Constructor(BT_INT));
    Variable *write_param = Variable_Constructor(
        CMM_LOC_INITIALIZER,
        "value"
    );
    write_param->valtype = Type_Basic_Constructor(BT_INT);
    list_prepend(&builtin_func_write->paramlist, write_param);
    builtin_func_write->stmt = Statement_Expression_Constructor(
        CMM_LOC_INITIALIZER,
        Expression_Write_Constructor(CMM_LOC_INITIALIZER,
            Expression_Variable_Constructor(CMM_LOC_INITIALIZER, write_param)
        )
    );
    symtbl_insert(&symtbl_functions, "write", builtin_func_write);
}

void builtin_define() {
    // Function_IR_Generate_Code(builtin_func_read);
    // Function_IR_Generate_Code(builtin_func_write);
}