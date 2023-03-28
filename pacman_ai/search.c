#include <stddef.h>
#include <stdlib.h>
#include "lib/linked_list.h"
#include "utils.h"

#define WALL '#'
#define WALL2 '_'
#define GRID_WIDTH 27
#define GRID_HEIGHT 28
#define NOT_VISITED -5
#define VISITED 1

void form_adjlist(int vertex, llist *adjlist){
    int *n;
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
}

void bfs(char *grid, llist *stack, int start, int end){
    int grid_length = GRID_WIDTH * GRID_HEIGHT;
    int M[grid_length];
    for (int i = 0; i <  grid_length; i++){
        M[i] = NOT_VISITED;
    }
    llist *q;
    init_llist(q);
    llist_prepend(q, &start);
    M[start] = -1;
    while (q->length != 0){
        int *n = llist_fastpop(q);
        if (*n == end){
            q->length = 0;
        }
        else{
            llist *adjlist;
            init_llist(adjlist);
            form_adjlist(*n, adjlist);
            for (int i = 0; i < adjlist->length; i++){
                int *iter = llist_use(adjlist, i);
                if (M[*iter] == NOT_VISITED && !(grid[*iter] == WALL) && !(grid[*iter] == WALL2)){
                   llist_prepend(q, iter);
                   M[*iter] = *n;
                }
            }
        }
    }
    while(M[end] != -1){
        llist_prepend(stack, &M[end]);
        end = M[end];
    }
    
}

int __dfs(char *grid, llist *stack, int start, int end, int *M, int parent){
    M[start] = VISITED;
    llist *adjlist;
    init_llist(adjlist);
    form_adjlist(start, adjlist);
    for (int i = 0; i < adjlist->length; i++){
        int *iter = llist_use(adjlist, i);
        if (*iter == end){
            llist_prepend(stack, iter);
            return 1;
        }
        else{
            if (M[*iter] == NOT_VISITED && !(grid[*iter] == WALL) && !(grid[*iter] == WALL2)){
                if (1 == __dfs(grid, stack, *iter, end, M, start)){
                    llist_prepend(stack, iter);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void dfs(char *grid, llist *stack, int start, int end){
    int grid_length = GRID_HEIGHT * GRID_WIDTH;
    int *M = malloc(sizeof(int) * grid_length);
    for (int i = 0; i < grid_length; i++){
        M[i] = NOT_VISITED;
    }
    __dfs(grid, stack, start, end, M, -1);
}

void ucs(char *grid, llist *stack, int start, int end){
    //TODO - might not be used
}

void astar(char *grid, llist *stack, int start, int end){
    struct Astar_node *start_node, *end_node;
    init_astar_node(start_node, NULL, start);
    init_astar_node(end_node, NULL, end);

    llist *open, *close;
    init_llist(open);
    init_llist(close);
    llist_append(open, start_node);

    while (open->length > 0){
        struct Astar_node *curr_node;
        curr_node = llist_use(open, 0);
        int curr_i = 0;
        for (int i = 0; i < open->length; i++){
            struct Astar_node *tmp = llist_use(open, i);
            if(tmp->f < curr_node->f){
                curr_node = llist_use(open, i);
                curr_i = i;
            }
        }
       
        struct Astar_node *tmp = llist_pop(open, curr_i);
        free_astar_node(tmp);
        llist_append(close, curr_node);

        if (curr_node->position == end_node->position){
           struct Astar_node *curr;
           curr = curr_node;
           while (curr != NULL){
                llist_prepend(stack, &curr->position);
                curr = curr->parent;
           }
           return;
        }

        llist *adjlist;
        form_adjlist(curr_node->position, adjlist);
        for (int k = 0; k < adjlist->length; k++){
            struct Astar_node *child;
            int *iter = llist_use(adjlist, k);
            init_astar_node(child, curr_node, *iter);
            if(!(llist_search(close, child))){
                child->g = curr_node->g + 1;
                child->h = ((child->position - end_node->position));
                child->f = child->h + child->g;
                if(!(llist_search(open, child))){
                    llist_append(open, child);
                }
            }
            else{
                free_astar_node(child);
            }
        }
    }
}
