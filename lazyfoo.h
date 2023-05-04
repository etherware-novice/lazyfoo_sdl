#ifndef LAZYFOO_H
#define LAZYFOO_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

SDL_Window* init( void );
SDL_Surface* loadSurface( char *path, SDL_Surface *formatSrc );
SDL_Surface* optimizeSurface( SDL_Surface *loadedSurface, SDL_PixelFormat *format );

/* libimg exclusive */
int imgInit(int flags);
SDL_Surface* loadPNGSurface( char *path, SDL_Surface *formatSrc );

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#endif
