#ifndef PLAY_H
#define PLAY_H

void Move(SDL_Rect* pos,int direction);
void draw_game(SDL_Renderer* renderer,Game* game,int map_load);

#endif