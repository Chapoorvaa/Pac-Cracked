#ifndef MAIN_H
#define MAIN_H

#include "obj/ghost.h"
#include "obj/player.h"
#include "src/map.h"
#include "pacman_ai/lib/linked_list.h"

#define ROW 29
#define COL 27

#define POWER_PELLET 500
#define TICTAC 10
#define EAT_GHOST 200
#define DEATH -100
#define GAME_OVER -10000

#define WALL '#'
#define WALL2 '_'

#define PEACEFULL 0
#define EASY 2
#define HARD 4

#define KEY_UP 122
#define KEY_DOWN 115
#define KEY_LEFT 113
#define KEY_RIGHT 100

typedef struct Game{
	int round;
    int difficulty;
    int is_ai;
    Player* pacman;
    Map* map;
    llist* ghosts;
} Game;

llist* init_ghosts(int difficulty);

Game *init_game(int is_ai, int difficulty, int map_load);

void free_game(Game* game);

int game_over(Game* game);

void update(Game* game);

#endif
