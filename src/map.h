#ifndef MAP_H
#define MAP_H

typedef struct Map{
    char* grid;
    int points;
}Map;

Map *init_map();

void free_map(Map* map);

Map* load_map(char* path);

void save_map(Map* map);

void print_map(Map* map);

#endif
