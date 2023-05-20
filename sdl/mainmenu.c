#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include "play.h"

#define MAX_MAPS 10
#define MAPS_FOLDER "maps"
#define MAX_FILES 256

char selectedMapPath[512] = "maps/map_1.txt";

int difficulty;
int is_ai;
int window_width, window_height;
int image_width, image_height;


void draw_menu(SDL_Renderer* renderer);
void draw_play_mode(SDL_Renderer* renderer);
void draw_play_ai(SDL_Renderer* renderer);
void draw_select_map(SDL_Renderer* renderer);


void draw_map(SDL_Renderer* renderer)
{

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* play_surface = IMG_Load("menuimg/map.png");
    SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_FreeSurface(play_surface);

    SDL_QueryTexture(play_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect play_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

    int buttonwidth = 300;
    int buttonheight = 300;

    int back_x = 450;
    int back_y = 713;
    int ai_y = (window_height - buttonheight) / 2;
    int me_x = 700;
    int ai_x = 200;

    SDL_RenderPresent(renderer);

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
                draw_play_ai(renderer);
            }
            else if (x >= ai_x && x <= ai_x + buttonwidth &&
                y >= ai_y && y <= ai_y + buttonheight) {
                draw_select_map(renderer);
            }
            else if (x >= me_x && x <= me_x + buttonwidth &&
             y >= ai_y && y <= ai_y + buttonheight) {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                draw_game(renderer);
            }
            
        
        }
    }
}

void draw_play_ai(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* play_surface = IMG_Load("menuimg/who.png");
    SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_FreeSurface(play_surface);

    SDL_QueryTexture(play_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect play_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

    int buttonwidth = 300;
    int buttonheight = 300;

    int back_x = 450;
    int back_y = 713;
    int ai_y = (window_height - buttonheight) / 2;
    int me_x = 700;
    int ai_x = 200;

    SDL_RenderPresent(renderer);

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
                draw_play_mode(renderer);
            }
            else if (x >= ai_x && x <= ai_x + buttonwidth &&
                y >= ai_y && y <= ai_y + buttonheight) {
                // TODO : update in the game it's ai 
                is_ai = 1;
                draw_map(renderer);
            }
            else if (x >= me_x && x <= me_x + buttonwidth &&
             y >= ai_y && y <= ai_y + buttonheight) {
                //TODO : update in the game it's human playing
                is_ai = 0;
                draw_map(renderer);
            }
            
        
        }
    }

}

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
                // TODO : PEACEFULL
                draw_play_ai(renderer);
            }
            else if (x >= easy_x && x <= easy_x + buttonwidth &&
             y >= medium_y && y <= medium_y + buttonheight) {
                //TODO : easy
                draw_play_ai(renderer);
            }
            else if (x >= easy_x && x <= easy_x + buttonwidth &&
             y >= hard_y && y <= hard_y + buttonheight) {
                // TODO: hard
                draw_play_ai(renderer);
            }
        }
    }


}

void draw_select_map(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
    SDL_RenderPresent(renderer);

    SDL_Surface* sm_surface = IMG_Load("menuimg/button.png");
    SDL_Texture* sm_texture = SDL_CreateTextureFromSurface(renderer, sm_surface);
    SDL_FreeSurface(sm_surface);

    SDL_QueryTexture(sm_texture, NULL, NULL, &image_width, &image_height);
    SDL_QueryTexture(sm_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect sm_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, sm_texture, NULL, &sm_rect);
    int back_x = 450;
    int back_y = 713; 

    // todo : draw the files buttons


    SDL_RenderPresent(renderer);
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
                draw_menu(renderer); // for testing purposes
            }
            else if (x >= 0 && x <= 1200 &&
             y >= 0 && y <= 864)
            {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                draw_game(renderer);
            }
        }
    }
   
}

void draw_high_score(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
    SDL_RenderPresent(renderer);

    SDL_Surface* sm_surface = IMG_Load("menuimg/high_score.png");
    SDL_Texture* sm_texture = SDL_CreateTextureFromSurface(renderer, sm_surface);
    SDL_FreeSurface(sm_surface);

    SDL_QueryTexture(sm_texture, NULL, NULL, &image_width, &image_height);
    SDL_QueryTexture(sm_texture, NULL, NULL, &image_width, &image_height);
    SDL_Rect sm_rect = { 0, 0, image_width, image_height};
    
    SDL_RenderCopy(renderer, sm_texture, NULL, &sm_rect);
    int back_x = 450;
    int back_y = 713; 

    // TODO : display the high score

    SDL_RenderPresent(renderer);
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
                draw_high_score(renderer);
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
    TTF_Init();

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
    TTF_Quit();
    SDL_Quit();

    return 0;
}