#include <stdlib.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include "error.h"
#include "option.h"

bool opt_show_comment;
bool opt_verbose;
const char *opt_program_name;

static noreturn void _opt_usage() {
    printf("Usage: %s [-cvh] [file]\n", opt_program_name);
    printf("Generate IR for given cmm source.\n");
    printf("Options:\n");
    printf("  -c    Show comments in output files.\n");
    printf("  -v    Enter verbose mode.\n");
    printf("  -h    Display this help message.\n");
    printf("  file  Read from specified file instead of stdin.\n");
    exit(EXIT_FAILURE);
}

static void _opt_parse_flags(const char *flags) {
    do {
        switch (*flags) {
        case 'c' :
            opt_show_comment = true;
            break;
        case 'v' :
            opt_verbose = true;
            break;
        case 'h' : _opt_usage();
        default : _opt_usage();
        }
    } while (*(++flags));
}

void opt_parse(int argc, char *argv[]) {
    opt_program_name = argv[0];
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            _opt_parse_flags(argv[i] + 1);
        } else {
            if (freopen(argv[i], "r", stdin) == NULL) {
                cmm_error(CMM_ERROR_FILEERROR, CMM_LOC_INITIALIZER, argv[1]);
                exit(EXIT_FAILURE);
            }
        }
    }
}
