#include <SDL2/SDL.>
#include <SDL2/SDL_image.h>
#include "stdio.h"
#include "stddef.h"
#include "txtToPNG.h"

#define SPRITE_SIZE 16
#define ROW 29
#define COL 27
#define WALL '#'
#define WALL2 '_'

void combinePNGs(const char* outputFilename, Map* map,
        int width, int height)
{
    char* grid = map->grid;

    // Initialize SDL's Video subsystem
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Image Processing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    
    // Create a renderer that will draw to the window, -1 specifies that we
    // don't care which renderer is used
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Load the image into memory using SDL_image library function
    SDL_Surface* VerticalWall = IMG_Load("VerticalWall.png");
    SDL_Surface* HorizontalWall = IMG_Load("HorizontalWall.png");
    SDL_Surface* CornerBottomLeft = IMG_Load("CornerBottomLeft.png");
    SDL_Surface* CornerBottomRight = IMG_Load("CornerBottomRight.png");
    SDL_Surface* CornerTopLeft = IMG_Load("CornerTopLeft.png");
    SDL_Surface* CornerTopRight = IMG_Load("CornerTopRight.png");
    SDL_Surface* UCornerBottom = IMG_Load("UCornerBottom.png");
    SDL_Surface* UCornerLeft = IMG_Load("UCornerLeft.png");
    SDL_Surface* UCornerRight = IMG_Load("UCornerRight.png");
    SDL_Surface* HouseWall = IMG_Load("HouseWall.png");
    SDL_Surface* 1DIntersection = IMG_Load("1DIntersection.png");

    // Get the width and height of the surface to be created
    int combinedWidth = ROW * SPRITE_SIZE;
    int combinedHeight = COL * SPRITE_SIZE;

    SDL_Surface* combinedImage = SDL_CreateRGBSurface(0, combinedWidth,
            combinedHeight, 32, 0, 0, 0, 0);

    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_Rect dstRect = {0, 0, 0, 0};

    //TODO : 
    //Go through the map and assign the correct sprite at the correct location
    // -> loop through each row
    // -> loop through each column of the row
    //    -> check what block to put if it is a wall (WALL || WALL2)
    //      . Look in the 3*3 adjacent tiles:
    //          _ Depending on the adjacent tiles, select the correct image to
    //            use
    //      . Use SDL_BlitSurface to copy the right PNG to the right spot
    // Once out of the loop save the combined image to the output file name
    for (int y = 0; y < ROW; y++){
        for (int x = 0; x < COL; x++){
        
        }
    }

    // Cleanup
    SDL_FreeSurface(VerticalWall);
    SDL_FreeSurface(HorizontalWall);
    SDL_FreeSurface(CornerBottomLeft);
    SDL_FreeSurface(CornerBottomRight);
    SDL_FreeSurface(CornerTopRight);
    SDL_FreeSurface(CornerTopLeft);
    SDL_FreeSurface(UCornerBottom);
    SDL_FreeSurface(UCornerLeft);
    SDL_FreeSurface(UCornerRight);
    SDL_FreeSurface(HouseWall);
    SDL_FreeSurface(1DIntersection);

    SDL_FreeSurface(combinedImage);
    
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}
