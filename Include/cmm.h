#ifndef __CMM_H__
#define __CMM_H__

/* location type */
typedef struct cmm_loc {
    int line, col;
} cmm_loc_t;

#define CMM_LOC_INITIALIZER ((cmm_loc_t) {1, 1})

extern cmm_loc_t yylloc;

int yylex(void);
int yyparse(void);

#endif
