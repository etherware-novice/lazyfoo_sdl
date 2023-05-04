#include "lazyfoo.h"
#include <SDL2/SDL_image.h>

SDL_Window *gWindow = NULL;
SDL_Surface *gScrSurf = NULL;
SDL_Surface *gImage = NULL;

void clean(void);

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
	if( ( gWindow = init() ) == NULL )
	{
		printf( "Failed to initialize!\n" );
		return 1;
	}
	gScrSurf = SDL_GetWindowSurface( gWindow );
	if( ( gImage = loadPNGSurface( "img/rfirebad.png", gScrSurf ) ) == NULL )
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

		SDL_BlitScaled( gImage, NULL, gScrSurf, &stretchRect );
		SDL_UpdateWindowSurface( gWindow );
	}

	printf("exiting..");
	clean();
	return 0;
}
