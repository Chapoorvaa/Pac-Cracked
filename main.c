#include "main.h"
#include "obj/ghost.h"
#include "obj/player.h"
#include "pacman_ai/lib/linked_list.h"
#include "pacman_ai/minimax.h"
#include "src/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pacman_ai/search.h"

llist* init_ghosts(int difficulty){
    // if difficulty is easy init 2 ghosts
    // if hard init 4
    // peacefull init 0 
    llist *ghosts;
    init_llist(ghosts);
    if (difficulty == PEACEFULL){
        return ghosts;
    }
    // The coords (13, 13) should be the coords just under the door of the ghost
    // house
    else if (difficulty == EASY){
        Ghost* blinky = ghostInit("blinky", left, SCATTER, ROW, 0, 13, 13);
        Ghost* clyde = ghostInit("clyde", left, SCATTER, 0, COL, 13, 13);
        llist_append(ghosts, blinky);
        llist_append(ghosts, clyde);
        return ghosts;
    }
    else{
        Ghost* blinky = ghostInit("blinky", left, SCATTER, ROW, 0, 13, 13);
        Ghost* clyde = ghostInit("clyde", left, SCATTER, 0, COL, 13, 13);
        Ghost* inky = ghostInit("inky", right, SCATTER, 0, 0, 13, 13);
        Ghost* pinky = ghostInit("pinky", right, SCATTER, ROW, COL, 13, 13);
        llist_append(ghosts, blinky);
        llist_append(ghosts, clyde);
        llist_append(ghosts, inky);
        llist_append(ghosts, pinky);
        return ghosts;
    }
}

Game *init_game(int is_ai, int difficulty, int map_load){
    Game *game;
    game = malloc(sizeof(Game));
    game->difficulty = difficulty;
    if (map_load != 1){
        game->map = load_map("./maps/map_1.txt");
    }
    else{
        game->map = init_map();
    }
    game->pacman = init_player();
    game->ghosts = init_ghosts(difficulty);
    game->is_ai = is_ai;
	game->round = 0;
    return game;
}

void free_game(Game* game){
	llist_free(game->ghosts);
	free_map(game->map);
	free_player(game->pacman);
	free(game);	
}

int game_over(Game* game){
    if (game->pacman->lives == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void update(Game* game){
    // check each entities direction and update x and y values accordingly
	int x = game->pacman->x;
	int y = game->pacman->y;
	int pac_location = y * ROW + x;
	if (game->map->grid[pac_location + game->pacman->direction] != WALL){
		pac_location += game->pacman->direction;
		game->pacman->x = pac_location % ROW;
		game->pacman->y = pac_location / ROW;
	}
	for (size_t i = 0; i < game->ghosts->length; i++){
		Ghost *ghost = llist_use(game->ghosts, i);
		int ghost_location = ghost->x + ROW * ghost->y;
		// check if pacman and ghost overlap and do what is needed
		if (ghost_location == pac_location){
			if (ghost->mode == SCATTER || ghost->mode == CHASE){
				player_respawn(game->pacman);
				game->pacman->lives--;
				game->map->points += DEATH;
				if (game_over(game)){
					game->map->points += GAME_OVER;
				}
			}
			else{
				if (ghost->mode == FRIGHTENED){
					game->map->points += EAT_GHOST;
					ghost->mode = DEAD;
				}
			}
		}
	}
	// update score if needed and remove objects if needed
	if (game->map->grid[pac_location] != ' '){
		if (game->map->grid[pac_location] == '.'){
			game->map->points += TICTAC;
		}
		else{
			game->map->points += POWER_PELLET;
		}
		game->map->grid[pac_location] = ' ';
	}
	game->round++;
}

int main(){
    // - Launch the SDL Interface
    // - On Play Button Click
    // - Select Difficulty and if want to load map
    // - Select pacman is played by ai or human
    // - Load gameplay loop:
    //   .Generate / Load map
    //   .Init player and ghosts
	int is_ai = 0;
	int difficulty = 0;
	int map_load = 0;
	Game* game = init_game(is_ai, difficulty, map_load);
	gtree* minimax_tree;
    llist *ghosts = init_ghosts(difficulty);
	if (game->is_ai == 1){
		minimax_tree = create_tree(game, 6);
	}
	while (game_over(game) == 0){
    //   .Start Gameplay loop (while not_won):
    //      _Print Board
		print_map(game->map);
    //      _Update Ghost Direction
    //      _Update Pacman Direction
    //      _Update location
    //      _Update Score
		if (game->is_ai != 1){
			update(game);
		}
		else{
            switch (game->difficulty) {
                case PEACEFULL:
                    game->pacman->direction = bfs(game);
                    break;
                case EASY:
			        minimax_tree = minimax(minimax_tree);
                    Game *g = minimax_tree->key;
		        	game->pacman = g->pacman;                    
                    break;
                case HARD:
			        minimax_tree = minimax(minimax_tree);
                    Game *ga = minimax_tree->key;
		        	game->pacman = ga->pacman;  
                    break;
            }
            for (size_t i = 0; i < ghosts->length; i++){
                GhostMove(llist_use(ghosts, i), game->map, game->pacman);
            }
            update(game);
		}
		// Force prints to stdout
		fflush(stdout);
		// Makes loop sleep for 1s
		sleep(1);
	}
	free_minimax(minimax_tree);
    // - When game done ask if player wants to save map
	// - Ask for save file name TODO
	char name[128];
	int save = 0;
	if (save == 1){
		save_map(game->map, name);
	}
    // - Free all game assets
	free_game(game);
    // - End game screen with score, replay button, close game button
    // - If close:
    //   .Close SDL window
    //   .Destroy all elements
	return 1;
}
