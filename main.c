#include "main.h"
#include "obj/ghost.h"
#include "obj/player.h"
#include "pacman_ai/lib/linked_list.h"
#include "pacman_ai/minimax.h"
#include "src/map.h"
#include <stdlib.h>

llist* init_ghosts(int difficulty){
	//TODO
	llist *ghosts;
	return ghosts;
}

void init_game(Game* game, int is_ai, int difficulty, char* map_load){
    game = malloc(sizeof(Game));
    game->difficulty = difficulty;
    if (map_load != NULL){
        game->map = load_map(map_load);
    }
    else{
        game->map = init_map();
    }
    game->pacman = init_player();
    game->ghosts = init_ghosts(difficulty);
    game->is_ai = is_ai;
	game->round = 0;
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
		ghost_location += ghost->direction;
		// check if pacman and ghost overlap and do what is needed
		if (ghost_location == pac_location){
			if (ghost->mode == SCATTER || ghost->mode == CHASE){
				player_respawn(game->pacman);	
			}
			else{
				if (ghost->mode == FRIGHTENED){
					// TODO
					// ADD THE POINTS IF EATEN OR IF PACMAN EATS A GHOST
					// ALSO ADD THE POINTS FOR LOSS OF LIFE AND GAME OVER
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
    //TODO: add SDL OBJECTS

    // - Launch the SDL Interface
    // - On Play Button Click
    // - Select Difficulty and if want to load map
    // - Select pacman is played by ai or human
    // - Load gameplay loop:
    //   .Generate / Load map
    //   .Init player and ghosts
	int is_ai;
	int difficulty;
	char* map_load;
	Game* game;
	init_game(game, is_ai, difficulty, map_load);
	while (game_over(game) == 0){
    //   .Start Gameplay loop (while not_won):
    //      _Print Board
		print_map(game->map);
    //      _Update Ghost Direction
    //      _Update Pacman Direction
    //      _Update location
    //      _Update Score
		update(game);
	}
    // - When game done ask if player wants to save map
	// - Ask for save file name TODO
	char* name;
	int save;
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
