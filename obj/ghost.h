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
    DEAD
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
void ghostInit(struct Ghost* ghost, char* label, int x, int y, int speed,
 int direction, int mode, int scatterTargetX, int scatterTargetY, int spawnX, int spawnY);

// Check if the ghost is in a intersection and act accordingly
// 1. if it's in a intersection, call ghostPathing
// 2. if it's not in a intersection, and the next position is a wall,
//      change the direction to where the only direction it can go, update the next position + direction
// 3. if it's not in a intersection move the ghost
void ghostMove(struct Ghost* ghost, char** map, struct Player* player);


// This function will use the A* algorithm to find the shortest path to the target position
void Astar(struct Ghost* ghost, char** map);

// This function is called when a ghost is in a intersection
// It will check the ghost's state and target it's next position
//check for it's state:
//  1.1 if it's in scatter mode, target it's assigned corner
//  1.2 if it's in chase mode, depending on the ghost, target the player or a specific position
//  1.3 if it's in frightened mode, target a random position
//  1.4 if it's in dead mode, target the ghost house
void ghostPathing(struct Ghost* ghost, char** map, struct Player* player);

#endif
