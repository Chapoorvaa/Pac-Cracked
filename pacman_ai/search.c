#include <stddef.h>
#include <stdlib.h>
#include "lib/linked_list.h"
#include "utils.h"
#include "search.h"
#include "../src/map.c"

#define WALL '#'
#define WALL2 '_'
#define GRID_WIDTH 29
#define GRID_HEIGHT 27
#define NOT_VISITED -5
#define VISITED 1

void form_adjlist(int vertex, llist *adjlist){
    int *n = malloc(sizeof(int));
    if (vertex % GRID_WIDTH + 1 < GRID_WIDTH){
        *n = vertex + 1;
        llist_append(adjlist, n);
    }
    if (vertex % GRID_WIDTH - 1 >= 0){
        *n = vertex - 1;
        llist_append(adjlist, n);
    }
    if (vertex + GRID_WIDTH < GRID_HEIGHT * GRID_WIDTH){
        *n = vertex + GRID_HEIGHT;
        llist_append(adjlist, n);
    } 
    if (vertex - GRID_WIDTH >= 0){
        *n = vertex - GRID_HEIGHT;
        llist_append(adjlist, n);
    }
    free(n);
}

int bfs(Game *game){
    llist *q = init_llist();
    char* grid = game->map->grid;
    int src = game->pacman->y * ROW + game->pacman->x;
    llist_prepend(q, &src);
    llist *adjlist = init_llist();
    int M[ROW * COL];
    for (int i = 0; i < ROW * COL; i++){
        M[i] = -2;
    }
    M[src] = -1;
    int not_found = -1;
    while ((q->length != 0) && (not_found == -1)){
        int *n = llist_fastpop(q);
        form_adjlist(*n, adjlist);
        for(size_t i = 0; i < adjlist->length; i++){
            int *adj = (llist_use(adjlist, i));
            char k = grid[*adj];
            if (k == '.'){
                not_found = *adj;
            }
            if (M[*adj] == -2){
                M[*adj] = *n;
                llist_prepend(q, adj);
            }
        }
    }
    int dst = not_found;
    int dir = 0;
    while (dst != src){
        dir = dst;
        dst = M[dst];
    }
    return src - dir;
}

