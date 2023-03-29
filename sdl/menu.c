#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "play.h"

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_Image
    IMG_Init(IMG_INIT_PNG);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Pac-Cracked",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1080, 780,
        SDL_WINDOW_SHOWN  
    );

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    
    // Load a menu background image
    SDL_Surface* menu_surface = IMG_Load("logo.png");
    SDL_Texture* menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    SDL_FreeSurface(menu_surface);

    SDL_Surface* play_surface = IMG_Load("menu_buttons/play.png");
    SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_FreeSurface(play_surface);

    SDL_Surface* select_map_surface = IMG_Load("menu_buttons/select_map.png");
    SDL_Texture* select_map_texture = SDL_CreateTextureFromSurface(renderer, select_map_surface);
    SDL_FreeSurface(select_map_surface);

    SDL_Surface* high_score_surface = IMG_Load("menu_buttons/high_score.png");
    SDL_Texture* high_score_texture = SDL_CreateTextureFromSurface(renderer, high_score_surface);
    SDL_FreeSurface(high_score_surface);

    SDL_Surface* help_surface = IMG_Load("menu_buttons/help.png");
    SDL_Texture* help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
    SDL_FreeSurface(help_surface);

    SDL_Surface* about_surface = IMG_Load("menu_buttons/about.png");
    SDL_Texture* about_texture = SDL_CreateTextureFromSurface(renderer, about_surface);
    SDL_FreeSurface(about_surface);

    SDL_Surface* quit_surface = IMG_Load("menu_buttons/quit.png");
    SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
    SDL_FreeSurface(quit_surface);

    // Calculate the position of the image
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    int image_width, image_height;
    SDL_QueryTexture(menu_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect dst_rect;
    dst_rect.x = (window_width - image_width) / 6;
    dst_rect.y = (window_height - image_height) / 2;
    dst_rect.w = image_width;
    dst_rect.h = image_height;

    // Calculate button positions
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 40;
    const int BUTTON_MARGIN = 20;

    int play_x = ((window_width - BUTTON_WIDTH)/6)*5;
    int play_y = (window_height - BUTTON_HEIGHT)/3.75;

    int select_map_x = play_x;
    int select_map_y = play_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    int high_score_x = play_x;
    int high_score_y = select_map_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    int help_x = play_x;
    int help_y = high_score_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    int about_x = play_x;
    int about_y = help_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    int quit_x = play_x;
    int quit_y = about_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    // Draw the menu
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menu_texture, NULL, &dst_rect);
    
    // Draw buttons
    SDL_Rect play_rect = { play_x, play_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);
    SDL_Rect select_map_rect = { select_map_x, select_map_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, select_map_texture, NULL, &select_map_rect);
    SDL_Rect high_score_rect = { high_score_x, high_score_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, high_score_texture, NULL, &high_score_rect);
    SDL_Rect help_rect = { help_x, help_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);
    SDL_Rect about_rect = { about_x, about_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, about_texture, NULL, &about_rect);
    SDL_Rect quit_rect = { quit_x, quit_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rect);

    SDL_RenderPresent(renderer);

    // Wait for the user to quit
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {

            int x = event.button.x;
            int y = event.button.y;
    
            // Check if Play button was clicked
            if (x >= play_x && x <= play_x + BUTTON_WIDTH &&
                y >= play_y && y <= play_y + BUTTON_HEIGHT) {
                // Handle Play button click
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
                dif_rect.x = (1080 - image_width) / 3.60;
                dif_rect.y = (780 - image_height) / 7;
                dif_rect.w = image_width*1.5;
                dif_rect.h = image_height*1.5;


                const int BUTTON_WIDTH = 300;
                const int BUTTON_HEIGHT = 60;
                const int BUTTON_MARGIN = 40;

                int easy_x = (1080 - BUTTON_WIDTH)/2;
                int easy_y = ((780 - BUTTON_HEIGHT)/3)+ (2*BUTTON_MARGIN);

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

            else if (x >= select_map_x && x <= select_map_x + BUTTON_WIDTH &&
             y >= select_map_y && y <= select_map_y + BUTTON_HEIGHT) {
            // Handle Select Map button click
            }
            else if (x >= high_score_x && x <= high_score_x + BUTTON_WIDTH &&
             y >= high_score_y && y <= high_score_y + BUTTON_HEIGHT) {
                // Handle High Score button click
            }
            else if (x >= help_x && x <= help_x + BUTTON_WIDTH &&
             y >= help_y && y <= help_y + BUTTON_HEIGHT) {
                // Handle Help button click
            }
            else if (x >= about_x && x <= about_x + BUTTON_WIDTH &&
             y >= about_y && y <= about_y + BUTTON_HEIGHT) {
                // Handle About button click
            }
            else if (x >= quit_x && x <= quit_x + BUTTON_WIDTH &&
             y >= quit_y && y <= quit_y + BUTTON_HEIGHT) {
                break; 
            }
        }
    }

    // Clean up
    SDL_DestroyTexture(menu_texture);
    SDL_DestroyTexture(play_texture);
    SDL_DestroyTexture(select_map_texture);
    SDL_DestroyTexture(help_texture);
    SDL_DestroyTexture(about_texture);
    SDL_DestroyTexture(quit_texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

