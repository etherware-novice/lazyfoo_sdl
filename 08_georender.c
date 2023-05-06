#include "lazyfoo.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

void clean( void )
{
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_DestroyRenderer ( gRenderer );
	gRenderer = NULL;

	SDL_Quit();
}

int main()
{
	gWindow = init();
	if(!gWindow)
	{
		printf( "Failed to initialize!" );
		return 1;
	}

	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if(!gRenderer)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		// red filled rectangle
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( gRenderer, &fillRect );

		// green outlined rectangle
		SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
		SDL_RenderDrawRect( gRenderer, &outlineRect );

		// blue horizontal line
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
		SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

		// vertical dotted yellow line
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
		for( int i = 0; i < SCREEN_HEIGHT; i+=4 )
		{
			SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
		}
		SDL_RenderPresent( gRenderer );
	}
	printf( "Exiting.." );
	clean();
}
