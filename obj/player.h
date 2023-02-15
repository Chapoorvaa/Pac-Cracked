#ifndef PLAYER_H
#define PLAYER_H

// This file will handle all the player logic and structs

#include <stddef.h>

#define UP -28
#define DOWN 28
#define LEFT -1
#define RIGHT 1

// Structure of a player.
typedef struct Player {
    size_t x;
    size_t y;
    int lives;
    int direction;
} Player;

#endif
