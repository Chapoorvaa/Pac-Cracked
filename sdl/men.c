#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
//#include "play.h"

#define STACK_MAX 10

typedef struct {
    SDL_Texture* data[STACK_MAX];
    int size;
} Stack;

Stack screen_stack;

void init_stack() {
    screen_stack.size = 0;
}

void push_screen(SDL_Texture* screen) {
    if (screen_stack.size < STACK_MAX) {
        screen_stack.data[screen_stack.size++] = screen;
    } else {
        printf("Stack overflow\n");
    }
}

SDL_Texture* pop_screen() {
    if (screen_stack.size > 0) {
        return screen_stack.data[--screen_stack.size];
    } else {
        printf("Stack underflow\n");
        return NULL;
    }
}

void return_to_previous_screen(SDL_Renderer* renderer) {
    SDL_Texture* previous_screen = pop_screen();
    if (previous_screen != NULL) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, previous_screen, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(previous_screen);
    }
}


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

    SDL_QueryTexture(menu_texture, NULL, NULL, &image_width, &image_height);
    
    SDL_Rect dst_rect;
    dst_rect.x = (window_width - image_width) / 6;
    dst_rect.y = (window_height - image_height) / 2;
    dst_rect.w = image_width;
    dst_rect.h = image_height;
    
    // Calculate buttons positions
    BUTTON_WIDTH = 200;
    BUTTON_HEIGHT = 40;
    BUTTON_MARGIN = 20;
    
    play_x = ((window_width - BUTTON_WIDTH)/6)*5;
    play_y = (window_height - BUTTON_HEIGHT)/3.75;

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
    push_screen(menu_texture);

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

    SDL_Surface* back_surface = IMG_Load("back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int image_width, image_height;
    SDL_QueryTexture(dif_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect dif_rect;
    dif_rect.x = (1080 - image_width) / 3.60;
    dif_rect.y = (780 - image_height) / 7;
    dif_rect.w = image_width*1.5;
    dif_rect.h = image_height*1.5;


    BUTTON_WIDTH = 300;
    BUTTON_HEIGHT = 60;
    BUTTON_MARGIN = 40;

    easy_x = (1080 - BUTTON_WIDTH)/2;
    easy_y = ((780 - BUTTON_HEIGHT)/3)+ (2*BUTTON_MARGIN);

    medium_x = easy_x;
    medium_y = easy_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    hard_x = easy_x;
    hard_y = medium_y + BUTTON_HEIGHT + BUTTON_MARGIN;

    
    back_x = easy_x;
    back_y = hard_y + BUTTON_HEIGHT + (BUTTON_MARGIN*3);

    SDL_RenderCopy(renderer, dif_texture, NULL, &dif_rect);

    SDL_Rect easy_rect = { easy_x, easy_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, easy_texture, NULL, &easy_rect);
    SDL_Rect medium_rect = { medium_x, medium_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, medium_texture, NULL, &medium_rect);
    SDL_Rect hard_rect = { hard_x, hard_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, hard_texture, NULL, &hard_rect);
    SDL_Rect back_rect = { back_x, back_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, back_texture, NULL, &back_rect);

    SDL_RenderPresent(renderer);
    push_screen(dif_texture);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            break;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
    
            // Check if Play button was clicked
            if (x >= easy_x && x <= easy_x + BUTTON_WIDTH &&
                y >= easy_y && y <= easy_y + BUTTON_HEIGHT) {
                // Handle easy button click 
                //play(renderer);
            }
            else if (x >= medium_x && x <= medium_x + BUTTON_WIDTH &&
            y >= medium_y && y <= medium_y + BUTTON_HEIGHT) {
            // Handle medium button click
                //play(renderer);
            }
            else if (x >= hard_x && x <= hard_x + BUTTON_WIDTH &&
            y >= hard_y && y <= hard_y + BUTTON_HEIGHT) {
                // Handle hard button click
                //play(renderer);
            }
            else if (x >= back_x && x <= back_x + BUTTON_WIDTH &&
            y >= back_y && y <= back_y + BUTTON_HEIGHT)
            {   
                return_to_previous_screen(renderer);
                sleep(0.2);
                draw_menu(renderer);
            }   
        }
    }

    SDL_DestroyTexture(easy_texture);
    SDL_DestroyTexture(medium_texture);
    SDL_DestroyTexture(hard_texture);
    SDL_DestroyTexture(dif_texture);
    SDL_DestroyTexture(back_texture);

}


void draw_help(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,11,63,114,255);
    SDL_Surface* help1_surface = IMG_Load("help.png");
    SDL_Texture* help1_texture = SDL_CreateTextureFromSurface(renderer, help1_surface);
    SDL_FreeSurface(help1_surface);


    SDL_Surface* back_surface = IMG_Load("back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int help1_width, help1_height;
    SDL_QueryTexture(help1_texture, NULL, NULL, &help1_width, &help1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);

    int help1_x = (width - help1_width) / 2;
    int help1_y = ((height - help1_height) / 2)-50;

    int back_x = (width - back_width) / 2;
    int back_y = ((height - back_height) / 2)*1.75;
    SDL_RenderCopy(renderer, help1_texture, NULL, &(SDL_Rect){help1_x, help1_y, help1_width, help1_height});
    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
    SDL_RenderPresent(renderer);
    push_screen(help1_texture);

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
                return_to_previous_screen(renderer);
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
    SDL_Surface* about1_surface = IMG_Load("about.png");
    SDL_Texture* about1_texture = SDL_CreateTextureFromSurface(renderer, about1_surface);
    SDL_FreeSurface(about1_surface);


    SDL_Surface* back_surface = IMG_Load("back.png");
    SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
    SDL_FreeSurface(back_surface);

    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int about1_width, about1_height;
    SDL_QueryTexture(about1_texture, NULL, NULL, &about1_width, &about1_height);

    int back_width, back_height;
    SDL_QueryTexture(back_texture, NULL, NULL, &back_width, &back_height);

    int about1_x = (width - about1_width) / 2;
    int about1_y = ((height - about1_height) / 2)-50;

    int back_x = (width - back_width) / 2;
    int back_y = ((height - back_height) / 2)*1.75;
    SDL_RenderCopy(renderer, about1_texture, NULL, &(SDL_Rect){about1_x, about1_y, about1_width, about1_height});
    SDL_RenderCopy(renderer, back_texture, NULL, &(SDL_Rect){back_x, back_y, back_width, back_height});
    SDL_RenderPresent(renderer);
    push_screen(about1_texture);

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
                return_to_previous_screen(renderer);
                sleep(0.2);
                draw_menu(renderer);
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
        1080, 780,
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
    
    init_stack();
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

