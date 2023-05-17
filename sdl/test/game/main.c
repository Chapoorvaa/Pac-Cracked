#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "play.h"

void draw_map(SDL_Renderer* renderer)
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

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_Image
    IMG_Init(IMG_INIT_PNG);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Pac-Cracked",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1194, 864,
        SDL_WINDOW_SHOWN  
    );

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    draw_map(renderer);

    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        play(renderer);
                }
                break;

        }
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}