#ifndef GHOST_H
#define GHOST_H

// This file will handle all the ghost ai and structs

// Structure of the ghost AI.
// This file will handle all the ghost ai and structs
#include "player.h"
#include "../src/map.h"

typedef enum GhostMode
{
    SCATTER,
    CHASE,
    FRIGHTENED,
    DEAD,
    IDLE
}GhostMode;


typedef enum GhostDirection
{
	up,
	down,
	left,
	right
}GhostDirection;

typedef struct Ghost
{
    char* name;
    int x;
    int y;
    int speed;
    GhostDirection direction;
    GhostMode mode;
    int targetX;
    int targetY;
    int scatterTargetX;
    int scatterTargetY;
    int spawnX;
    int spawnY;
}Ghost;

typedef struct Ghosts
{
    struct Ghost* blinky;
    struct Ghost* pinky;
    struct Ghost* inky;
    struct Ghost* clyde;
}Ghosts;



// Ghost functions


// Initialize a ghost
Ghost* ghostInit(char* label, int x, int y, int speed,
 int direction, int mode, int scatterTargetX, int scatterTargetY, int spawnX, int spawnY);

// Moves the ghost and checks for collisions + intersections with the map
void GhostMove(Ghost* ghost, Map* map, struct Player* player);

// Just moves the ghost (however no checks are made)
void move(Ghost* ghost);

// Checks if there is a wall in front of the ghost and changes direction
void checkWall(Ghost* ghost, Map* map);

// Checks if the ghost is at an intersection and changes direction
// depending on the ghost's attribute
void ghostPathing(Ghost* ghost, Map* map, struct Player* player);

#endif
