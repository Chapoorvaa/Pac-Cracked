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

void stack_push(struct Stack *stack, char data){
    *(stack->stack + stack->size) = data;
    stack->size += 1;
}

char stack_pop(struct Stack *stack){
    char n;
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
    stack->stack = calloc(INIT_SIZE, sizeof(char));
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

