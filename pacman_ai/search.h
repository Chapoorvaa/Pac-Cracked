#ifndef SEARCH_H
#define SEARCH_H

#include "utils.h"

// bfs traversal of the grid and adds the coords of the path to reach the end
// in the stack
void bfs(char *grid, struct Stack *stack, int start, int end);

// dfs traversal of the grid and adds the coords of the path to reach the end
// in the stack
void dfs(char *grid, struct Stack *stack, int start, int end);

// uniform cost search
// TODO
void ucs(char *grid, struct Stack *stack, int start, int end);

// a star seach
// TODO
void astar(char *grid, struct Stack *stack, int start, int end);

#endif
