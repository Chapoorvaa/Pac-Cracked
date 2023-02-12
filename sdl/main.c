#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>


const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;

int main(int argc,char*argv[])
{
	SDL_Surface *screen = NULL;
	SDL_Surface *menu = NULL;

	SDL_Rect positionMenu;
	
	int continuer = 3 ;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
        	errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	/*SDL_WM_SetIcon(IMG_Load("logo.png"),NULL);*/
	screen = SDL_SetVideoMode(952,442,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Pac Cracked",NULL);
	

	menu = IMG_Load("logo.png");
	positionMenu.x = 0
	posiionMenu.y = 0

	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_KP_ENTER:
						play(screen);
						break;

				}
				break;
		}
		SDL_BlitSurface(menu,NULL,screen,&positionMenu);
		SDL_Flip(screen)
	}
	SDL_FreeSurface(menu);
	SDL_Quit();
	return EXIT_SUCCESS;
}
