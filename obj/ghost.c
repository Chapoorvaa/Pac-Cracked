#include "ghost.h"

Ghost* ghostInit(char* label, int x, int y, int speed, int direction, int mode,
 int scatterTargetX, int scatterTargetY, int spawnX, int spawnY)
{
    Ghost* ghost = malloc(sizeof(Ghost));
    ghost->name = label;
    ghost->x = spawnX;
    ghost->y = spawnY;
    ghost->speed = speed;
    ghost->direction = direction;
    ghost->mode = mode
    ghost->targetX = spawnX;
    ghost->targetY = spawnY;
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
        case UP:
            ghost->y -= 1;
            break;
        case DOWN:
            ghost->y += 1;
            break;
        case LEFT:
            ghost->x -= 1;
            break;
        case RIGHT:
            ghost->x += 1;
            break;
    }
}

void GhostMove(Ghost* ghost, Map* map, struct Player* player){
    // check if the ghost is in an intersection
    if (map->grid[(ghost->y * COL) + ghost->x] == 'D' ||
        map->grid[(ghost->y * COL) + ghost->x] == '4' ||
        map->grid[(ghost->y * COL) + ghost->x] == '3' ||
        map->grid[(ghost->y * COL) + ghost->x] == 'E')
        ghostPathing(ghost, map, player);
    else
        checkWall(ghost, map);
    move(ghost);
}

// if direction is NULL then we only check the ghost direction
void checkWall(Ghost* ghost, Map* map){
    //check the next position of the ghost and if it's a wall then change the direction to the only direction it can go
    switch (ghost->direction)
    {
        case UP:
            if(map->grid[((ghost->y - 1) * COL) + ghost->x]== 'X')
            {
                if(map->grid[(ghost->y * COL) + ghost->x - 1] != 'X')
                {
                    ghost->direction = LEFT;
                }
                else if(map->grid[(ghost->y * COL) + ghost->x + 1] != 'X')
                {
                    ghost->direction = RIGHT;
                }
            }
            break;
        case DOWN:
            if(map->grid[(ghost->y + 1 * COL) + ghost->x] == 'X')
            {
                if(map->grid[(ghost->y * COL) + ghost->x - 1] != 'X')
                {
                    ghost->direction = LEFT;
                }
                else if(map->grid[(ghost->y * COL) + ghost->x + 1] != 'X')
                {
                    ghost->direction = RIGHT;
                }
            }
            break;
        case LEFT:
            if(map->grid[(ghost->y * COL) + ghost->x - 1] == 'X')
            {
                if(map->grid[((ghost->y - 1) * COL) + ghost->x] != 'X')
                {
                    ghost->direction = UP;
                }
                else if(map->grid[((ghost->y + 1) * COL) + ghost->x] != 'X')
                {
                    ghost->direction = DOWN;
                }
            }
            break;
        case RIGHT:
            if(map->grid[ghost->y * COL + ghost->x + 1] == 'X')
            {
                if(map->grid[((ghost->y - 1) * COL) + ghost->x] != 'X')
                {
                    ghost->direction = UP;
                }
                else if(map->grid[((ghost->y + 1) * COL) + ghost->x] != 'X')
                {
                    ghost->direction = DOWN;
                }
            }
            break;
    }
}

void ghostPathing(Ghost* ghost, char** map, struct Player* player)
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
            //find the shortest path to the target position using shortest manhattan distance
            switch (ghost->direction)
            {
                // find the smallest heuristic value
                case UP:
                    if(map->grid[(ghost->y - 1) * COL + ghost->x] != 'X' &&
                            (map->grid[ghost->y * COL + ghost->x] != '4' ||
                             map->grid[ghost->y * COL + ghost->x] != 'E'))
                    {
                        int distance = abs(ghost->x - ghost->targetX) + 
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map->grid[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                    if(map->grid[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
                case DOWN:
                    if(map->grid[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) + abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
                case LEFT:
                    if(map[(ghost->y - 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                case RIGHT:
                    if(map[(ghost->y - 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
            }
            break;
        case CHASE:
            // Target the ghost's chase target
            if (strcmp(ghost->name, "blinky") == 0)
            {
                ghost->targetX = pacman->x;
                ghost->targetY = pacman->y;
            }
            else if (strcmp(ghost->name, "pinky") == 0)
            {
                ghost->targetX = pacman->x + 4 * pacman->directionX;
                ghost->targetY = pacman->y + 4 * pacman->directionY;
            }
            else if (strcmp(ghost->name, "inky") == 0)
            {
                ghost->targetX = pacman->x + 2 * pacman->directionX;
                ghost->targetY = pacman->y + 2 * pacman->directionY;
                int dx = ghost->x - ghost->targetX;
                int dy = ghost->y - ghost->targetY;
                ghost->targetX += dx;
                ghost->targetY += dy;
            }
            else if (strcmp(ghost->name, "clyde") == 0)
            {
                int dx = ghost->x - pacman->x;
                int dy = ghost->y - pacman->y;
                if (dx * dx + dy * dy > 64)
                {
                    ghost->targetX = pacman->x;
                    ghost->targetY = pacman->y;
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
            ghost->targetX = rand() % 28;
            ghost->targetY = rand() % 36;
            break;
        case DEAD:
            // Target the ghost's spawn position
            ghost->targetX = ghost->spawnX;
            ghost->targetY = ghost->spawnY;
            int min_distance = 1000;
            switch (ghost->direction)
            {
                case UP:
                    if(map[(ghost->y - 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) + 
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
                case DOWN:
                    if(map[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
                case LEFT:
                    if(map[(ghost->y - 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x - 1] != 'X')
                    {
                        int distance = abs(ghost->x - 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = LEFT;
                        }
                    }
                    break;
                case RIGHT:
                    if(map[(ghost->y - 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y - 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = UP;
                        }
                    }
                    if(map[(ghost->y + 1) * COL + ghost->x] != 'X')
                    {
                        int distance = abs(ghost->x - ghost->targetX) +
                            abs(ghost->y + 1 - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = DOWN;
                        }
                    }
                    if(map[ghost->y * COL + ghost->x + 1] != 'X')
                    {
                        int distance = abs(ghost->x + 1 - ghost->targetX) +
                            abs(ghost->y - ghost->targetY);
                        if(distance < min_distance)
                        {
                            min_distance = distance;
                            ghost->direction = RIGHT;
                        }
                    }
                    break;
            break;


    }
    
    
}
