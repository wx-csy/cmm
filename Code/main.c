#include <stdio.h>
#include "error.h"
#include "cmm.h"
#include "option.h"
#include "symtbl.h"
#include "ast/ast.h"
#include "ast/function.h"
#include "builtin.h"
#include "ir.h"

Program program;


int main(int argc, char *argv[]) {
    opt_parse(argc, argv);
    builtin_declare();
    yyparse();
    builtin_define();
    /* lexical, syntax or semantics error */
    if (cmm_nr_error != 0) return EXIT_FAILURE;
    for (FuncList func = program.funclist; func; func = func->next)
        Function_IR_Generate_Code(func->data);
    return 0;
}

