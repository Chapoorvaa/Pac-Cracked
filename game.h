#ifndef "GAME_H"
#define "GAME_H"

#include "obj/ghost.h"
#include "obj/player.h"
#include "src/map.h"
#include "pacman_ai/lib/linked_list.h"

#define PEACEFULL 0
#define EASY 2
#define HARD 4

typedef struct Game{
    size_t difficulty;
    int is_ai;
    Player* pacman;
    Map* grid;
    llist* ghosts;
} Game;

#endif
