#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "play.h"


void select_play_mode(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);

    SDL_Surface* dif_surface = IMG_Load("play_mode/select_difficulty.png");
    SDL_Texture* dif_texture = SDL_CreateTextureFromSurface(renderer, dif_surface);
    SDL_FreeSurface(dif_surface);

    SDL_Surface* easy_surface = IMG_Load("play_mode/easy.png");
    SDL_Texture* easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_FreeSurface(easy_surface);

    SDL_Surface* medium_surface = IMG_Load("play_mode/medium.png");
    SDL_Texture* medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_FreeSurface(medium_surface);

    SDL_Surface* hard_surface = IMG_Load("play_mode/hard.png");
    SDL_Texture* hard_texture = SDL_CreateTextureFromSurface(renderer, hard_surface);
    SDL_FreeSurface(hard_surface);

    int image_width, image_height;
    SDL_QueryTexture(dif_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect dif_rect;
    dif_rect.x = (1080 - image_width) / 2;
    dif_rect.y = (780 - image_height) / 6;
    dif_rect.w = image_width;
    dif_rect.h = image_height;


    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 40;
    const int BUTTON_MARGIN = 20;

    int easy_x = (1080 - BUTTON_WIDTH)/2;
    int easy_y = (780 - BUTTON_HEIGHT)/3.75;

    int medium_x = easy_x;
    int medium_y = easy_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    int hard_x = easy_x;
    int hard_y = medium_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    SDL_RenderCopy(renderer, dif_texture, NULL, &dif_rect);

    SDL_Rect easy_rect = { easy_x, easy_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, easy_texture, NULL, &easy_rect);
    SDL_Rect medium_rect = { medium_x, medium_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, medium_texture, NULL, &medium_rect);
    SDL_Rect hard_rect = { hard_x, hard_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, hard_texture, NULL, &hard_rect);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) 
        {
            int x = event.button.x;
            int y = event.button.y;
    
            // Check if Play button was clicked
            if (x >= easy_x && x <= easy_x + BUTTON_WIDTH &&
                y >= easy_y && y <= easy_y + BUTTON_HEIGHT) {
                // Handle Play button click
                
            }

            else if (x >= medium_x && x <= medium_x + BUTTON_WIDTH &&
             y >= medium_y && y <= medium_y + BUTTON_HEIGHT) {
            // Handle Select Map button click
            }
            else if (x >= hard_x && x <= hard_x + BUTTON_WIDTH &&
             y >= hard_y && y <= hard_y + BUTTON_HEIGHT) {
                // Handle High Score button click
            }
        }
    }



}