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
        640, 480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

     SDL_SetRenderDrawColor(renderer,11,63,114, 255);

    // Load a menu background image
    SDL_Surface* menu_surface = IMG_Load("logo.png");
    SDL_Texture* menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    SDL_FreeSurface(menu_surface);

    // Calculate the position of the image
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    int image_width, image_height;
    SDL_QueryTexture(menu_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect dst_rect;
    dst_rect.x = (window_width - image_width) / 2;
    dst_rect.y = (window_height - image_height) / 2;
    dst_rect.w = image_width;
    dst_rect.h = image_height;

    // Draw the menu
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menu_texture, NULL, &dst_rect);
    SDL_RenderPresent(renderer);

    // Wait for the user to quit
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            // Resize the window and redraw the menu
            SDL_GetWindowSize(window, &window_width, &window_height);

            dst_rect.x = (window_width - image_width) / 2;
            dst_rect.y = (window_height - image_height) / 2;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menu_texture, NULL, &dst_rect);
            SDL_RenderPresent(renderer);
        }
    }

    // Clean up
    SDL_DestroyTexture(menu_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

