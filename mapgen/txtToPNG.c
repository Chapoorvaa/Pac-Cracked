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

char* nbAdjacentWalls(char* grid, int x, int y, int* nbWalls, int* house)
{
    //Check the 8 adjacent tiles and increment nbWalls for each wall found
    // -> check if the tile is a wall
    // -> increment nbWalls if it is
    // -> return the string of the 8 adjacent tiles
    char* adjacentTiles = calloc(9, sizeof(char));
    *nbWalls = 0;
    adjacentTiles[4] = -1;
    int i;
    int j;
    if (x == 0)
        i = 0;
    else 
        i = -1;

    if (y == 0)
        j = 0;
    else 
        j = -1;
    
    int imax;
    int jmax;
    if (x == COL - 1)
        imax = 1;
    else 
        imax = 2;
    
    if (y == ROW - 1)
        jmax = 1;
    else 
        jmax = 2;
    
    for (; i < imax; i++){
        for (; j < jmax; j++){
            if (((j+1) * 3 + (i+1)) != 4){
                if (grid[(y + j) * COL + (x + i)] == WALL2){
                    (*nbWalls)++;
                    *house = 1;
                    adjacentTiles[(j + 1) * 3 + (i + 1)] = 2;
                } else if (grid[(y + j) * COL + (x + i)] == WALL){
                    (*nbWalls)++;
                    adjacentTiles[(j + 1) * 3 + (i + 1)] = 1;
                } else {
                    adjacentTiles[(j + 1) * 3 + (i + 1)] = 0;
                }
            }
        }
    }
    return adjacentTiles;
}

int chooseTile(char* tiles, int nbWalls, int house){
    //TODO: Choose the correct png to use depending on the adjacent tiles
    switch(nbWalls){
        case 1:
            if (house)
                return -1;
            if (tiles[1])
                return 14;
            else if (tiles[3])
                return 13;
            else if (tiles[5])
                return 12;
            else if (tiles[7])
                return 11;
            else
                return -1;
            break;
        case 2:
            // Two cases if the house is adjacent to the tile
            if (tiles[3] == 2 && tiles[5])
                return 13;
            if (tiles[5] == 2 && tiles[3])
                return 12;

            if(tiles[0]){
                if (tiles[1])
                    return 11;
                else if(tiles[3])
                    return 12;
                else
                    return -1;
            }
            if (tiles[1]){
                if (tiles[2])
                    return 11;
                else if (tiles[3])
                    return 6;
                else if (tiles[5])
                    return 5;
                else if (tiles[7])
                    return 15;
                else
                    return -1;
            }
            if (tiles[2]){
                if (tiles[5])
                    return 13;
                else
                    return -1;
            }
            if (tiles[3]){
                if (tiles[5])
                    if (house) // case if the tile is the house tile
                        return 10;
                    else
                        return 9;
                else if (tiles[6])
                    return 12;
                else if (tiles[7])
                    return 8;
                else
                    return -1;
            }
            if (tiles[5]){
                if (tiles[7])
                    return 7;
                else if (tiles[8])
                    return 13;
                else
                    return -1;
            }
            if (tiles[7]){
                if (tiles[6] || tiles[8])
                    return 14;
                else
                    return -1;
            }
            break;
        case 3:
            if (house)
                return -1;
            if (tiles[0]){
                if (tiles[1]){
                    if (tiles[2])
                        return 11;
                    else if (tiles[3])
                        return 6;
                    else if (tiles[5])
                        return 5;
                    else if (tiles[7])
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[3]){
                    if (tiles[5])
                        return 9;
                    else if (tiles[6])
                        return 12;
                    else if (tiles[7])
                        return 8;
                    else
                        return -1;
                }
                else
                    return -1;
            }
            if (tiles[1]){
                if (tiles[2]){
                    if (tiles[3])
                        return 6;
                    else if (tiles[5])
                        return 5;
                    else if (tiles[7])
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[3]){
                    if (tiles[5])
                        return 4;
                    else if (tiles[6])
                        return 6;
                    else if (tiles[7])
                        return 3;
                    else
                        return -1;
                }
                else if (tiles[5]){
                    if (tiles[7])
                        return 2;
                    else if (tiles[8])
                        return 5;
                    else
                        return -1;
                }
                else if ((tiles[6] && tiles[7]) || (tiles[7] && tiles[8]))
                    return 15;
                else
                    return -1;
            }
            if (tiles[2]){
                if (tiles[3] && tiles[5])
                    return 9;
                else if (tiles[5] && tiles[7])
                    return 7;
                else if (tiles[5] && tiles[8])
                    return 13;
                else
                    return -1;
            }
            if (tiles[3]){
                if (tiles[5]){
                    if (tiles[6])
                        return 9;
                    else if (tiles[7])
                        return 1;
                    else if (tiles[8])
                        return 9;
                }
                else if ((tiles[6] && tiles[7]) || (tiles[7] && tiles[8]))
                    return 8;
                else
                    return -1;
            }
            if (tiles[5]){
                if (tiles[6] && tiles[7] || tiles[7] && tiles[8])
                    return 7;
                else
                    return -1;
            }
            if (tiles[6] && tiles[7] && tiles[8])
                return 14;
            break;
        case 4:
            if (house)
                return -1;
            if (tiles[0]){
                if (tiles[1]){
                    if (tiles[2]){
                        if (tiles[3])
                            return 6;
                        else if (tiles[5])
                            return 5;
                        else if (tiles[7])
                            return 15;
                        else
                            return -1;
                    }
                    else if (tiles[3]){
                        if (tiles[5])
                            return 4;
                        else if (tiles[6])
                            return 6;
                        else if (tiles[7])
                            return 3;
                        else
                            return -1;
                    }
                    else if (tiles[5]){
                        if (tiles[7])
                            return 2;
                        else if (tiles[8])
                            return 5;
                        else
                            return -1;
                    }
                    else if ((tiles[6] && tiles[7]) || (tiles[7] && tiles[8]))
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[2] && tiles[3] && tiles[5])
                    return 9;
                else if (tiles[3]){
                    if (tiles[5]){
                        if (tiles[6])
                            return 9;
                        else if (tiles[7])
                            return 1;
                        else if (tiles[8])
                            return 9;
                        else
                            return -1;
                    }
                    else if (tiles[6] && tiles[7] || tiles[7] && tiles[8])
                        return 8;
                    else
                        return -1;
                }
                else
                    return -1;
            }
            else if (tiles[1]){
                if (tiles[2]){
                    if (tiles[3]){
                        if (tiles[5])
                            return 4;
                        else if (tiles[6])
                            return 6;
                        else if (tiles[7])
                            return 3;
                        else
                            return -1;
                    }
                    else if (tiles[5]){
                        if (tiles[7])
                            return 2;
                        else if (tiles[8])
                            return 5;
                        else
                            return -1;
                    }
                    else if ((tiles[6] && tiles[7]) || (tiles[7] && tiles[8]))
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[3]){
                    if (tiles[5]){
                        if (tiles[6])
                            return 4;
                        else if (tiles[7])
                            return 16; // special case crossroads
                        else if (tiles[8])
                            return 4;
                        else
                            return -1;
                    }
                    else if ((tiles[6] && tiles[7]) || (tiles[7] && tiles[8]))
                        return 3;
                }
                else if (tiles[5]){
                    if (tiles[6] && tiles[7] || tiles[7] && tiles[8])
                        return 2;
                    else
                        return -1;
                }
                else if (tiles[6] && tiles[7] && tiles[8])
                    return 15;
                else
                    return -1;
            }
            else if (tiles[3]){
                if (tiles[5]){
                    if (tiles[6]){
                        if (tiles[7])
                            return 1;
                        else if (tiles[8])
                            return 9;
                        else
                            return -1;
                    }
                    else if (tiles[7] && tiles[8])
                        return 1;
                    else
                        return -1;
                }
                else if (tiles[6] && tiles[7] && tiles[8])
                    return 8;
                else
                    return -1;
            }
            else if (tiles[5] && tiles[6] && tiles[7] && tiles[8])
                return 7;
            else
                return -1;
            break;
        case 5:
            if (house)
                return -1;
            if (tiles[0]){
                if (tiles[1]){
                    if (tiles[2]){
                        if (tiles[3]){
                            if (tiles[5])
                                return 9;
                            else if (tiles[6])
                                return 6;
                            else if (tiles[7])
                                return 3;
                            else
                                return -1;
                        }
                        else if (tiles[5]){
                            if (tiles[7])
                                return 2;
                            else if (tiles[8])
                                return 5;
                            else
                                return -1;
                        }
                        else if ((tiles[6] && tiles[7]) ||
                                (tiles[7] && tiles[8]))
                            return 15;
                        else
                            return -1;
                    }
                    else if (tiles[3]){
                        if (tiles[5]){
                            if (tiles[6])
                                return 4;
                            else if (tiles[7])
                                return 16; // special case crossroads
                            else if (tiles[8])
                                return 4;
                            else
                                return -1;
                        }
                        else if (tiles[6] && tiles[7])
                            return 15;
                        else if (tile[7] && tiles[8])
                            return 2;
                        else
                            return -1;
                    }
                    else if (tiles[5]){
                        if (tiles[6] && tiles[7])
                            return 3;
                        else if (tiles[7] && tiles[8])
                            return 15;
                        else
                            return -1;
                    }
                    else if (tiles[6] && tiles[7] && tiles[8])
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[2]){
                    if (tiles[3]){
                        if (tiles[5]){
                            if (tiles[6])
                                return 9;
                            else if (tiles[7])
                                return 1;
                            else if (tiles[8])
                                return 9;
                            else
                                return -1;
                        }
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if (tiles[3]){
                    if (tiles[5]){
                        if (tiles[6]){
                            if (tiles[7])
                                return 1;
                            else if (tiles[8])
                                return 9;
                            else
                                return -1;
                        }
                        else if (tiles[7] && tiles[8])
                            return 1;
                        else
                            return -1;
                    }
                    else if (tiles[6] && tiles[7] && tiles[8])
                        return 8;
                    else
                        return -1;
                }
                else 
                    return -1;
            }
            else if (tiles[1]){
                if (tiles[2]){
                    if (tiles[3]){
                        if (tiles[5]){
                            if (tiles[6])
                                return 4;
                            else if (tiles[7])
                                return 16; // special case crossroads
                            else if (tiles[8])
                                return 4;
                            else
                                return -1;
                        }
                        else if (tiles[6]){
                            if (tiles[7])
                                return 2;
                            else
                                return -1;
                        }
                        else if (tiles[7] && tiles[8])
                            return 2;
                        else
                            return -1;
                    }
                    else if (tiles[5]){
                        if (tiles[6] && tiles[7])
                            return 3;
                        else if (tiles[7] && tiles[8])
                            return 15;
                        else
                            return -1;
                    }
                    else if (tiles[6] && tiles[7] && tiles[8])
                        return 15;
                    else
                        return -1;
                }
                else if (tiles[3]){
                    if (tiles[5]){
                        if (tiles[6] && tiles[7])
                            return 16; // special case crossroads
                        else if (tiles[6] && tiles[8])
                            return 4;
                        else if (tiles[7] && tiles[8])
                            return 16; // special case crossroads
                        else
                            return -1;
                    }
                    else if (tiles[6] && tiles[7] && tiles[8])
                        return 2;
                    else
                        return -1;
                }
                else if (tiles[5] && tiles[6] && tiles[7] && tiles[8])
                    return 3;
                else
                    return -1;
            }
            else if (tiles[2]){
                if (tiles[3]){
                    if (tiles[5]){
                        if (tiles[6]){
                            if (tiles[7])
                                return 1;
                            else if (tiles[8])
                                return 9;
                            else
                                return -1;
                        }
                        else if (tiles[7] && tiles[8])
                            return 1;
                        else
                            return -1;
                    }
                    else 
                        return -1;
                }
                else if (tiles[5]){
                    if (tiles[6] && tiles[7] && tiles[8])
                        return 7;
                    else
                        return -1;
                }
                else
                    return -1;
            }
            else if (tiles[3]){
                if (tiles[5]){
                    if (tiles[6] && tiles[7] && tiles[8])
                        return 9;
                    else
                        return -1;
                }
                else
                    return -1;
            }
            else
                return -1;
            break;
        case 6:
            if (house)
                return -1;
            if (!tiles[0]){
                if (!tiles[1])
                    return 9;
                else if (!tiles[2])
                    return 4;
                else if (!tiles[3])
                    return 15;
                else if (!tiles[6])
                    return 2;
                else if (!tiles[8])
                    return 16; // special case crossroads
                else
                    return -1;
            }
            else if (!tiles[1] && !tiles[2])
                return 9;
            else if (!tiles[2]){
                if (!tiles[5])
                    return 15;
                else if (!tiles[6])
                    return 16;
                else if (!tiles[8])
                    return 3;
                else
                    return -1;
            }
            else if (!tiles[3] && !tiles[6])
                return 15;
            else if (!tiles[5] && !tiles[8])
                return 15;
            else if (!tiles[6]){
                if (!tiles[7])
                    return 9;
                else if (!tiles[8])
                    return 1;
                else
                    return -1;
            }
            else if (!tiles[7] && !tiles[8])
                return 9;
            else
                return -1;
            break;
        case 7:
            if (house)
                return -1;
            if (!tiles[0])
                return 6;
            else if (!tiles[1] || !tiles[7])
                return 9;
            else if (!tiles[2])
                return 5;
            else if (!tiles[3] || !tiles[5])
                return 15;
            else if (!tiles[6])
                return 8;
            else if (!tiles[8])
                return 7;
            else
                return -1;
            break;
        case 8:
            if (house)
                return -1;
            return 0;
            break;
    }
}

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
    SDL_Surface* UCornerTop = IMG_Load("UCornerTop.png");
    SDL_Surface* HouseWall = IMG_Load("HouseWall.png");
    SDL_Surface* 1DIntersectionTop = IMG_Load("1DIntersectionTop.png");
    SDL_Surface* 1DIntersectionBottom = IMG_Load("1DIntersectionBottom.png");
    SDL_Surface* 1DIntersectionLeft = IMG_Load("1DIntersectionLeft.png");
    SDL_Surface* 1DIntersectionRight = IMG_Load("1DIntersectionRight.png");

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
    int* nbWalls = malloc(sizeof(int));
    char* adjacentTiles;
    for (int y = 0; y < ROW; y++){
        for (int x = 0; x < COL; x++){
            if (grid[y * COL + x] == WALL || grid[y * COL + x] == WALL2){
                int house = 0;
                adjacentTiles = nbAdjacentWalls(grid, x, y, nbWalls, &house);
                //TODO : choose the correct tile
                free(adjacentTiles);
            }
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
