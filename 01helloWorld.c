#include "lazyfoo.h"

int main()
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if( ( window = init() ) == NULL )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	screenSurface = SDL_GetWindowSurface( window );
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x9F, 0xFF, 0xFF ) );

	SDL_UpdateWindowSurface( window );

	SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
