#include "lazyfoo.h"
#include <SDL2/SDL_image.h>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;

void clean( void );

void clean( void )
{
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main()
{
	gWindow = init();
	if( !gWindow )
	{
		printf( "Failed to initalize!\n" );
		return 1;
	}
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

	if( !gRenderer )
	{
		printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 2;
	}

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	if( !imgInit( IMG_INIT_PNG ) ) return 3;

	gTexture = loadPNGTexture( gRenderer, "img/rfirebad.png" );
	if( !gTexture ) return 4;

	bool quit = false;
	SDL_Event e;

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) quit = true;
		}
		SDL_RenderClear( gRenderer );
		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
		SDL_RenderPresent( gRenderer );
	}

	printf( "exiting.." );
	clean();
}
