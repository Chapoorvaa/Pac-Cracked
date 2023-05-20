#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "../obj/ghost.h"

#define ROW 29
#define COL 27

Map *init_map(){
	Map *map = malloc(sizeof(Map));
	map->grid = malloc(ROW * COL * sizeof(char));
	map->points = 0;
	return map;
}

void free_map(Map* map){
	free(map->grid);
	free(map);
}

Map* load_map(char* path){
	Map *map = malloc(sizeof(Map));
	map->grid = malloc(sizeof(char) * ROW * COL);
	map->points = 0;
	FILE *f;
	f = fopen(path, "r");
	if (f == NULL){
		return NULL;
	}
    if (fscanf(f, "%[^\n]", map->grid)!= 1) {
        return NULL;
    }
	fclose(f);
	return map;
}

void save_map(Map* map, char* name){
	FILE *f = fopen("./%s.txt", name);
	fprintf(f, "%s\n", map->grid);
	fclose(f);
}


void print_map(Map* map, Player* pacman, llist* ghosts) {
    char grid[ROW * COL];
    for (int i = 0; i < ROW * COL; i++){
        grid[i] = map->grid[i];
    }
    for (size_t i = 0; i < ghosts->length; i++){
        Ghost *ghost = llist_use(ghosts, i);
        if (i == 0){
            grid[ghost->x + ghost->y * COL] = 'b';
        }
        else if (i == 1){
            grid[ghost->x + ghost->y * COL] = 'c';
        }
        else if (i == 2){
            grid[ghost->x + ghost->y * COL] = 'i';
        }
        else if (i == 3){
            grid[ghost->x + ghost->y * COL] = 'p';
        }
    }    grid[pacman->x + pacman->y * COL] = 'P';
	for (int i = 0; i < ROW * COL; i++){
        if (i % COL == 0){
            printf("\n");
        }
        putchar(grid[i]);
    }
    printf("\n");
}
