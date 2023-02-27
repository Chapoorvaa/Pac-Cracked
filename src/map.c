#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

#define ROW 28
#define COL 36

Map *init_map(){
	Map *map = malloc(sizeof(Map));
	map->grid = calloc(ROW * COL, sizeof(char));
	map->points = 0;
	return map;
}

void free_map(Map* map){
	free(map->grid);
	free(map);
}

Map* load_map(char* path){
	//TODO
	Map *map;
	return map;
}

void save_map(Map* map){
	//TODO
}

void print_map(Map* map) 
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%c", map->grid[i * ROW + j]);
		}
		printf("\n");
	}
}
