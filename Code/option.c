#include <stdlib.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "option.h"

bool opt_show_comment;
bool opt_verbose;
int opt_optimize;
static bool input_redirected;
FILE *opt_output_stream;
const char *opt_program_name;

static noreturn void _opt_usage() {
    printf("Usage: %s [-cvhO] [file [ [-o] output ] ]\n", opt_program_name);
    printf("Generate IR for given cmm source.\n");
    printf("Options:\n");
    printf("  -c    Show comments in output files.\n");
    printf("  -v    Enter verbose mode.\n");
    printf("  -h    Display this help message.\n");
    printf("  -O    Generate optimized IR code.\n");
    printf("  -o    Output to specified file.\n");
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
        case 'O' :
            opt_optimize = 1;
            break;
        case 'h' : _opt_usage();
        default : _opt_usage();
        }
    } while (*(++flags));
}

static void redirect_output(const char *filename) {
    opt_output_stream = fopen(filename, "w");
    if (opt_output_stream == NULL) {
        cmm_error(CMM_ERROR_FILEERROR, CMM_LOC_INITIALIZER, filename);
        exit(EXIT_FAILURE);
    }
}

static void redirect_input(const char *filename) {
    if (freopen(filename, "r", stdin) == NULL) {
        cmm_error(CMM_ERROR_FILEERROR, CMM_LOC_INITIALIZER, filename);
        exit(EXIT_FAILURE);
    }
}

void opt_parse(int argc, char *argv[]) {
    opt_program_name = argv[0];
    opt_output_stream = stdout;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (++i >= argc) _opt_usage();
            redirect_output(argv[i]);
        } else if (argv[i][0] == '-') {
            _opt_parse_flags(argv[i] + 1);
        } else {
            if (!input_redirected) {
                redirect_input(argv[i]);
                input_redirected = true;
            } else {
                redirect_output(argv[i]);
            }
        }
    }
}
