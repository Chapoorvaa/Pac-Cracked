#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 28
#define COL 36

char map[ROW][COL];

void initMap() {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
        map[i][j] = 0;
      
    }
  }
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