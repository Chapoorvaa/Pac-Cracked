#include"txtToPNG.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char DEFAULT_MAP[] = {"############################............#............##.####.#####.#.#####.####.##o####.#####.#.#####.####o##.####.#####.#.#####.####.##.........................##.####.##.#######.##.####.##.####.##.#######.##.####.##......##....#....##......#######.##### # #####.######     #.##### # #####.#          #.##         ##.#          #.## ###_### ##.#          #.   #     #   .#          #.## ####### ##.#          #.##         ##.#          #.## ####### ##.#     ######.## ####### ##.#######............#............##.####.#####.#.#####.####.##.####.#####.#.#####.####.##o..##...............##..o####.##.##.#######.##.##.######.##.##.#######.##.##.####......##....#....##......##.##########.#.##########.##.##########.#.##########.##.........................############################"};

int main(int argc, char** argv){
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }
    //char* input = argv[1];
    char* output = argv[2];
    //char* buffer = NULL;
    /*size_t size = 0;
    FILE* file = fopen(input, "r");
    if(file == NULL){
        printf("Error: could not open file %s\n", input);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    buffer = malloc((size + 1) * sizeof(*buffer));
    fread(buffer, size, 1, file);
    buffer[size] = '\0';
    fclose(file);*/
    char* buffer = DEFAULT_MAP;
    combinePNGs(output,buffer);
    
    //free(buffer);
    return 0;
}
