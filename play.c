#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

#include "main.h"
#include "pacman_ai/search.h"

int score = 0;
int game_won;
int image_width, image_height;

int get_input();
int all_eaten(Game* game);
void draw_final(SDL_Renderer* renderer);

void draw_save(SDL_Renderer* renderer,Game* game)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* save_surface = IMG_Load("menuimg/save_map.png");
    SDL_Texture* save_texture = SDL_CreateTextureFromSurface(renderer, save_surface);
    SDL_FreeSurface(save_surface);

    SDL_QueryTexture(save_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect save_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, save_texture, NULL, &save_rect);

    int buttonwidth = 300;
    int buttonheight = 300;

    int yes_y = ( 864- buttonheight) / 2;
    int no_x = 700;
    int yes_x = 200;

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            SDL_DestroyTexture(save_texture);
            SDL_DestroyRenderer(renderer);
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            exit(0);
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= yes_x && x <= yes_x + buttonwidth &&
                y >= yes_y && y <= yes_y + buttonheight) {
                break;
            }
            else if (x >= no_x && x <= no_x + buttonwidth &&
             y >= yes_y && y <= yes_y + buttonheight) {
                game->map->points+=0; //just for testing purposes
                /*
                char name[128];
                // function to retrieve input user
                save_map(game->map, name);*/
                
            }
        }
    }
    SDL_DestroyTexture(save_texture);
}


void draw_game(SDL_Renderer* renderer,Game* game,int map_load)
{
    SDL_RenderClear(renderer);
    SDL_Surface* map_surface= IMG_Load("Default_Map.png");
    
    if (map_load == 0) {
        map_surface = IMG_Load("Default_Map.png");
    }
    else
    {   // function mapgeneration thomas 
        // function arthur
        // map_surface = IMG_Load("fichierarthur");

    }
    SDL_Texture* map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    SDL_FreeSurface(map_surface);
    

    int map_x = 0;
    int map_y = 0;
    int map_height = 928 ;
    int map_width = 864 ;
    
    SDL_Rect map_rect = { map_x, map_y, map_height,map_width};
    SDL_RenderCopy(renderer, map_texture, NULL, &map_rect);
    SDL_RenderPresent(renderer);

    sleep(5);
    
    
    int ch = 0;
    int prev_ch = 0;
    int countdown = 10;
    int state = 0;

    while (game_over(game) == 0 && all_eaten(game) == 1){
        
        if (game->is_ai != 1){
            ch = get_input();
            if (ch == 0){
                ch = prev_ch;
            }
            else{
                prev_ch = ch;
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
            state = update(game);
		}
		else{
            size_t pos = game->pacman->x + game->pacman->y * COL;
            switch (game->difficulty) {
                case PEACEFULL:
                    game->pacman->direction = Bellman(game, pos);
                    break;
                case EASY:
                    game->pacman->direction = Bellman(game, pos);                   
                    break;
                case HARD:
                    game->pacman->direction = Bellman(game, pos);
                    break;
            }
            
            state = update(game);
		}
        state = countdown;
        countdown = state;
        if (game->pacman->lives == 0){
            break;
        }
            
    }
    score = game->map->points;
    game_won = game->pacman->lives;
    /*
    if (map_load==0)
    {
        draw_save(renderer,game);
    }*/
    free_game(game);
    draw_final(renderer);
    SDL_DestroyTexture(map_texture);
    

}