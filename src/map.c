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
	Map *map = malloc(sizeof(Map));
	map->grid = malloc(sizeof(char) * ROW * COL);
	map->points = 0;
	FILE *f;
	f = fopen(path, "r");
	if (f == NULL){
		return NULL;
	}
	fscanf(f, "%[^\n]", map->grid);
	fclose(f);
	return map;
}

void save_map(Map* map, char* name){
	FILE *f = fopen("./%s.txt", name);
	fprintf(f, "%s\n", map->grid);
	fclose(f);
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
