/*
* @Author: AnthonyKenny98
* @Date:   2019-11-01 15:45:21
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2019-11-01 15:53:43
*/

#include "tools.h"

// Delay in milliseconds
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

// Returns a Random Double
double randomDouble(int max) {
    return ((double)rand() / (double)RAND_MAX) * max;
}