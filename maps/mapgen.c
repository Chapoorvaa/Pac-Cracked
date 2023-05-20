#include "mapgen.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../pacman_ai/lib/linked_list.c"

#define FALSE 0
#define TRUE 1

Cell* init_cell(int x, int y){
    Cell* cell = malloc(sizeof(Cell));
    cell->x = x;
    cell->y = y;
    cell->filled = FALSE;
    for (int i = 0; i < 4; i++){
        cell->connect[i] = FALSE;
    }
    cell->next = malloc(sizeof(Cell*)*4);
    for(int i = 0; i < 4; i++){
        cell->next[i] = NULL;
    }
    cell->num = -1;
    cell->group = -1;
    return cell;
};

Cell** init_table(){
    Cell** table = malloc(sizeof(Cell*) * num_cols * num_rows);
    Cell** cells = malloc(sizeof(Cell*) * num_cols * num_rows);
    for (int y = 0; y < num_rows; y++){
        for (int x = 0; x < num_cols; x++){
            Cell* cell = init_cell(x, y);
            table[y * num_cols + x] = cell;
            cells[y * num_cols + x] = cell; 
        }
    }

    for (int i = 0; i < num_cols * num_rows; i++){
        Cell* cell = cells[i];
        int x = cell->x;
        int y = cell->y;
        if (x > 0) cell->next[LEFT] = table[y * num_cols + x - 1];
        if (x < num_cols - 1) cell->next[RIGHT] = table[y * num_cols + x + 1];
        if (y > 0) cell->next[UP] = table[(y - 1) * num_cols + x];
        if (y < num_rows - 1) cell->next[DOWN] = table[(y + 1) * num_cols + x];
    }

    set_ghost_home(table);

    return table;
}; 

void set_ghost_home(Cell** table){
    Cell* c;

    c = table[ghost_row * num_cols];
    c->filled = TRUE;
    c->connect[LEFT] = TRUE;
    c->connect[RIGHT] = TRUE;
    c->connect[DOWN] = TRUE;
    
    c = table[ghost_row * num_cols + 1];
    c->filled = TRUE;
    c->connect[LEFT] = TRUE;
    c->connect[DOWN] = TRUE;

    c = table[(ghost_row + 1) * num_cols];
    c->filled = TRUE;
    c->connect[LEFT] = TRUE;
    c->connect[UP] = TRUE;
    c->connect[RIGHT] = TRUE;

    c = table[(ghost_row + 1) * num_cols + 1];
    c->filled = TRUE;
    c->connect[UP] = TRUE;
    c->connect[LEFT] = TRUE;
}; 

llist* get_leftmost_empty_cells(Cell** table){
    llist* left_cells = init_llist();
    for (int x = 0; x < num_cols; x++){
        for (int y = 0; y < num_rows; y++){
            Cell* c = table[y * num_cols + x];
            if (c->filled == FALSE) llist_append(left_cells, c);
        }
        if (left_cells->length > 0) break;
    }
    return left_cells;
};

State* init_state(){
    State* state = malloc(sizeof(State));
    state->table = init_table();

    state->cell = NULL;
    state->first_cell = NULL;

    state->num_filled = 0;
    state->num_groups = 0;

    state->size = 0;
    for (int i = 0; i < num_rows; i++){
        Cell* c1 = state->table[i * num_cols];
        Cell* c2 = state->table[i * num_cols + num_cols - 1];
        if (c1->filled == FALSE) state->single_count++;
        if (c2->filled == FALSE) state->single_count++;
    }

    return state;
};

void fill_cell(State* state, Cell* cell){
    cell->filled = TRUE;
    cell->num = state->num_filled++;
    cell->group = state->num_groups;
};

int rand_int(int min, int max){
    srand(time(NULL));
    int x = rand() % (max - min) + min;
    return x;
};

void *rand_element(llist* list){
   if (list->length > 0) return llist_use(list, rand_int(0, list->length));
   return NULL;
};

int try_single_cell_group(State* state){
    //TODO
    return 0;
};

Cell* start_new_group(State* state){
    Cell** table = state->table;
    llist* open_cells = get_leftmost_empty_cells(table);
    Cell* cell = rand_element(open_cells);
    if (cell != NULL) {
        fill_cell(state, cell);
        state->first_cell = cell;
        state->cell = cell;
        return cell;
    }
    return NULL;
};

State* gen_random_cells(){
    State* state = init_state();
    while (TRUE){
        Cell* cell = start_new_group(state);
        if (cell == NULL){
            break;
        }
        //if (try_single_cell_group(state)){
        //  continue;
        //}

        state->size = 1;
        if (cell->x == num_cols - 1) {
            cell->connect[RIGHT] = TRUE;
            continue;
        }
        break;

        state->num_groups++;
    }
    return state;
};

char* make_map(){
    State* state = gen_random_cells();
    Cell** table = state->table;
    char* map = malloc(sizeof(char) * num_rows * num_cols * 2);
    for (int j = 0; j < num_rows; j++){
        for (int i = 0; i < num_cols; i++){
            if (table[j * num_cols + i]->filled){
                map[num_cols + i + j * num_cols] = '#';
                map[num_cols - i + j * num_cols] = '#';
            }
            else{
                map[num_cols + i + j * num_cols] = ' ';
                map[num_cols - i + j * num_cols] = ' ';
            }
        }
    }
    return map;
}


int main(){
    char* map = make_map();
    for (int j = 0; j < num_rows; j++){
        for (int i = 0; i < num_cols * 2; i++){
            printf("%c", map[j * num_cols * 2 + i]);
        }
        printf("\n");
    }
    return 1;
}

