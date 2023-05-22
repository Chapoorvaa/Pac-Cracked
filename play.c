#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

#include "main.h"
#include "pacman_ai/search.h"

#define TILE_SIZE 32
enum{HAUT,BAS,GAUCHE,DROITE};

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

void Move(SDL_Rect* pos,int direction)
{
    switch (direction)
    {
    case HAUT:
        pos->y--;
        break;
    case BAS:
        pos->y++;
        break;
    case GAUCHE:
        pos->x--;
        break;
    case DROITE:
        pos->x++;
        break;
    
    default:
        break;
    }
} 
/*
void display_map(SDL_Renderer* renderer)
{
    //TODO

}
*/

void draw_game(SDL_Renderer* renderer,Game* game,int map_load)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Surface* map_surface= IMG_Load("png/map1.png");
    
    if (map_load == 0) {
        map_surface = IMG_Load("png/map1.png");
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
    int map_height = 864;
    int map_width = 928 ;
    
    SDL_Rect map_rect = { map_x, map_y, map_height,map_width};
    SDL_RenderCopy(renderer, map_texture, NULL, &map_rect);
 
    SDL_Surface *pacman[4]={NULL};
    SDL_Surface *pacmanActuel = NULL;

    pacman[HAUT]= IMG_Load("characters/pacman_up.png");
    pacman[BAS]= IMG_Load("characters/pacman_down.png");
    pacman[GAUCHE]= IMG_Load("characters/pacman_left.png");
    pacman[DROITE]= IMG_Load("characters/pacman_right.png");

    pacmanActuel= pacman[DROITE];
    SDL_Texture* pac_texture = SDL_CreateTextureFromSurface(renderer, pacmanActuel);
    int pac_x = game->pacman->x*TILE_SIZE;
    int pac_y = game->pacman->y*TILE_SIZE;
    int pac_height = 32 ;
    int pac_width =  32;
    SDL_Rect position = {pac_x,pac_y,pac_height,pac_width};

    SDL_RenderCopy(renderer, pac_texture, NULL, &position);
    SDL_RenderPresent(renderer);

    SDL_Surface* pp = IMG_Load("characters/power_pellet.png");
    SDL_Texture* pp_texture = SDL_CreateTextureFromSurface(renderer, pp);
    SDL_FreeSurface(pp);
    SDL_Surface* tt = IMG_Load("characters/tic_tac.png");
    SDL_Texture* tt_texture = SDL_CreateTextureFromSurface(renderer, tt);
    SDL_FreeSurface(tt);
      
    //int ch = 0;
    //int prev_ch = 0;
    int countdown = 10;
    int state = 0; 
    int pos;  
    char c; 

    while (game_over(game) == 0 && all_eaten(game) == 1){
    
        position.x= (game->pacman->x*TILE_SIZE);//30
        position.y= (game->pacman->y*TILE_SIZE); //31
        SDL_RenderCopy(renderer, map_texture, NULL, &map_rect);
        pac_texture = SDL_CreateTextureFromSurface(renderer, pacmanActuel);
        SDL_RenderCopy(renderer, pac_texture, NULL, &position);
        for (int i = 0;i<COL;i++)
        {
            for(int j=0;j<ROW;j++)
            {
                position.x=i*TILE_SIZE;
                position.y= j*TILE_SIZE;
                c=game->map->grid[i+j*COL];
                switch(c)
                {
                    case '.':
                        SDL_RenderCopy(renderer, tt_texture, NULL, &position);

                        break;
                    case 'o':
                        SDL_RenderCopy(renderer, pp_texture, NULL, &position);
                        break;
                    default:
                        break;

                }

            }
        } 
    
        SDL_RenderPresent(renderer);  
        
        if (game->is_ai != 1){
            pos = game->pacman->x + game->pacman->y * COL;
            SDL_Event event;
            while (SDL_WaitEvent(&event)) {
    
                if (event.type == SDL_QUIT) {
                    SDL_DestroyTexture(map_texture);
                    SDL_DestroyRenderer(renderer);
                    TTF_Quit();
                    IMG_Quit();
                    SDL_Quit();
                    exit(0);
                    break;
                } 
                else if (event.type == SDL_KEYDOWN) { 
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            if (game->map->grid[pos + UP] != WALL && game->map->grid[pos + UP] != WALL2){
                                game->pacman->direction = UP; 
                                pacmanActuel = pacman[HAUT];
                                Move(&position,HAUT);
                            }
                            break;
                        case SDLK_DOWN:
                            if (game->map->grid[pos + DOWN] != WALL && game->map->grid[pos + DOWN] != WALL2){
                                game->pacman->direction = DOWN;
                                pacmanActuel = pacman[BAS];
                                Move(&position,BAS);
                            }
                            break;
                        case SDLK_LEFT:
                            if (game->map->grid[pos + LEFT] != WALL && game->map->grid[pos + LEFT] != WALL2){
                                game->pacman->direction = LEFT;
                                pacmanActuel = pacman[GAUCHE];
                                Move(&position,GAUCHE);
                            }
                            break;
                        case SDLK_RIGHT:
                            if (game->map->grid[pos + RIGHT] != WALL && game->map->grid[pos + RIGHT] != WALL2){
                                game->pacman->direction = RIGHT;
                                pacmanActuel = pacman[DROITE];
                                Move(&position,DROITE);
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
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
            sleep(0.1);
            
            state = update(game);
		} 
        state = countdown;
        countdown = state;
        if (game->pacman->lives == 0){
            break;
        }       
    }
    
    for (int i =0;i<4;i++)
    {
        SDL_FreeSurface(pacman[i]);
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
    //SDL_DestroyTexture(map_texture);

}