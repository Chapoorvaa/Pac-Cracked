#include <stddef.h>
#include <stdlib.h>
#include "lib/linked_list.h"
#include "utils.h"
#include "search.h"
#include "../src/map.h"
#include <limits.h>
#include "minimax.h"

#define WALL '#'
#define WALL2 '_'
#define GRID_HEIGHT 29
#define GRID_WIDTH 27
#define NOT_VISITED -5
#define VISITED 1

void form_adjlist(int vertex, llist *adjlist){
    int n = 0;
    if (vertex % GRID_WIDTH + 1 < GRID_WIDTH){
        n = vertex + 1;
        llist_append(adjlist, &n);
    }
    if (vertex % GRID_WIDTH - 1 >= 0){
        n = vertex - 1;
        llist_append(adjlist, &n);
    }
    if (vertex + GRID_WIDTH < GRID_HEIGHT * GRID_WIDTH){
        n = vertex + GRID_HEIGHT;
        llist_append(adjlist, &n);
    } 
    if (vertex - GRID_WIDTH >= 0){
        n = vertex - GRID_HEIGHT;
        llist_append(adjlist, &n);
    }
}

int bfs(Game *game){
    llist *q = init_llist();
    char *grid = game->map->grid;
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
            int *adj = llist_use(adjlist, i);
            char k = grid[*adj];
            if (k != ' '){
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
    llist_free(q);
    llist_free(adjlist);
    return src - dir;
}

int manhattandist(int x, int y, int i, int j){
    int a = x - i;
    int b = y - j;
    if (a < 0){
        a = -a;
    }
    if (b < 0){
        b = -b;
    }
    return a + b;
}

int min(int* dst, int len){
    int min_i = 0;
    for(int i = 0; i < len; i++){
        if (dst[min_i] > dst[i]){
            min_i = i;
        }
    }
    return min_i;
}

int abs(int a){
    if (a < 0){
        return -a;
    }
    return a;
}

int choose_dir(int dir, int* can_go){
    int lowest = INT_MAX;
    int lowest_i = 0;
    for (int i = 0; i < 4; i++){
        if (can_go[i] != 0){
            if (abs(dir - can_go[i]) < lowest){
                lowest = dir - can_go[i];
                lowest_i = i;
            }
        }
    }
    return can_go[lowest_i];
}

int closest(Game *game){
    int inf = INT_MAX;
    int dst[ROW * COL];
    for (size_t i = 0; i < ROW * COL; i++){
        if (game->map->grid[i] == '.' || game->map->grid[i] == 'o'){
            int x = game->pacman->x;
            int y = game->pacman->y;
            int i = i % COL;
            int j = j / COL;
            dst[i] = manhattandist(x, y, i, j);
        }
        else{
            dst[i] = inf;
        }
    }
    int lowest = min(dst, ROW * COL);
    int *can_go = can_goto(game);
    return choose_dir(lowest, can_go);
}
