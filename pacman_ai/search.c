#include <stddef.h>
#include <stdlib.h>
#include "utils.h"

#define WALL '#'
#define GRID_WIDTH 28
#define GRID_HEIGHT 36
#define NOT_VISITED -5
#define VISITED 1

void form_adjlist(int vertex, struct List *adjlist){
    if (vertex % GRID_WIDTH + 1 < GRID_WIDTH){
        append_list(adjlist, vertex + 1);
    }
    if (vertex % GRID_WIDTH - 1 >= 0){
        append_list(adjlist, vertex - 1);
    }
    if (vertex + GRID_WIDTH < GRID_HEIGHT * GRID_WIDTH){
        append_list(adjlist, vertex + GRID_HEIGHT);
    } 
    if (vertex - GRID_WIDTH >= 0){
        append_list(adjlist, vertex - GRID_HEIGHT);
    }
}

void bfs(char *grid, struct Stack *stack, int start, int end){
    int grid_length = GRID_WIDTH * GRID_HEIGHT;
    int M[grid_length];
    for (int i = 0; i <  grid_length; i++){
        M[i] = NOT_VISITED;
    }
    struct Queue *q;
    init_queue(q);
    push_queue(q, start);
    M[start] = -1;
    while (!(is_queue_empty(q) == 1)){
        int n = pop_queue(q);
        if (n == end){
            q->length = 0;
        }
        else{
            struct List *adjlist;
            init_list(adjlist);
            form_adjlist(n, adjlist);
            for (int i = 0; i < adjlist->length; i++){
                int iter = iter_list(adjlist, i);
                if (M[iter] == NOT_VISITED && !(grid[iter] == WALL)){
                   push_queue(q, iter);
                   M[iter] = n;
                }
            }
        }
    }
    struct Stack *s;
    init_stack(s);
    while(M[end] != -1){
        push_stack(s, M[end]);
        end = M[end];
    }
}

int __dfs(char *grid, struct Stack *stack, int start, int end, int *M, int parent){
    M[start] = VISITED;
    struct List *adjlist;
    init_list(adjlist);
    form_adjlist(start, adjlist);
    for (int i = 0; i < adjlist->length; i++){
        int iter = iter_list(adjlist, i);
        if (iter == end){
            push_stack(stack, iter);
            return 1;
        }
        else{
            if (M[iter] == NOT_VISITED && !(grid[iter])){
                if (1 == __dfs(grid, stack, iter, end, M, start)){
                    push_stack(stack, iter);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void dfs(char *grid, struct Stack *stack, int start, int end){
    int grid_length = GRID_HEIGHT * GRID_WIDTH;
    int *M = malloc(sizeof(int) * grid_length);
    for (int i = 0; i < grid_length; i++){
        M[i] = NOT_VISITED;
    }
    __dfs(grid, stack, start, end, M, -1);
}

void ucs(char *grid, struct Stack *stack, int start, int end){
    //TODO - might not be used
}

void astar(char *grid, struct Stack *stack, int start, int end){
    struct Astar_node *start_node, *end_node;
    init_astar_node(start_node, NULL, start);
    init_astar_node(end_node, NULL, end);

    struct Astar_q *open, *close;
    init_astar_q(open);
    init_astar_q(close);
    append_astar(open, start_node);

    while (open->length > 0){
        struct Astar_node *curr_node;
        curr_node = open->q[0];
        int curr_i = 0;
        for (int i = 0; i < open->length; i++){
            if(open->q[i]->f < curr_node->f){
                curr_node = open->q[i];
                curr_i = i;
            }
        }
       
        struct Astar_node *tmp = pop_astar(open, curr_i);
        free_astar_node(tmp);
        append_astar(close, curr_node);

        if (curr_node->position == end_node->position){
           struct Astar_node *curr;
           curr = curr_node;
           while (curr != NULL){
                push_stack(stack, curr->position);
                curr = curr->parent;
           }
           return;
        }

        struct List *adjlist;
        form_adjlist(curr_node->position, adjlist);
        for (int k = 0; k < adjlist->length; k++){
            struct Astar_node *child;
            int iter = iter_list(adjlist, k);
            init_astar_node(child, curr_node, iter);
            if(!(is_in_astar(close, child))){
                child->g = curr_node->g + 1;
                child->h = ((child->position - end_node->position));
                child->f = child->h + child->g;
                if(!(is_in_astar(open, child))){
                    append_astar(open, child);
                }
            }
            else{
                free_astar_node(child);
            }
        }
    }
}
