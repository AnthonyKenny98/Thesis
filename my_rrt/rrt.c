/*
* @Author: AnthonyKenny98
* @Date:   2019-10-31 11:57:52
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2019-10-31 12:29:56
*/

#include "rrt.h"

double distance(point_t p1, point_t p2) {
    return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
}

int main() {
    point_t p1 = {.x=0.0, .y=0.0};
    point_t p2 = {.x=3.0, .y=4.0};
    double test = distance(p1, p2);
    printf("%f\n", test);
    return 0;
}