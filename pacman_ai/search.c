#include <stddef.h>
#include "utils.h"

#define WALL '#'
#define GRID_WIDTH 28
#define GRID_HEIGHT 36
#define DIRECTIONS {GRID_WIDTH, -GRID_WIDTH, 1, -1}

void bfs(*grid, *path, start, end){
    int grid_length = GRID_WIDTH * GRID_HEIGHT;
    int M[grid_length];
    int directions[grid_length];
    struct Queue *q;
    init_queue(q);
    queue_push(q, start);
    M[start] = -1;
    while (!(is_queue_empty(q) == 1)){
        int n = queue_pop(q);
    }
}

void dfs(grid, start_x, start_y, end_x, end_y){
    //TODO
}

void ucs(grid, start_x, start_y, end_x, end_y){
    //TODO
}

void astar(grid, start_x, start_y, end_x, end_y){
    //TODO
}
