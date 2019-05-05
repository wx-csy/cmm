#ifndef __OPTION_H__
#define __OPTION_H__

#include "common.h"

extern bool opt_show_comment;
extern bool opt_verbose;
extern const char *opt_program_name;
void opt_parse(int argc, char *argv[]);

#endif
