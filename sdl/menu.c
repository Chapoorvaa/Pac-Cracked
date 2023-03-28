#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    SDL_Surface* play_surface = IMG_Load("play.png");
    SDL_Texture* play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
    SDL_FreeSurface(play_surface);

    SDL_Surface* select_map_surface = IMG_Load("select_map.png");
    SDL_Texture* select_map_texture = SDL_CreateTextureFromSurface(renderer, select_map_surface);
    SDL_FreeSurface(select_map_surface);

    SDL_Surface* high_score_surface = IMG_Load("high_score.png");
    SDL_Texture* high_score_texture = SDL_CreateTextureFromSurface(renderer, high_score_surface);
    SDL_FreeSurface(high_score_surface);

    SDL_Surface* help_surface = IMG_Load("help.png");
    SDL_Texture* help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
    SDL_FreeSurface(help_surface);

    SDL_Surface* about_surface = IMG_Load("about.png");
    SDL_Texture* about_texture = SDL_CreateTextureFromSurface(renderer, about_surface);
    SDL_FreeSurface(about_surface);

    SDL_Surface* quit_surface = IMG_Load("quit.png");
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
    const int BUTTON_WIDTH = 250;
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

