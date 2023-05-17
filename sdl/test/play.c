#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "play.h"


void play(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);  
    SDL_Surface* map_surface = IMG_Load("Default_Map.png");
    SDL_Texture* map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    SDL_FreeSurface(map_surface); 

    int image_width, image_height;
    SDL_QueryTexture(map_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect map_rect;
    map_rect.x = (1080 - image_width) / 3.60;
    map_rect.y = (780 - image_height) / 7;
    map_rect.w = image_width;
    map_rect.h = image_height;
    SDL_RenderCopy(renderer, map_texture, NULL, &map_rect);
    push_screen(map_texture);


    SDL_Event event;
    int continuer = 1;
    int i = 0,j=0;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }
    }
}