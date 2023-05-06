#ifndef LAZYFOO_H
#define LAZYFOO_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

SDL_Window* init( void );
SDL_Surface* loadSurface( char *path, SDL_Surface *formatSrc );
SDL_Surface* optimizeSurface( SDL_Surface *loadedSurface, SDL_PixelFormat *format );

SDL_Texture* loadTexture( SDL_Renderer *render, char *path );
SDL_Texture* freeTextureFromSurface( SDL_Renderer *render, SDL_Surface *sourceSurf );

/* libimg exclusive */
int imgInit(int flags);
SDL_Surface* loadPNGSurface( char *path, SDL_Surface *formatSrc );
SDL_Texture* loadPNGTexture( SDL_Renderer *render, char *path );

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#endif
