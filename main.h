#ifndef MAIN_H
#define MAIN_H

#include "pacman_ai/search.h"
#include "pacman_ai/minimax.h"
#include "obj/ghost.h"
#include "obj/player.h"
#include "src/map.h"
#include "pacman_ai/lib/linked_list.h"

#define ROW 32
#define COL 28

#define POWER_PELLET 500
#define TICTAC 10
#define WALL '#'

#define PEACEFULL 0
#define EASY 2
#define HARD 4

typedef struct Game{
    int difficulty;
    int is_ai;
    Player* pacman;
    Map* map;
    llist* ghosts;
} Game;

#endif
