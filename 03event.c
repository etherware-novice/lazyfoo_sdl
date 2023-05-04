#include "lazyfoo.h"

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
		printf( "Unable to load image! SDL_Error: %s\n", SDL_GetError() );
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
	if( ( gWindow = init() ) == NULL )
	{
		printf("Failed to initialize!\n");
		return 1;
	}
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	
	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
	}

	bool quit = false;
	SDL_Event e;

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 ) if( e.type == SDL_QUIT ) quit = true;
		SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL );
		SDL_UpdateWindowSurface( gWindow );
	}

	printf( "exiting" );
	clean();

}
