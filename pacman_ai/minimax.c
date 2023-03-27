#include <stdlib.h>
#include "lib/linked_list.h"
#include "minimax.h"
#include "lib/tree.h"
#include "../main.h"
#include <libc.h>

int *can_goto(Game *game){
	int x = game->pacman->x;
	int y = game->pacman->y;
	int pos = y * 28 + x;
	int* options = calloc(4, sizeof(int));
	char* grid = game->map->grid;
	if(grid[pos + 28] != WALL){
		options[0] = 28;
	}
	if(grid[pos - 28] != WALL){
		options[1] = -28;
	}
	if(grid[pos + 1] != WALL){
		options[2] = 1;
	}
	if(grid[pos - 1] != WALL){
		options[3] = -1;
	}
	return options;
}

gtree *create_tree(Game *game, size_t depth){
	gtree* decision_tree = malloc(sizeof(gtree));
	llist* q = malloc(sizeof(llist));
	q->length = 0;
	decision_tree->key = game;
	int start = game->round;
	llist_prepend(q, decision_tree);
	while (q->length != 0){
		gtree* branch = llist_fastpop(q);
		Game *cur_state = branch->key;
		int *options = can_goto(cur_state);
		if ((cur_state->round != start + depth - 1) && (game_over(cur_state) != 1)){
			for (int i = 0; i < 4; i++){
				if (options[i] != 0){
					Game *new = malloc(sizeof(Game));
					memcpy(new, cur_state, sizeof(Game));
					new->pacman->direction = options[i];
					llist_append(branch->children, new);
					update(new);
					
				}
			}
		}
	}
	return decision_tree;
}

void update_tree(Game *game, gtree *tree){
	if (tree->children->length == 0){
		Game *cur_state = tree->key;
		int *options = can_goto(cur_state);
		if (game_over(cur_state) == 1){
			return;
		}
		for (int i = 0; i < 4; i++){
			if (options[i] != 0){
				Game *new = malloc(sizeof(Game));
				memcpy(new, cur_state, sizeof(Game));
				new->pacman->direction = options[i];
				llist_append(tree->children, new);
				update(new);
			}
		}
	}
	else{
		for (int i = 1; i <= tree->children->length; i++){
			update_tree(game, llist_use(tree->children, i));
		}
	}
}

int make_decision(gtree *tree){
	// TODO
	return 1;
}

int minimax(size_t depth, Game *game){
	// TODO
	return 1;
}

