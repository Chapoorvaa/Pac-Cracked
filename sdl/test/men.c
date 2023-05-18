#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
//#include "play.h"

int window_width, window_height;
int image_width, image_height;
int play_x,play_y,select_map_x,select_map_y;
int high_score_x,high_score_y,help_x,help_y,about_x,about_y,quit_x,quit_y;
int easy_x,easy_y,medium_x,medium_y,hard_x,hard_y,back_x,back_y;
int BUTTON_WIDTH;
int BUTTON_HEIGHT;
int BUTTON_MARGIN;


void draw_menu(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* menu_surface = IMG_Load("menu_buttons/logo.png");
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

    SDL_QueryTexture(menu_texture, NULL, NULL, &image_width, &image_height);
    
    SDL_Rect dst_rect;
    dst_rect.x = (window_width - image_width) / 9.25;
    dst_rect.y = (window_height - image_height) / 3.25;
    dst_rect.w = image_width;
    dst_rect.h = image_height;
    
    // Calculate buttons positions
    BUTTON_WIDTH = 200*1.5;
    BUTTON_HEIGHT = 40*1.5;
    BUTTON_MARGIN = 20+15;
    
    play_x = (((window_width - BUTTON_WIDTH)/6)*5.5)+15;
    play_y = ((window_height - BUTTON_HEIGHT)/5.25)-12;

    select_map_x = play_x;
    select_map_y = play_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    high_score_x = play_x;
    high_score_y = select_map_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    help_x = play_x;
    help_y = high_score_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    about_x = play_x;
    about_y = help_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    quit_x = play_x;
    quit_y = about_y + BUTTON_HEIGHT + BUTTON_MARGIN;

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
   
    SDL_DestroyTexture(menu_texture);
    SDL_DestroyTexture(play_texture);
    SDL_DestroyTexture(select_map_texture);
    SDL_DestroyTexture(help_texture);
    SDL_DestroyTexture(about_texture);
    SDL_DestroyTexture(quit_texture);
}

void draw_play_mode(SDL_Renderer* renderer)
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

    SDL_Surface* back_surface = IMG_Load("buttons/back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    BUTTON_WIDTH = 500;
    BUTTON_HEIGHT = 100;
    BUTTON_MARGIN = 60;

    int about1_width, about1_height;
    SDL_QueryTexture(dif_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);

    int about1_x = ((width - 750) / 2) -195;
    int about1_y = (((height - 750) / 2))-40;

    int back_x = (width - back_width) / 2;
    int back_y = (((height - back_height) / 2)*1.75)+10;

    SDL_RenderCopy(renderer, dif_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width, about1_height});


    easy_x = ((1200 - BUTTON_WIDTH)/2);
    easy_y = ((864 - BUTTON_HEIGHT)/3)+ (2*BUTTON_MARGIN) -130;

    medium_x = easy_x;
    medium_y = easy_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    hard_x = easy_x;
    hard_y = medium_y + BUTTON_HEIGHT + BUTTON_MARGIN;



    SDL_Rect easy_rect = { easy_x, easy_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, easy_texture, NULL, &easy_rect);
    SDL_Rect medium_rect = { medium_x, medium_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, medium_texture, NULL, &medium_rect);
    SDL_Rect hard_rect = { hard_x, hard_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, hard_texture, NULL, &hard_rect);


    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
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
            y >= back_y && y <= back_y + 60)
            {   
                sleep(0.2);
                draw_menu(renderer);
            }   
        }
    }
}


void draw_help(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* about1_surface = IMG_Load("buttons/help.png");
    SDL_Texture* about1_texture = SDL_CreateTextureFromSurface(renderer, about1_surface);
    SDL_FreeSurface(about1_surface);


    SDL_Surface* back_surface = IMG_Load("buttons/back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int about1_width, about1_height;
    SDL_QueryTexture(about1_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);

    int about1_x = ((width - 625) / 2);
    int about1_y = (((height - 625) / 2)-95);

    int back_x = (width - back_width) / 2;
    int back_y = (((height - back_height) / 2)*1.75)+10;
    SDL_RenderCopy(renderer, about1_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width, about1_height});
    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
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
            y >= back_y && y <= back_y + 60)
            {   
                sleep(0.2);
                draw_menu(renderer);
            }   
        }
    }
}

void draw_about(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* about1_surface = IMG_Load("buttons/about.png");
    SDL_Texture* about1_texture = SDL_CreateTextureFromSurface(renderer, about1_surface);
    SDL_FreeSurface(about1_surface);


    SDL_Surface* back_surface = IMG_Load("buttons/back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int about1_width, about1_height;
    SDL_QueryTexture(about1_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);

    int about1_x = ((width - 625) / 2);
    int about1_y = (((height - 625) / 2)-75);

    int back_x = (width - back_width) / 2;
    int back_y = (((height - back_height) / 2)*1.75)+10;
    SDL_RenderCopy(renderer, about1_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width, about1_height});
    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
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
            y >= back_y && y <= back_y + 60)
            {   
                sleep(0.2);
                draw_menu(renderer);
            }   
        }
    }

}  /*
void draw_select_map(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);

    SDL_Surface* dif_surface = IMG_Load("buttons/who.png");
    SDL_Texture* dif_texture = SDL_CreateTextureFromSurface(renderer, dif_surface);
    SDL_FreeSurface(dif_surface);

    SDL_Surface* easy_surface = IMG_Load("buttons/ai.png");
    SDL_Texture* easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_FreeSurface(easy_surface);

    SDL_Surface* medium_surface = IMG_Load("buttons/me.png");
    SDL_Texture* medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_FreeSurface(medium_surface);

    SDL_Surface* back_surface = IMG_Load("buttons/back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int about1_width, about1_height;
    SDL_QueryTexture(dif_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);
    int back_x = (width - back_width) / 2;
    int back_y = (((height - back_height) / 2) * 1.75) + 10;

    int about1_x = ((width - 1125) / 2);
    int about1_y = 50;

    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
    SDL_RenderCopy(renderer, dif_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width, about1_height});
    

    int buttonwidth = 300;
    int buttonheight = 300;

    int ai_x = 200;  // Center horizontally on the left side
    int ai_y = (height - buttonheight) / 2;

    int me_x = 700;  // Center horizontally on the right side
    int me_y = (height - buttonheight) / 2;

    SDL_RenderCopy(renderer, easy_texture, NULL, &(SDL_Rect){ai_x, ai_y, buttonwidth, buttonheight});
    SDL_RenderCopy(renderer, medium_texture, NULL, &(SDL_Rect){me_x, me_y, buttonwidth, buttonheight});
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= back_x && x <= back_x + back_width &&
                y >= back_y && y <= back_y + back_height) {
                draw_play_mode(renderer);
            } else if (x >= ai_x && x <= ai_x + buttonwidth &&
                       y >= ai_y && y <= ai_y + buttonheight) {
                // TODO: Handle AI button click
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
                SDL_RenderPresent(renderer);
            } else if (x >= me_x && x <= me_x + buttonwidth &&
                       y >= me_y && y <= me_y + buttonheight) {
                // TODO: Handle ME button click
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
                SDL_RenderPresent(renderer);
            }
        }
    }
}*/


void draw_select_map(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);

    SDL_Surface* dif_surface = IMG_Load("buttons/map.png");
    SDL_Texture* dif_texture = SDL_CreateTextureFromSurface(renderer, dif_surface);
    SDL_FreeSurface(dif_surface);

    SDL_Surface* easy_surface = IMG_Load("buttons/load.png");
    SDL_Texture* easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_FreeSurface(easy_surface);

    SDL_Surface* medium_surface = IMG_Load("buttons/generate.png");
    SDL_Texture* medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_FreeSurface(medium_surface);

    SDL_Surface* back_surface = IMG_Load("buttons/back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int about1_width, about1_height;
    SDL_QueryTexture(dif_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);
    int back_x = (width - back_width) / 2;
    int back_y = (((height - back_height) / 2) * 1.75) + 10;

    int about1_x = ((width - about1_width) / 2)-100;
    int about1_y = 20;

    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
    SDL_RenderCopy(renderer, dif_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width*1.25, about1_height*1.25});
    

    int buttonwidth = 300;
    int buttonheight = 300;

    int ai_x = 200;  // Center horizontally on the left side
    int ai_y = (height - buttonheight) / 2;

    int me_x = 700;  // Center horizontally on the right side
    int me_y = (height - buttonheight) / 2;

    SDL_RenderCopy(renderer, easy_texture, NULL, &(SDL_Rect){ai_x, ai_y, buttonwidth, buttonheight});
    SDL_RenderCopy(renderer, medium_texture, NULL, &(SDL_Rect){me_x, me_y, buttonwidth, buttonheight});
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            if (x >= back_x && x <= back_x + back_width &&
                y >= back_y && y <= back_y + back_height) {
                draw_play_mode(renderer);
            } else if (x >= ai_x && x <= ai_x + buttonwidth &&
                       y >= ai_y && y <= ai_y + buttonheight) {
                // TODO: Handle AI button click
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
                SDL_RenderPresent(renderer);
            } else if (x >= me_x && x <= me_x + buttonwidth &&
                       y >= me_y && y <= me_y + buttonheight) {
                // TODO: Handle ME button click
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 11, 63, 114, 255);
                SDL_RenderPresent(renderer);
            }
        }
    }
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

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    
    // Calculate the position of the image
    
    SDL_GetWindowSize(window, &window_width, &window_height);
   
    draw_menu(renderer);

    int continuer = 1;

    // Wait for the user to quit
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
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
                draw_play_mode(renderer);
            }

            else if (x >= select_map_x && x <= select_map_x + BUTTON_WIDTH &&
             y >= select_map_y && y <= select_map_y + BUTTON_HEIGHT) {
            // Handle Select Map button click
            draw_select_map(renderer);
            }
            else if (x >= high_score_x && x <= high_score_x + BUTTON_WIDTH &&
             y >= high_score_y && y <= high_score_y + BUTTON_HEIGHT) {
                // Handle High Score button click
            }
            else if (x >= help_x && x <= help_x + BUTTON_WIDTH &&
             y >= help_y && y <= help_y + BUTTON_HEIGHT) {
                // Handle Help button click
                draw_help(renderer);
            }
            else if (x >= about_x && x <= about_x + BUTTON_WIDTH &&
             y >= about_y && y <= about_y + BUTTON_HEIGHT) {
                draw_about(renderer);
            }
            else if (x >= quit_x && x <= quit_x + BUTTON_WIDTH &&
             y >= quit_y && y <= quit_y + BUTTON_HEIGHT) {
                break; 
            }
        }
    }
    
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

