#include "lazyfoo.h"
#define MAX_FILEPATH	20
#define IMAGE_FOLDER	"img/"

#define SETCUR(x) gCurrentSurface = gKeySurface[x]

enum Keys
{
	DEFAULT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	TOTAL,
};

const char *keyImage[] = { "press.bmp", "up.bmp", "down.bmp", "left.bmp", "right.bmp", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa" };

bool loadMedia(void);
void clean(void);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gKeySurface[ TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

bool loadMedia(void)
{
	bool success = true;
	unsigned short int i;
	const char *curStr;
	char filename[MAX_FILEPATH];

	for( i = 0; ( curStr = keyImage[i] ) != '\0'; i++ )
	{
		filename[0] = '\0';
		if( strlen( IMAGE_FOLDER ) + strlen( curStr ) > MAX_FILEPATH ){
			printf("File %s is too long! Skipping..\n", curStr);
			continue;
		}
		strcat( filename, IMAGE_FOLDER );
		strcat( filename, curStr );
		if( ( gKeySurface[i] = loadSurface( filename, NULL ) ) == NULL )
		{
			printf( "\nFailed to load image %s! SDL_Error %s\n", filename, SDL_GetError() );
			success = false;
		}
	}
	return success;

}

void clean()
{
	for( unsigned short int i = 0; i < TOTAL; ++i )
	{
		SDL_FreeSurface( gKeySurface[i] );
		gKeySurface[i] = NULL;
	}
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	SDL_Quit();
}

int main()
{
	if( ( gWindow = init() ) == NULL )
	{
		printf( "Failed to initialize!\n" );
	}
	gScreenSurface = SDL_GetWindowSurface( gWindow );

	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
	}

	bool quit = false;
	SDL_Event e;

	gCurrentSurface = gKeySurface[ DEFAULT ];

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) quit = true;
			else if( e.type = SDL_KEYDOWN )
				switch( e.key.keysym.sym )
				{
					case SDLK_UP:
						SETCUR(UP);
						break;
					case SDLK_DOWN:
						SETCUR(DOWN);
						break;
					case SDLK_LEFT:
						SETCUR(LEFT);
						break;
					case SDLK_RIGHT:
						SETCUR(RIGHT);
						break;
					default:
						SETCUR(DEFAULT);
						break;
				}
		}
		SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
		SDL_UpdateWindowSurface( gWindow );
	}

	printf("exiting..");
	clean();
	return 0;
}
