#ifndef __OPTION_H__
#define __OPTION_H__

#include "common.h"

extern bool opt_show_comment;
extern bool opt_verbose;
extern int opt_optimize;
extern const char *opt_program_name;
extern FILE *opt_output_stream;
void opt_parse(int argc, char *argv[]);

#endif
