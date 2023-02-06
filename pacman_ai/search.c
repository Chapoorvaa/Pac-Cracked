#include <stddef.h>
#include "utils.h"

#define WALL '#'
#define GRID_WIDTH 28
#define GRID_HEIGHT 36
#define DIRECTIONS {GRID_WIDTH, -GRID_WIDTH, 1, -1}
#define NOT_VISITED -5

void bfs(char *grid, struct Stack *stack, int start, int end){
    int grid_length = GRID_WIDTH * GRID_HEIGHT;
    int M[grid_length];
    for (int i = 0; i <  grid_length; i++){
        M[i] = NOT_VISITED;
    }
    char directions[grid_length];
    struct Queue *q;
    init_queue(q);
    queue_push(q, start);
    M[start] = -1;
    while (!(is_queue_empty(q) == 1)){
        int n = queue_pop(q);
        //TODO make while loop
    }

    struct Stack *s;
    init_stack(s);
    while(M[end] != -1){
        push_stack(s, directions[end]);
        end = M[end];
    }
}

int __dfs(char *grid, struct Stack *stack, int start,
        int end, int *M, char *directions, int parent){
    M[start] = parent;
    while(1){
    //TODO while loop
    }
    return 1;
}

void dfs(char *grid, struct Stack *stack, int start, int end){
    int grid_length = GRID_HEIGHT * GRID_WIDTH;
    int *M = malloc(sizeof(int) * grid_length);
    for (int i = 0; i < grid_length; i++){
        M[i] = NOT_VISITED;
    }
    char *directions = malloc(sizeof(char) * grid_length);
    __dfs(grid, stack, start, end, M, directions, -1);
}

void ucs(char *grid, struct Stack *stack, int start, int end){
    //TODO
}

void astar(char *grid, struct Stack *stack, int start, int end){
    //TODO
}
