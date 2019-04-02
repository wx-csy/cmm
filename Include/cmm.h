#ifndef __CMM_H__
#define __CMM_H__

#include "common.h"
#include "location.h"

extern cmm_loc_t yylloc;

int yylex(void);
int yyparse(void);

#endif
