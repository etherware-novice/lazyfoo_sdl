#include "lazyfoo.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

void clean(void);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;


void clean(void)
{
	SDL_FreeSurface( gImage );
	gImage = NULL;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	SDL_Quit();
}

int main()
{
	gWindow = init();
	if( !gWindow )
	{
		printf( "Failed to initialize!\n" );
		return 1;
	}
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	if( !( gImage = loadSurface( "img/helloworld.bmp", gScreenSurface ) ) )
	{
		printf( "Failed to load media!\n" );
		return 2;
	}

	bool quit = false;
	SDL_Event e;

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) quit = true;
		}

		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		SDL_BlitScaled( gImage, NULL, gScreenSurface, &stretchRect );
		SDL_UpdateWindowSurface( gWindow );
	}



	clean();
	return 0;
}
