#ifndef MAPGEN_H
#define MAPGEN_H

#include "../pacman_ai/lib/linked_list.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define num_rows 9
#define num_cols 5

#define ghost_row 3

typedef struct Cell {
    size_t x;
    size_t y;
    int filled;
    int connect[4];
    struct Cell** next;
    int num;
    int group;
} Cell ;

Cell** init_table(); 

void set_ghost_home(Cell** table); 

llist* get_leftmost_empty_cells(Cell** table);

typedef struct State {
    Cell** table;
    struct Cell* cell;
    struct Cell* first_cell;
    int num_filled;
    int num_groups;
    int size;
    int single_count;
} State ;

State* init_state();

void fill_cell(State* state, struct Cell* cell);

int rand_int(int min, int max);

void *rand_element(llist* list);

#define prob_top_and_bot 1

int try_single_cell_group(State* state);

struct Cell* start_new_group(State* state);

State* gen_random_cells();

#endif
