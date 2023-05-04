#include "lazyfoo.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

bool loadMedia(void);
void clean(void);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;


bool loadMedia(void)
{
	gImage = SDL_LoadBMP( "img/helloworld.bmp" );
	if( gImage == NULL )
	{
		printf( "Unable to load image! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	return true;
}

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
	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
		return 2;
	}

	SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface( gWindow );

	SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	clean();
	return 0;
}
