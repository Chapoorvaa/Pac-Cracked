#ifndef UTILS_H
#define UTILS_H

#define INIT_SIZE 1000

#define NORTH 'w'
#define SOUTH 's'
#define EAST 'd'
#define WEST 'a'

/*
Stack structure:
    - size (int): the amount of items left in the stack
    - stack (int*): the stack containing the information
 */
struct Stack{
    int size;
    int *stack;
};

// Push the param *data* into the *stack* and update the size value.
void push_stack(struct Stack *stack, int data);

// Pop from the *stack* and return *data* at the top of the stack update the size
// value.
char pop_stack(struct Stack *stack);

// Checks if the *stack* is empty if true return 1 else 0. 
int is_stack_empty(struct Stack *stack);

// Init the new empty *stack* with size = 0 and stack[INIT_SIZE]
void init_stack(struct Stack *stack);

// Frees the *stack*
void free_stack(struct Stack *stack);

/*
Queue Structure:
    - length (int): length of the queue
    - queue (int**): queue containing the data in format (int*)
*/
struct Queue{
    int length;
    int *queue;
};

// Push the *data* into the *queue* and update the length
void push_queue(struct Queue *queue, int data);

// Pop the *data* from the end of the *queue* and returns it. update the length
int pop_queue(struct Queue *queue);

// Checks if queue is empty return 1 if true else 0
int is_queue_empty(struct Queue *queue);

// Init the new empty *queue* with length = 0 and queue[INIT_SIZE][2]
void init_queue(struct Queue *queue);

// Frees the queue
void free_queue(struct Queue *queue);

/*
Node Structure:
    - data (int): data in the node 
    - next (struct Node): the next node in the list
*/

struct Node {
    int data;
    struct Node *next;
};

// Initiates the node 
void init_node(struct Node *node, int data);

// Frees the node
void free_node(struct Node *node);

/*
List Structure:
    - length (int): length of the list
    - list (struct Node*): start of the list
*/

struct List{
    int length;
    struct Node *list;
};

// Initiates the list
void init_list(struct List *list);

// Frees the list
void free_list(struct List *list);

// Appends the value data to the end of the list
void append_list(struct List *list, int data);

// Pops the last value in the list and returns its data
void pop_list(struct List *list, int data);

// Iterates i-times in the list and returns the data at position i
int iter_list(struct List *list, int i);

/*
 Node and queue but for the Astar function same properties as a normal queue
 just different data type.
 */

struct Astar_node{
    struct Astar_node *parent;
    int position;
    int g, h, f;
};

void init_astar_node(struct Astar_node *node, struct Astar_node *parent, int position);

void free_astar_node(struct Astar_node *node);

struct Astar_q{
    int length;
    struct Astar_node **q;
};

void append_astar(struct Astar_q *q, struct Astar_node *node);

struct Astar_node *pop_astar(struct Astar_q *q, int i);

void init_astar_q(struct Astar_q *q);

void free_astar_q(struct Astar_q *q);

int is_in_astar(struct Astar_q *q, struct Astar_node *n);
#endif
