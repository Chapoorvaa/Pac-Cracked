#ifndef MAP_H
#define MAP_H

#include "../obj/player.h"

typedef struct Map{
    char* grid;
    int points;
}Map;

Map *init_map();

void free_map(Map* map);

Map* load_map(char* path);

void save_map(Map* map, char* name);

void print_map(Map* map, Player* pacman);

#endif
