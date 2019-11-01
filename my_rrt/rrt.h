#ifndef RRT
#define RRT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define XDIM 640
#define YDIM 480

#define EPSILON 20.0
#define NUM_NODES 5000

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

#endif