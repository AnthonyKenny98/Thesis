#ifndef RRT
#define RRT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define XDIM 640
#define YDIM 480

#define EPSILON 10.0
#define NUM_NODES 500
#define NUM_OBSTACLES 10

#define STEP_DELAY 2

typedef struct point {
    double x;
    double y;
} point_t;

typedef struct edge {
    point_t p1 ;
    point_t p2;
} edge_t;

typedef struct graph {
    point_t nodes[NUM_NODES];
    edge_t edges[NUM_NODES];
    int existingNodes;
} graph_t;

typedef struct obstacle {
    point_t v1;
    point_t v2;
    point_t v3;
    point_t v4;
} obstacle_t;

typedef struct space {
    obstacle_t obstacles[NUM_OBSTACLES];
} space_t;



#endif