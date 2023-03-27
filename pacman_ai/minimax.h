#ifndef MINIMAX_H
#define MINIMAX_H

#include <stddef.h>
#include "lib/tree.h"
#include "../main.h"

/*
 * Reward enum:
 *  - on pacman death -100
 *  - on game loss -1000
 *  - when pacman eats a point +10
 *  - when pacman eats a power pellet +100
 *  - when pacman eats a ghost +20
 */
enum Rewards {
    death = -100,
    loss = -1000,
    eat_tictac = 10,
    eat_powerup = 100,
    eat_ghost = 20,
};

gtree *create_tree(Game *game, size_t depth);

void update_tree(Game *game, gtree *tree);

int make_decision(gtree *tree);

// Using a decision tree decide pacmans next movement
int minimax(size_t depth, Game *game);
/*
 * - Create decision tree
 * - Create initial state node
 * - Start making the tree:
 *   . Get all directions pacman can go to
 *   . Get all ghost movement and update
 *   . Set the amount of points at that point in the gamestate
 *      *redo till depth hits 1*
 * - Retrace path and set direction
 * - Return the direction
 */
#endif
