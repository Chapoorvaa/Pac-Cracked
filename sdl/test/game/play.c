#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "play.h"
#include "constants.h"


void play(SDL_Renderer* renderer)
{
    SDL_Rect position;
    SDL_Rect player_pos;
    SDL_Surface* pacman[4]={NULL};
    SDL_Surface* pacmanActuel = NULL;

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    int continuer = 1;
    int i=0,j=0;

    pacman[DOWN]=IMG_Load("characters/pacman_down.png");
    pacman[UP]=IMG_Load("characters/pacman_up.png");
    pacman[RIGHT]=IMG_Load("characters/pacman_right.png");
    pacman[LEFT]=IMG_Load("characters/pacman_left.png");

    pacmanActuel=pacman[LEFT];
    player_pos.x=416;
    player_pos.y=672;

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        pacmanActuel = pacman[UP];
                        if (player_pos.y > 0) {
                            player_pos.y--;
                        }
                        break;
                    case SDLK_DOWN:
                        pacmanActuel = pacman[DOWN];
                        if (player_pos.y < (928 - 1)) {
                            player_pos.y++;
                        }
                        break;
                    case SDLK_LEFT:
                        pacmanActuel = pacman[LEFT];
                        if (player_pos.x > 0) {
                            player_pos.x--;
                        }
                        break;
                    case SDLK_RIGHT:
                        pacmanActuel = pacman[RIGHT];
                        if (player_pos.x < (864 - 1)) {
                            player_pos.x++;
                        }
                        break;
                }
                break;
        }

        position.x = player_pos.x * BLOCK_SIZE;
        position.y = player_pos.y * BLOCK_SIZE;

        SDL_BlitSurface(pacmanActuel, NULL, surface, &position);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);
    }

    for(i=0;i<4;i++)
    {   
        SDL_FreeSurface(pacman[i]);
    }
    SDL_FreeSurface(surface);
}
