#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

/*
Stack Functions:
    - stack_push        TO_TEST
    - stack_pop         TO_TEST
    - is_stack_empty    TO_TEST
    - init_stack        TO_TEST
    - free_stack        TO_TEST
*/

void stack_push(struct Stack *stack, int data){
    *(stack->stack + stack->size) = data;
    stack->size += 1;
}

char stack_pop(struct Stack *stack){
    int n;
    n = *(stack->stack + stack->size - 1);
    *(stack->stack + stack->size - 1) = 0;
    stack->size -= 1;
    return n;
}

int is_stack_empty(struct Stack *stack){
    if (stack->size != 0){
        return 0;
    }
    else{
        return 1;
    }
}

void init_stack(struct Stack *stack){
    stack->stack = calloc(INIT_SIZE, sizeof(int));
    stack->size = 0;
}

void free_stack(struct Stack *stack){
    free(stack->stack);
    free(stack);
}

/*
Queue Functions:
    - queue_push        TO_TEST
    - queue_pop         TO_TEST
    - is_queue_empty    TO_TEST
    - init_queue        TO_TEST
    - free_queue        TO_TEST
*/

void queue_push(struct Queue *queue, int data){
    int i = 0;
    int tmp;
    while (i < queue->length){
        tmp = queue->queue[i];
        queue->queue[i] = data;
        data = tmp;
    }
    queue->length += 1;
}

int queue_pop(struct Queue *queue){
    queue->length -= 1;
    int n;
    n = queue->queue[queue->length];
    return n;
}

int is_queue_empty(struct Queue *queue){
    if (queue->length != 0){
        return 0;
    }
    else{
        return 1;
    }
}

void init_queue(struct Queue *queue){
    queue->queue = calloc(INIT_SIZE, sizeof(int));
    queue->length = 0;
}

void free_queue(struct Queue *queue){
    free(queue->queue);
    free(queue);
}

/*
List and Node Functions:
    List:
    - init_list         TO_TEST
    - append_list       TO_TEST
    - pop_list          TO_TEST
    - free_list         TO_TEST

    Node:
    - init_node         TO_TEST
    - free_node         TO_TEST
*/

void init_node(struct Node *node, int data){
    node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
}

void free_node(struct Node *node){
    free(node);
}

void init_list(struct List *list){
    list = malloc(sizeof(struct List));
    list->length = 0;
    list->list = NULL;
}

void free_list(struct List *list){
    int i = 0;
    struct Node *curr;
    struct Node *last;
    curr = list->list;
    while (i < list->length){
        last = curr;
        curr = curr->next;
        free_node(last);
    }
    free(list);
}

void append_list(struct List *list, int data){
    struct Node *to_add;
    init_node(to_add, data);
    struct Node *tmp = list->list;
    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = to_add;
    list->length += 1;
}

void pop_list(struct List *list, int data){
    struct Node *to_del;
    to_del = list->list;
    while (to_del->next->next != NULL){
        to_del = to_del->next;
    }
    free_node(to_del->next);
    to_del->next = NULL;
}

int iter_list(struct List *list, int i){
    struct Node *tmp;
    tmp = list->list;
    while (i != 0){
        tmp = tmp->next;
    }
    return tmp->data;
}

/*
Astar queue and node Functions
*/

void init_astar_node(struct Astar_node *node, struct Astar_node *parent, int position){
    node->f = 0;
    node->g = 0;
    node->h = 0;
    node->parent = parent;
    node->position = position;
}

void free_astar_node(struct Astar_node *node){
    free(node);
}

void append_astar(struct Astar_q *q, struct Astar_node *node){
    q->q[q->length] = node;
    q->length += 1;
}

struct Astar_node *pop_astar(struct Astar_q *q, int i){
    struct Astar_node *n;
    for (int k = i; k < q->length; k++){
       n = q->q[k+1];
       q->q[k+1] = q->q[k];
       q->q[k] = n;
    }
    n = q->q[q->length];
    q->length -= 1;
    return n;
}

void init_astar_q(struct Astar_q *q){
    q->q = malloc(INIT_SIZE * sizeof(struct Astar_node*));
    q->length = 0;
}

void free_astar_q(struct Astar_q *q){
    free(q->q);
    free(q);
}

int is_in_astar(struct Astar_q *q, struct Astar_node *n){
    for(int i = 0; i < q->length; i++){
        if (q->q[i] == n){
            return 1;
        }
    }
    return 0;
}
