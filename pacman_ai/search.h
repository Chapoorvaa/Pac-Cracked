#ifndef SEARCH_H
#define SEARCH_H

#include "utils.h"

void bfs(char *grid, struct Stack *stack, int start, int end);
void dfs(char *grid, struct Stack *stack, int start, int end);
void ucs(char *grid, struct Stack *stack, int start, int end);
void astar(char *grid, struct Stack *stack, int start, int end);

#endif
