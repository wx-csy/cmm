#ifndef __CMM_H__
#define __CMM_H__

#include "common.h"
#include "location.h"
#include "error.h"
#include "ast/ast.h"

extern cmm_loc_t yylloc;
extern Program program;

int yylex(void);
int yyparse(void);

#endif
