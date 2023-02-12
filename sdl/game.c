#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "game.h"

void play(SDL_Surface* screen)
{
	SDL_Event event;
	int continuer = 1;
	int i=0; j=0;
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
		}

		SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255);		
		SDL_Flip(screen);
	}
}

