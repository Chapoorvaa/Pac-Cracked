#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "play.h"

void draw_mappng(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    
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

    SDL_DestroyTexture(map_texture);

}
