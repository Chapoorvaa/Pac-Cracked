#include <stddef.h>
#include <stdlib.h>
#include "lib/linked_list.h"
#include "utils.h"
#include "search.h"
#include "../src/map.h"
#include <limits.h>
#include "minimax.h"
#include <stdio.h>

#define WALL '#'
#define WALL2 '_'
#define GRID_HEIGHT 29
#define GRID_WIDTH 27
#define NOT_VISITED -5
#define VISITED 1

int *form_adjlist(int vertex, Map* map){
    int* adj = calloc(4, sizeof(int));
    if (map->grid[vertex + UP] != WALL && map->grid[vertex + UP] != WALL2){
        adj[0] = UP;
    }
        if (map->grid[vertex + LEFT] != WALL && map->grid[vertex + LEFT] != WALL2){
        adj[1] = LEFT;
    }
    if (map->grid[vertex + DOWN] != WALL && map->grid[vertex + DOWN] != WALL2){
        adj[2] = DOWN;
    }
    if (map->grid[vertex + RIGHT] != WALL && map->grid[vertex + RIGHT] != WALL2){
        adj[3] = RIGHT;
    }
    return adj;
}

int bfs(Game *game){
    llist *q = init_llist();
    char *grid = game->map->grid;
    int src = game->pacman->y * ROW + game->pacman->x;
    llist_prepend(q, &src);
    int M[ROW * COL];
    for (int i = 0; i < ROW * COL; i++){
        M[i] = -2;
    }
    M[src] = -1;
    int not_found = -1;
    while ((q->length != 0) && (not_found == -1)){
        int *n = llist_fastpop(q);
        int *adjlist = form_adjlist(*n, game->map);
        for(size_t i = 0; i < 4; i++){
            int adj = adjlist[i];
            if (adj == 0){
                continue;
            }
            char k = grid[adj];
            if (k != ' '){
                not_found = adj;
            }
            if (M[adj] == -2){
                M[adj] = *n;
                llist_prepend(q, &adj);
            }
        }
        free(adjlist);
    }
    int dst = not_found;
    int dir = 0;
    while (dst != src){
        dir = dst;
        dst = M[dst];
    }
    llist_free(q);
    return src - dir;
}

int manhattandist(int x, int y, int i, int j){
    int a = abs(i - x);
    int b = abs(j - y);
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
    printf("x:%d, y:%d\n", lowest % COL, lowest / COL);
    return can_go[lowest_i];
}

int closest(Game *game){
    int inf = INT_MAX;
    int dst[ROW * COL];
    for (size_t j = 0; j < ROW; j++){
        for (size_t i = 0; i < COL; i++){
            if (game->map->grid[i] == '.' || game->map->grid[i] == 'o'){
                int x = game->pacman->x;
                int y = game->pacman->y;
                dst[i] = manhattandist(x, y, i, j);
            } 
            else{
                dst[i] = inf;
            }
        }
    }
    int lowest = min(dst, ROW * COL);
    int *can_go = can_goto(game);
    int c = choose_dir(lowest, can_go);
    free(can_go);
    return c;
}
