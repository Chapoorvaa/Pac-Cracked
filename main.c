#include "main.h"
#include "obj/ghost.h"
#include "obj/player.h"
#include "pacman_ai/lib/linked_list.h"
#include "pacman_ai/minimax.h"
#include "src/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "pacman_ai/search.h"

char DEFAULT_MAP[] = {"############################............#............##.####.#####.#.#####.####.##o####.#####.#.#####.####o##.####.#####.#.#####.####.##.........................##.####.##.#######.##.####.##.####.##.#######.##.####.##......##....#....##......#######.##### # #####.######     #.##### # #####.#          #.##         ##.#          #.## ###_### ##.#          #.   #     #   .#          #.## ####### ##.#          #.##         ##.#          #.## ####### ##.#     ######.## ####### ##.#######............#............##.####.#####.#.#####.####.##.####.#####.#.#####.####.##o..##...............##..o####.##.##.#######.##.##.######.##.##.#######.##.##.####......##....#....##......##.##########.#.##########.##.##########.#.##########.##.........................############################"};

llist* init_ghosts(int difficulty){
    // if difficulty is easy init 2 ghosts
    // if hard init 4
    // peacefull init 0 
    llist *ghosts = init_llist();
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

// get input from keyboard
int getch(){
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

// case for arrow keys but not ready yet
int get_input(){
    int input = getch();
    if (input == 27){
        input = getch();
        if (input == 91){
            input = getch();
            return input;
        }
    }
    return input;
}

Game *init_game(int is_ai, int difficulty, int map_load){
    Game *game;
    game = malloc(sizeof(Game));
    game->difficulty = difficulty;
    if (map_load != 0){
        //game->map = load_map("./maps/map_1.txt");
        Map *map = malloc(sizeof(Map));
        map->grid = malloc(sizeof(char) * (ROW * COL));
        map->points = 0;
        for(size_t i = 0; i < ROW * COL; i++){
            map->grid[i] = DEFAULT_MAP[i];
        }
        game->map = map;
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
	int pac_location = y * COL + x;
    //check if the next position for pacman is valid
    if (game->map->grid[pac_location + game->pacman->direction] != WALL &&
        game->map->grid[pac_location + game->pacman->direction] != WALL2){
        pac_location += game->pacman->direction;
    }
	game->pacman->x = pac_location % COL;
	game->pacman->y = pac_location / COL;
	for (size_t i = 0; i < game->ghosts->length; i++){
		Ghost *ghost = llist_use(game->ghosts, i);
		int ghost_location = ghost->x + COL * ghost->y;
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

int all_eaten(Game *game){
    int f = 0;
    int i = 0;
    while (i < ROW * COL && f != 1){
        char c = game->map->grid[i];
        if (c == '.' || c == 'o'){
            f = 1;
        }
        i++;
    }
    return f;
}

int main(int argc, char** argv){
    if (argc != 3){
        printf("Usage: ./pacman [difficulty] [is_ai]\n");
        exit(EXIT_FAILURE);
    }
    // - Launch the SDL Interface
    // - On Play Button Click
    // - Select Difficulty and if want to load map
    // - Select pacman is played by ai or human
    // - Load gameplay loop:
    //   .Generate / Load map
    //   .Init player and ghosts
	int is_ai = argv[2][0] - '0';
	int difficulty = argv[1][0] - '0';
	int map_load = 1;
    int ch = 0;
    int prev_ch = 0;
    printf("Initiating game...\n");
	Game* game = init_game(is_ai, difficulty, map_load);
	gtree* minimax_tree = NULL;
    printf("Initiating extra assets...\n");
	if (game->is_ai == 1 && difficulty > 2){
		minimax_tree = create_tree(game, 6);
	}
    printf("Starting game...\n");
	while (game_over(game) == 0 && all_eaten(game) == 1){
    //   .Start Gameplay loop (while not_won):
    //      _Print Board
        printf("Score: %d\n", game->map->points);
        print_map(game->map, game->pacman, game->ghosts);
		fflush(stdout);
    //      _Update Ghost Direction
    //      _Update Pacman Direction
    //      _Update location
    //      _Update Score
        printf("Updating game state...\n");
		if (game->is_ai != 1){
            ch = get_input();
            if (ch == 0){
                ch = prev_ch;
                printf("No input detected, using previous input\n");
            }
            else{
                prev_ch = ch;
                printf("Input detected, using new input\n");
            }
            int pos = game->pacman->x + game->pacman->y * COL;
            switch (ch) {
                case KEY_UP:
                    if (game->map->grid[pos + UP] != WALL && game->map->grid[pos + UP] != WALL2){
                        game->pacman->direction = UP;
                    }
                    break;
                case KEY_DOWN:
                    if (game->map->grid[pos + DOWN] != WALL && game->map->grid[pos + DOWN] != WALL2){
                        game->pacman->direction = DOWN;
                    }
                    break;
                case KEY_LEFT:
                    if (game->map->grid[pos + LEFT] != WALL && game->map->grid[pos + LEFT] != WALL2){
                        game->pacman->direction = LEFT;
                    }
                    break;
                case KEY_RIGHT:
                    if (game->map->grid[pos + RIGHT] != WALL && game->map->grid[pos + RIGHT] != WALL2){
                        game->pacman->direction = RIGHT;
                    }
                    break;
                default:
                    break;
            }
            for (size_t i = 0; i < game->ghosts->length; i++){
                GhostMove(llist_use(game->ghosts, i), llist_use(game->ghosts, 0),
                        game->map->grid, game->pacman);
            }
			update(game);
		}
		else{
            switch (game->difficulty) {
                case PEACEFULL:
                    game->pacman->direction = searchdumb(game);
                    printf("%d", game->pacman->direction);
                    break;
                case EASY:
                    game->pacman->direction = searchdumb(game);                   
                    break;
                case HARD:
			        minimax_tree = minimax(minimax_tree);
                    Game *ga = minimax_tree->key;
		        	game->pacman = ga->pacman;  
                    break;
            }
            for (size_t i = 0; i < game->ghosts->length; i++){
                GhostMove(llist_use(game->ghosts, i), llist_use(game->ghosts, 0),
                        game->map->grid, game->pacman);
            }
            update(game);
		}
		// Makes loop sleep for 1s
		sleep(1);
	}
    printf("Game over...\n");
    if (minimax_tree != NULL){
	    free_minimax(minimax_tree);
    }
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
