#ifndef RRT
#define RRT

#include <stdio.h>
#include <math.h>

#define XDIM 640
#define YDIM 480
// #define WINSIZE [XDIM, YDIM]
#define EPSILON 7.0
#define NUMNODES 500

typedef struct point {
    double x;
    double y;
} point_t;

#endif