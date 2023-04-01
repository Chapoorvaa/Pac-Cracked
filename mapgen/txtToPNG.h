#ifndef TXT_TO_PNG
#define TXT_TO_PNG

// Here we will take charge of transforming map in txt format to a png format

#include "../src/map.h"

// From the 10 default sprites build the map in PNG format with the map in 
// an array
void combinePNGs(const char* outputFilename, const char** map, int width, 
        int height);

#endif
