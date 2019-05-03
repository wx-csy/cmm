#include <stdio.h>
#include "error.h"
#include "cmm.h"
#include "ast/ast.h"
#include "ast/function.h"

Program program;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            cmm_error(CMM_ERROR_FILEERROR, CMM_LOC_INITIALIZER, argv[1]);
            return 0;
        }
    }
    yyparse();
    /* lexical, syntax or semantics error */
    if (cmm_nr_error != 0) return EXIT_FAILURE;
    for (FuncList func = program.funclist; func; func = func->next)
        Function_IR_Generate_Code(func->data);
    return 0;
}

