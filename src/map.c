#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 28
#define COL 36

void init_map(char* map){
  map = calloc(ROW * COL, sizeof(char));
  map->points = 0;
}

void free_map(char* map){
  free(map);
}

void load_map(char* map){
  //TODO
}

void save_map(char* map){
  //TODO
}

void printMap() 
{
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      printf("%c", map[i][j]);
    }
    printf("\n");
  }
}

int main() 
{
    initMap();
    printMap();
    return 0;
}
