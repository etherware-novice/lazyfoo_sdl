#include "lazyfoo.h"

SDL_Window* init(void)
{
	SDL_Window* gWindow = NULL;
	int initStatus = SDL_Init( SDL_INIT_VIDEO );
	if( initStatus < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}

	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	if( gWindow == NULL ) printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );

	return gWindow;
}


SDL_Surface* loadSurface( char *path, SDL_Surface *formatSrc )
{
	SDL_Surface* loadedSurface = SDL_LoadBMP( path );

	if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError() );
	else if( formatSrc != NULL) loadedSurface = optimizeSurface( loadedSurface, formatSrc->format );

	return loadedSurface;
}	

SDL_Surface* optimizeSurface( SDL_Surface *origSurface, SDL_PixelFormat *format )
{
	SDL_Surface* optimizedSurface = SDL_ConvertSurface( origSurface, format, 0 );
	if( optimizedSurface == NULL )
	{
		printf( "Unable to optimize image! SDL_Error: %s\n", SDL_GetError );
		return origSurface;
	}
	SDL_FreeSurface( origSurface );
	return optimizedSurface;
}

SDL_Texture* loadTexture( SDL_Renderer *render, char *path )
{
	SDL_Texture *loadedTexture = NULL;
	SDL_Surface *loadedSurface = loadSurface( path, NULL );
	if( !loadedSurface ) return NULL;

	loadedTexture = freeTextureFromSurface( render, loadedSurface );
	if( !loadedTexture ) printf( "Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
}

SDL_Texture* freeTextureFromSurface( SDL_Renderer *render, SDL_Surface *sourceSurf )
{
	SDL_Texture *newTexture = SDL_CreateTextureFromSurface( render, sourceSurf );
	if( newTexture ) SDL_FreeSurface( sourceSurf );
	return newTexture;
}

