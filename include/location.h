#ifndef __LOCATION_H__
#define __LOCATION_H__

typedef struct location {
    int line, col;
} location_t;

#define DEFAULT_LOCATION {1, 1}

#endif
