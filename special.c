#include "lazyfoo.h"
#include <SDL2/SDL_image.h>

int imgInit(int flags)
{
	if( !( IMG_Init( flags ) & flags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	return true;
}

SDL_Surface* loadPNGSurface( char *path, SDL_Surface *formatSrc )
{
	SDL_Surface *loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL Error: %s\n",
			path, SDL_GetError() );
	else if( formatSrc != NULL ) loadedSurface = optimizeSurface( loadedSurface, formatSrc->format );

	return loadedSurface;
}

SDL_Texture* loadPNGTexture( SDL_Renderer *render, char *path )
{
	SDL_Texture *loadedTexture = NULL;
	SDL_Surface *loadedSurface = loadPNGSurface( path, NULL );
	if( !loadedSurface ) return NULL;

	loadedTexture = freeTextureFromSurface( render, loadedSurface );
	if( !loadedTexture ) printf( "Unable to create texture from PNG %s! SDL Error: %s", SDL_GetError() );
	return loadedTexture;
}
