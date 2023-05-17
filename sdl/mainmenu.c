#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

int window_width, window_height;
int image_width, image_height;

void draw_play_mode(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* play_surface = IMG_Load("menuimg/play.png");
    SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_FreeSurface(play_surface);

    SDL_QueryTexture(play_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect play_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

    SDL_RenderPresent(renderer);

    int buttonwidth = 500;
    int buttonheight = 100;
    int buttonmargin = 60;

    int sum = buttonheight+buttonmargin;
    int easy_x = 350;
    int easy_y = 244;
    int medium_y = easy_y + sum;
    int hard_y = medium_y + sum;
    int back_x = 450;
    int back_y = 713;

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= back_x && x <= back_x + 300 &&
                y >= back_y && y <= back_y + 60) {
                draw_menu(renderer);
            }
            else if (x >= easy_x && x <= easy_x + buttonwidth &&
                y >= easy_y && y <= easy_y + buttonheight) {
                // TODO
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer,11,63,114,255);
                SDL_RenderPresent(renderer);
            }
            else if (x >= easy_x && x <= easy_x + buttonwidth &&
             y >= medium_y && y <= medium_y + buttonheight) {
                //TODO
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer,11,63,114,255);
                SDL_RenderPresent(renderer);
            }
            else if (x >= easy_x && x <= easy_x + buttonwidth &&
             y >= hard_y && y <= hard_y + buttonheight) {
                // TODO
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer,11,63,114,255);
                SDL_RenderPresent(renderer);
            }
        }
    }


}

void draw_select_map(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_RenderPresent(renderer);
}

void draw_help(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    SDL_Surface* help_surface = IMG_Load("menuimg/help.png");
    SDL_Texture* help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
    SDL_FreeSurface(help_surface);

    SDL_QueryTexture(help_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect help_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

    SDL_RenderPresent(renderer);
    int back_x = 450;
    int back_y = 713;

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= back_x && x <= back_x + 300 &&
                y >= back_y && y <= back_y + 60) {
                draw_menu(renderer);
            }
        }
    }
}

void draw_about(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    SDL_Surface* about_surface = IMG_Load("menuimg/about.png");
    SDL_Texture* about_texture = SDL_CreateTextureFromSurface(renderer, about_surface);
    SDL_FreeSurface(about_surface);

    SDL_QueryTexture(about_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect about_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, about_texture, NULL, &about_rect);

    SDL_RenderPresent(renderer);
    int back_x = 450;
    int back_y = 713;

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= back_x && x <= back_x + 300 &&
                y >= back_y && y <= back_y + 60) {
                draw_menu(renderer);
            }
        }
    }
}

void draw_menu(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* menu_surface = IMG_Load("menuimg/menu.png");
    SDL_Texture* menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    SDL_FreeSurface(menu_surface);

    SDL_QueryTexture(menu_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect menu_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);

    SDL_RenderPresent(renderer);

    int buttonwidth = 300;
    int buttonheight = 60;
    int buttonmargin = 35;
    int sum = buttonheight+buttonmargin;
    int play_x = 840;
    int play_y = 142;
    int select_map_y = play_y + sum;
    int high_score_y = select_map_y + sum;
    int help_y = high_score_y + sum;
    int about_y = help_y + sum;
    int quit_y = about_y + sum;

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= play_x && x <= play_x + buttonwidth &&
                y >= play_y && y <= play_y + buttonheight) {
                // Handle Play button click
                draw_play_mode(renderer);
            }
            else if (x >= play_x && x <= play_x + buttonwidth &&
             y >= select_map_y && y <= select_map_y + buttonheight) {
                // Handle Select Map button click
                draw_select_map(renderer);
            }
            else if (x >= play_x && x <= play_x + buttonwidth &&
             y >= high_score_y && y <= high_score_y + buttonheight) {
                // Handle High Score button click
            }
            else if (x >= play_x && x <= play_x + buttonwidth &&
             y >= help_y && y <= help_y + buttonheight) {
                // Handle Help button click
                draw_help(renderer);
            }
            else if (x >= play_x && x <= play_x + buttonwidth &&
             y >= about_y && y <= about_y + buttonheight) {
                draw_about(renderer);
            }
            else if (x >= play_x && x <= play_x + buttonwidth &&
             y >= quit_y && y <= quit_y + buttonheight) {
                SDL_DestroyTexture(menu_texture);
                SDL_DestroyRenderer(renderer);
                IMG_Quit();
                SDL_Quit();
                exit(0);
            } 
        }
    }
    SDL_DestroyTexture(menu_texture);
}

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
        1200, 864,
        SDL_WINDOW_SHOWN  
    );

    SDL_GetWindowSize(window, &window_width, &window_height);

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawColor(renderer,11,63,114,255);

    draw_menu(renderer);

    // Wait for the user to quit
    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}