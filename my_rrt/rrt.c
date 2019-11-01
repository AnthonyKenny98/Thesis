/*
* @Author: AnthonyKenny98
* @Date:   2019-10-31 11:57:52
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2019-10-31 22:48:01
*/

#include "rrt.h"

// Returns a random double since C doesn't do this natively (cucc)
double randomDouble(int max) {
    return ((double)rand() / (double)RAND_MAX) * max;
}

// Euclidean Distance between two points
double distance(point_t p1, point_t p2) {
    return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
}

point_t getRandomNode() {
    return (point_t) {.x = randomDouble(XDIM), .y = randomDouble(YDIM)};
}

point_t findNearestNode(point_t randomPoint, graph_t *graph) {
    point_t nearestNode = graph->nodes[0];
    for (int i=0; i<graph->existingNodes; i++) {
        if (distance(graph->nodes[i], randomPoint) < distance(nearestNode, randomPoint)) {
            nearestNode = graph->nodes[i];
        }
    }
    return nearestNode;
}

bool compareNode(point_t p1, point_t p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

// Steps from point 1 to point 2 or new point
point_t stepFromTo(point_t p1, point_t p2) {
    if (distance(p1, p2) < EPSILON) {
        return p2;
    }
    else {
        double theta = atan((p2.y-p1.y) / (p2.x - p1.x));
        point_t newPoint;
        newPoint.x = p1.x - EPSILON*cos(theta);
        newPoint.y = p1.x - EPSILON*sin(theta);
        return newPoint;
    }
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int rrt(graph_t *graph) {

    // Start Point
    point_t startNode = {.x = XDIM/2.0, .y = YDIM/2.0};
    graph->nodes[0] = startNode;

    // Goal Point
    point_t goalNode = {.x = 100, .y = 100};

    // Init points
    point_t randomNode = startNode;
    point_t nearestNode;
    point_t newNode;

    for (int i=1; i<NUM_NODES; i++) {
        
        // Get Random Point
        randomNode = getRandomNode();
        
        // Run through all points in graph, returns point nearest to randomPoint 
        nearestNode = findNearestNode(randomNode, graph);

        // Moves an incremental distance from nearestNode to (randomPoint if distance is < Epsilon) or new point
        newNode = stepFromTo(nearestNode, randomNode);
        
        // Update graph
        graph->nodes[i] = newNode;
        graph->existingNodes++;

        // Draw edge
        edge_t newEdge = {.p1 = nearestNode, .p2 = newNode};
        graph->edges[i] = newEdge;

        // Check if done
        if (distance(newNode, goalNode) < 50) {
            printf("%i\n", i);
            printf("Found End Node\n");
            return 0;
        }
    }

    printf("%i\n", NUM_NODES);
    printf("Didn't Find End Node\n");
    return 1;
}

int main() {

    // Configure Randomness
    srand ((unsigned int) time(NULL)*10000000);

    // Init Graph
    graph_t *graph = malloc(sizeof(graph_t));
    graph->existingNodes = 0;

    // Allocate Memory for Start and End Nodes
    point_t *startNode = malloc(sizeof(point_t));
    point_t *goalNode = malloc(sizeof(point_t));

    // Init Start and End Nodes
    startNode->x = XDIM/2.0;
    startNode->y = YDIM/2.0;
    goalNode->x = 100;
    goalNode->y = 100;

    // run RRT
    int status = rrt(graph);

    // GUI
    FILE *pipe = popen("gnuplot -persist", "w");
    FILE *temp = fopen("path.temp", "w");
    FILE *start = fopen("start.temp", "w");
    FILE *end = fopen("end.temp", "w");

    // set axis ranges
    fprintf(pipe,"set xrange [0:%d]\n", XDIM);
    fprintf(pipe,"set yrange [0:%d]\n", YDIM);

    fprintf(start, "%lf %lf \n", startNode->x, startNode->y);
    fprintf(end, "%lf %lf \n", goalNode->x, goalNode->y);
    for (int a=0; a < graph->existingNodes; a++) // a plots
    {
        fprintf(pipe,"set title \"Number of Nodes: %d\"\n", a);
        
        fprintf(temp, "%lf %lf \n", graph->nodes[a].x, graph->nodes[a].y); //Write the data to a temporary file

        char *gnu_command = "plot \
                            'path.temp' with point pointtype 1 ps 0.5 lc rgb \"red\" notitle, \
                            'start.temp' with point pointtype 3 ps 2 lc rgb \"blue\" title \'Start Node\', \
                            'end.temp' with point pointtype 3 ps 2 lc rgb \"green\" title \'Goal Node\'\n";
        fprintf(pipe, "%s\n", gnu_command);

        fflush(start);
        fflush(end);
        fflush(temp);
        fflush(pipe);   // flush the pipe to update the plot
        delay(10);
    }

    //  Close Files
    fclose(temp);
    fclose(pipe);
    
    // Free Memory
    free(graph);
    free(startNode);
    free(goalNode);


    return status;
}
