#include "ghost.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Ghost* ghostInit(char* label, int direction, int mode,
 int scatterTargetX, int scatterTargetY, int spawnX, int spawnY)
{
    Ghost* ghost = malloc(sizeof(Ghost));
    ghost->name = label;
    ghost->x = spawnX;
    ghost->y = spawnY;
    ghost->direction = direction;
    ghost->mode = mode;
    ghost->targetX = scatterTargetX;
    ghost->targetY = scatterTargetY;
    ghost->scatterTargetX = scatterTargetX;
    ghost->scatterTargetY = scatterTargetY;
    ghost->spawnX = spawnX;
    ghost->spawnY = spawnY;
    return ghost;
}

void move(Ghost* ghost){
    // depending on the direction of the ghost, move it
    switch (ghost->direction)
    {
        case up:
            ghost->y -= 1;
            break;
        case down:
            ghost->y += 1;
            break;
        case left:
            ghost->x -= 1;
            break;
        case right:
            ghost->x += 1;
            break;
    }
}

void GhostMove(Ghost* ghost, Ghost* blinky, char* map, struct Player* player){
    // case where the ghost is still in the ghost house
    if (map[(ghost->y - 1) * COL + ghost->x] == WALL2){
        ghost->y -= 1;
        return;
    }
    if (map[ghost->y * COL + ghost->x] == WALL2){
        ghost->y -= 1;
        return;
    }
    int nb_walls = 0;
    // check if 4 tiles around the ghost are walls
    if (map[(ghost->y - 1) * COL + ghost->x] == WALL ||
            map[(ghost->y - 1) * COL + ghost->x] == WALL2)
        nb_walls++;
    if (map[(ghost->y + 1) * COL + ghost->x] == WALL ||
            map[(ghost->y + 1) * COL + ghost->x] == WALL2)
        nb_walls++;
    if (map[ghost->y * COL + ghost->x - 1] == WALL ||
            map[ghost->y * COL + ghost->x - 1] == WALL2)
        nb_walls++;
    if (map[ghost->y * COL + ghost->x + 1] == WALL ||
            map[ghost->y * COL + ghost->x + 1] == WALL2)
        nb_walls++;
    printf("ghost name: %s, nb_walls: %d, x:%d, y:%d, targetx:%d, targety:%d\n", ghost->name,nb_walls, ghost->x, ghost->y, ghost->targetX, ghost->targetY);
    // if there are 0/1 walls around the ghost then we can use pathing
    // This is basically saying that we are at an intersection
    if (nb_walls <= 1)
        ghostPathing(ghost, blinky, map, player, nb_walls);
    else
        checkWall(ghost, map);
    printf("ghost name: %s, direction: %d\n", ghost->name, ghost->direction);
    move(ghost);
}

// if direction is NULL then we only check the ghost direction
void checkWall(Ghost* ghost, char* map){
    //check the next position of the ghost and if it's a wall then change the direction to the only direction it can go
    switch (ghost->direction)
    {
        case up:
            if(map[((ghost->y - 1) * COL) + ghost->x]== WALL)
            {
                if(map[(ghost->y * COL) + ghost->x - 1] != WALL)
                {
                    ghost->direction = left;
                }
                else if(map[(ghost->y * COL) + ghost->x + 1] != WALL)
                {
                    ghost->direction = right;
                }
            }
            break;
        case down:
            if(map[(ghost->y + 1 * COL) + ghost->x] == WALL)
            {
                if(map[(ghost->y * COL) + ghost->x - 1] != WALL)
                {
                    ghost->direction = left;
                }
                else if(map[(ghost->y * COL) + ghost->x + 1] != WALL)
                {
                    ghost->direction = right;
                }
            }
            break;
        case left:
            if(map[(ghost->y * COL) + ghost->x - 1] == WALL)
            {
                if(map[((ghost->y - 1) * COL) + ghost->x] != WALL)
                {
                    ghost->direction = up;
                }
                else if(map[((ghost->y + 1) * COL) + ghost->x] != WALL)
                {
                    ghost->direction = down;
                }
            }
            break;
        case right:
            if(map[ghost->y * COL + ghost->x + 1] == WALL)
            {
                if(map[((ghost->y - 1) * COL) + ghost->x] != WALL)
                {
                    ghost->direction = up;
                }
                else if(map[((ghost->y + 1) * COL) + ghost->x] != WALL)
                {
                    ghost->direction = down;
                }
            }
            break;
    }
}

void ghostPathing(Ghost* ghost, Ghost* blinky, char* map, 
        Player* player, int nb_walls)
{
    // Depending on the ghost mode, and knowing that the ghost is at an
    // intersection, then choose the direction of the ghost
    switch (ghost->mode)
    {
        case SCATTER:
            // Target the ghost's scatter target
            ghost->targetX = ghost->scatterTargetX;
            ghost->targetY = ghost->scatterTargetY;
            int min_distance = 1000; // arbitrary large number
            //find the shortest path to the target position using
            // the shortest manhattan distance
            switch (ghost->direction)
            {
                // find the smallest heuristic value
                case up:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL &&
                            nb_walls == 1)
                    {
                        int distance = abs(ghost->x - ghost->targetX) + 
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
                case down:
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) + abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
                case left:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    break;
                case right:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
            }
            break;
        case CHASE:
            // Target the ghost's chase target
            if (strcmp(ghost->name, "blinky") == 0)
            {
                ghost->targetX = player->x;
                ghost->targetY = player->y;
            }
            else if (strcmp(ghost->name, "pinky") == 0)
            {
                //depending on the direction of the player
                //target 4 tiles ahead of the player
                switch (player->direction){
                    case up:
                        ghost->targetX = player->x;
                        ghost->targetY = player->y - 4;
                        break;
                    case down:
                        ghost->targetX = player->x;
                        ghost->targetY = player->y + 4;
                        break;
                    case left:
                        ghost->targetX = player->x - 4;
                        ghost->targetY = player->y;
                        break;
                    case right:
                        ghost->targetX = player->x + 4;
                        ghost->targetY = player->y;
                        break;
                }
            }
            else if (strcmp(ghost->name, "inky") == 0)
            {
                int dpx;
                int dpy;
                switch (player->direction){
                    case up:
                        dpx = player->x;
                        dpy = player->y - 2;
                        break;
                    case down:
                        dpx = player->x;
                        dpy = player->y + 2;
                        break;
                    case left:
                        dpx = player->x - 2;
                        dpy = player->y;
                        break;
                    case right:
                        dpx = player->x + 2;
                        dpy = player->y;
                        break;
                }
                int blinkyx = blinky->x;
                int blinkyy = blinky->y;
                ghost->targetX = 2 * dpx - blinkyx;
                ghost->targetY = 2 * dpy - blinkyy;
            }
            else if (strcmp(ghost->name, "clyde") == 0)
            {
                int dx = ghost->x - player->x;
                int dy = ghost->y - player->y;
                if (dx * dx + dy * dy > 64)
                {
                    ghost->targetX = player->x;
                    ghost->targetY = player->y;
                }
                else
                {
                    ghost->targetX = ghost->scatterTargetX;
                    ghost->targetY = ghost->scatterTargetY;
                }
            }
            break;
        case FRIGHTENED:
            // Target a random position
            ghost->targetX = rand() % COL;
            ghost->targetY = rand() % ROW;
            break;
        case DEAD:
            // Target the ghost's spawn position
            ghost->targetX = ghost->spawnX;
            ghost->targetY = ghost->spawnY;
            min_distance = 1000;
            switch (ghost->direction)
            {
                case up:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) + 
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
                case down:
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
                case left:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != WALL)
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = left;
                        }
                    }
                    break;
                case right:
                    if(map[(ghost->y - 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = up;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != WALL)
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = down;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != WALL)
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = right;
                        }
                    }
                    break;
            break;
            }
    }
}
