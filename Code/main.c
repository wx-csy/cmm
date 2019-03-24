#include <stdio.h>
#include "error.h"
#include "cmm.h"
#include "cst.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            cmm_error(CMM_ERROR_FILEERROR, CMM_LOC_INITIALIZER, argv[1]);
            return 0;
        }
    }
    yyparse();
    if (cmm_nr_error == 0) cst_node_print(cst, 0);
    return 0;
}

