#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"

int score = 0;

void draw_final(SDL_Renderer* renderer,Game* game);
void draw_save(SDL_Renderer* renderer);


void draw_game(SDL_Renderer* renderer,Game* game,int map_load)
{
    SDL_RenderClear(renderer);
    // function arthur
    SDL_Surface* map_surface = IMG_Load("Default_Map.png");
    SDL_Texture* map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    SDL_FreeSurface(map_surface);

    int map_x = 0;
    int map_y = 0;
    int map_height = 928 ;
    int map_width = 864 ;
    

    SDL_Rect map_rect = { map_x, map_y, map_height,map_width};
    SDL_RenderCopy(renderer, map_texture, NULL, &map_rect);
    SDL_RenderPresent(renderer);
    
    //score = game->map->points;
    score += 10;

    /*
    int ch = 0;
    int prev_ch = 0;
    int countdown = 10;*/

    SDL_DestroyTexture(map_texture);


    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
    
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (map_load==0 && game->is_ai <2)
            {
                draw_save(renderer);
            }
            else 
            {
                draw_final(renderer,game);
            }
        }
    }

}