/*
* @Author: AnthonyKenny98
* @Date:   2019-10-31 11:57:52
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2019-11-01 22:24:24
*/

#include "rrt.h"
#include "tools.h"

// Euclidean Distance between two points
double distance(point_t p1, point_t p2) {
    return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
}

// Returns a random node in the state space
point_t getRandomNode() {
    return (point_t) {.x = randomDouble(XDIM), .y = randomDouble(YDIM)};
}

// Creates NUM_OBSTACLES rectangular obstacles
void initObstacles(space_t *space) {
    
    for (int i=0; i<NUM_OBSTACLES; i++) {
        point_t p1 = getRandomNode();
        point_t p2 = {.x = p1.x, .y = p1.y+50};
        point_t p3 = {.x = p1.x+50, .y = p1.y+50};
        point_t p4 = {.x = p1.x+50, .y = p1.y};
        obstacle_t obstacle = {.v1 = p1, .v2 = p2, .v3 = p3, .v4 = p4};
        space->obstacles[i] = obstacle;
    }
}

// Moves an incremental distance from nearestNode to (randomPoint if distance is < Epsilon) or new point
point_t findNearestNode(point_t randomPoint, graph_t *graph) {
    point_t nearestNode = graph->nodes[0];
    for (int i=0; i<graph->existingNodes; i++) {
        if (distance(graph->nodes[i], randomPoint) < distance(nearestNode, randomPoint)) {
            nearestNode = graph->nodes[i];
        }
    }
    return nearestNode;
}


// Steps from point 1 to point 2 or new point
point_t stepFromTo(point_t p1, point_t p2) {
    if (distance(p1, p2) < EPSILON) {
        return p2;
    }
    else {
        double theta = atan2((p2.y-p1.y), (p2.x - p1.x));
        point_t newPoint;
        newPoint.x = p1.x + EPSILON*cos(theta);
        newPoint.y = p1.y + EPSILON*sin(theta);
        return newPoint;
    }
}

bool LineIntersectsLine(point_t l1p1, point_t l1p2, point_t l2p1, point_t l2p2) {
    double q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) - (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
    double d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);

    if( d == 0 )
    {
        return false;
    }

    double r = q / d;

    q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) - (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
    double s = q / d;

    if( r < 0 || r > 1 || s < 0 || s > 1 )
    {
        return false;
    }

    return true;
}

bool LineIntersectsRect(point_t p1, point_t p2, obstacle_t r) {
    return LineIntersectsLine(p1, p2, (point_t) {.x=r.v1.x, .y=r.v1.y}, (point_t) {.x=r.v2.x, .y=r.v1.y}) ||
           LineIntersectsLine(p1, p2, (point_t) {.x=r.v2.x, .y=r.v1.y}, (point_t) {.x=r.v2.x, .y=r.v2.y}) ||
           LineIntersectsLine(p1, p2, (point_t) {.x=r.v2.x, .y=r.v2.y}, (point_t) {.x=r.v1.x, .y=r.v2.y}) ||
           LineIntersectsLine(p1, p2, (point_t) {.x=r.v1.x, .y=r.v2.y}, (point_t) {.x=r.v1.x, .y=r.v1.y});
}

double perpendicularDistance(point_t node, edge_t line) {
    double m = (line.p1.y - line.p2.y) / (line.p1.x - line.p2.x);
    double a = (line.p1.y - line.p2.y);
    double b = (line.p2.x - line.p1.x);
    double c = (line.p1.x - line.p2.x)*line.p1.y + (line.p2.y - line.p1.y)*line.p1.x;
    return (double)(fabs(a * node.x + b * node.y + c)) / (sqrt(pow(a,2) + pow(b,2)));
}

bool pointInRectangle(point_t node, obstacle_t obs) {
    return ((perpendicularDistance(node, (edge_t) {.p1=obs.v1, .p2=obs.v2}) < distance(obs.v1, obs.v4)) && 
        (perpendicularDistance(node, (edge_t) {.p1=obs.v2, .p2=obs.v3}) < distance(obs.v2, obs.v1))) ||
        ((perpendicularDistance(node, (edge_t) {.p1=obs.v3, .p2=obs.v4}) < distance(obs.v3, obs.v2)) &&
        (perpendicularDistance(node, (edge_t) {.p1=obs.v4, .p2=obs.v1}) < distance(obs.v4, obs.v3)));
}

bool edgeCollisions(edge_t edge, space_t *space) {
    for (int i=0; i<NUM_OBSTACLES; i++) {
        if (LineIntersectsRect(edge.p1, edge.p2, space->obstacles[i]))
            return true;
    }
    return false;
}

// Returns true if point collides with obstacle
// Works only for Rectangular obstacles
bool point_collision(point_t node, space_t *space) {
    for (int i=0; i<NUM_OBSTACLES; i++) {
        obstacle_t obs = space->obstacles[i];
        if (pointInRectangle(node, obs)) 
            return true;
    }
    return false;
}

int rrt(graph_t *graph, space_t *space) {

    int status = 1;

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
        
        // Get Random Point that is not in collision with 
        do {
            randomNode = getRandomNode();
            // Run through all points in graph, returns point nearest to randomPoint 
            nearestNode = findNearestNode(randomNode, graph);

            // Moves an incremental distance from nearestNode to (randomPoint if distance is < Epsilon) or new point
            newNode = stepFromTo(nearestNode, randomNode);

        } while (point_collision(newNode, space));
        
        // Draw edge
        edge_t newEdge = {.p1 = nearestNode, .p2 = newNode};

        if (!edgeCollisions(newEdge, space)) {

            // Update graph
            graph->nodes[i] = newNode;
            graph->existingNodes++;
            graph->edges[i] = newEdge;

            // Check if done
            if (distance(newNode, goalNode) < 10) {
                printf("%i\n", i);
                printf("Found End Node\n");
                status = 0;
            }
        }
        else {
            printf("FUCKUP");
            i--;
        }
    }
    return status;
}

int main(int argc, char *argv[]) {

    // Configure Randomness
    srand ((unsigned int) time(NULL)*10000000);

    // Init Space
    space_t *space = malloc(sizeof(space_t));
    initObstacles(space);

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
    int status = rrt(graph, space);

    // GUI
    if (argc > 1 && !strcmp(argv[1], "--no-gui")) {
        return status;
    }

    FILE *pipe = popen("gnuplot -persist", "w");
    FILE *temp = fopen("path.temp", "w");
    FILE *start = fopen("start.temp", "w");
    FILE *end = fopen("end.temp", "w");

    // set axis ranges
    fprintf(pipe,"set xrange [0:%d]\n", XDIM);
    fprintf(pipe,"set yrange [0:%d]\n", YDIM);

    // Set Start and End Points
    fprintf(start, "%lf %lf \n", startNode->x, startNode->y);
    fprintf(end, "%lf %lf \n", goalNode->x, goalNode->y);

    // Set Obstacles
    for (int i=0; i<NUM_OBSTACLES; i++) {
        fprintf(pipe, 
                "set object %d rect from %lf,%lf to %lf,%lf fc lt 0 back\n", 
                i+1, 
                space->obstacles[i].v1.x, 
                space->obstacles[i].v1.y, 
                space->obstacles[i].v3.x, 
                space->obstacles[i].v3.y);
    }

    for (int a=0; a < graph->existingNodes; a++) // a plots
    {
        fprintf(pipe,"set title \"Number of Nodes: %d\"\n", a+1);
        
        fprintf(temp, "%lf %lf %lf %lf\n", graph->edges[a].p1.x, graph->edges[a].p1.y, graph->edges[a].p2.x, graph->edges[a].p2.y); //Write the data to a temporary file

        char *gnu_command = "plot \
                            'path.temp' using 1:2:($3-$1):($4-$2) with vectors nohead lw 0.5 lc rgb \"red\" notitle, \
                            'start.temp' with point pointtype 3 ps 2 lc rgb \"blue\" title \'Start Node\', \
                            'end.temp' with point pointtype 3 ps 2 lc rgb \"green\" title \'Goal Node\'\n";
        fprintf(pipe, "%s\n", gnu_command);

        // flush the pipe to update the plot
        fflush(start);
        fflush(end);
        fflush(temp);
        fflush(pipe);
        delay(STEP_DELAY);
    }

    //  Close Files
    fclose(start);
    fclose(end);
    fclose(temp);
    fclose(pipe);

    // Delete Files
    remove("path.temp");
    remove("start.temp");
    remove("end.temp");
    
    // Free Memory
    free(graph);
    free(startNode);
    free(goalNode);

    return status;
}
