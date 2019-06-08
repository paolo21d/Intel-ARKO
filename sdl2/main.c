#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

int newW = 320;
int newH = 240;
const int maxW = 740;
const int maxH = 400;
const int minW = 10;
const int minH = 10;
const int diff = 20;

#ifdef __cplusplus
extern "C" {
#endif
 int func(char *a, char* b, int nw, int nh);
#ifdef __cplusplus
}
#endif

const int WIDTH = 150, HEIGHT = 150;

size_t fileSize;
char *fileData = NULL;

char output[4000000];

void LoadBmp(const char *fileName)
{
	if (fileData != NULL)
	{
		free(fileData);
		fileData = NULL;
	}

	FILE *file = fopen(fileName, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		fileData = malloc(sizeof(char) * fileSize);
		fread(fileData, sizeof(char), fileSize, file);
	}
	else printf("Error opening the file\n");
	fclose(file);
}

int main( int argc, char *argv[] )
{
	LoadBmp("g.bmp");

    SDL_Surface *imageSurface = NULL;
    SDL_Surface *windowSurface = NULL;
    
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
	    printf("ERROR1: SDL could not initialize!\n");
    }
    
    SDL_Window *window = SDL_CreateWindow( "ARKO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
    windowSurface = SDL_GetWindowSurface( window );
    
    if ( NULL == window )
    {
	    printf("ERROR2: Could not create window\n");
        
        return EXIT_FAILURE;
    }
    
    SDL_Event windowEvent;
    
	SDL_RWops *data = SDL_RWFromMem(fileData, fileSize);
    imageSurface = SDL_LoadBMP_RW(data, 0);

    if( imageSurface == NULL )
    {
	    printf("ERROR3: SDL could not load image!\n");
    }
    
    int program=1;
    while ( program )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if (SDL_KEYDOWN == windowEvent.type )
            {
                int prevW = newW;
                int prevH = newH;

                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_LEFT:  newW -= diff; if (newW < minW) newW = minW; break;
                    case SDLK_RIGHT: newW += diff; if (newW > maxW) newW = maxW; break;
                    case SDLK_UP:    newH -= diff; if (newH < minH) newH = minH; break;
                    case SDLK_DOWN:  newH += diff; if (newH > maxH) newH = maxH; break;
                    case SDLK_ESCAPE: program = 0; break;
                }

                if (prevW != newW || prevH != newH)
                {
                    func(fileData, output, newW, newH);

                    SDL_FillRect(windowSurface, NULL, 0x000000);
                    SDL_RWops *data = SDL_RWFromMem(output, newW*newH*4+138);
                    imageSurface = SDL_LoadBMP_RW(data, 0);
                }

                
            }
            else if ( SDL_QUIT == windowEvent.type )
            {
                break;		
            }
        }
        
        SDL_BlitSurface( imageSurface, NULL, windowSurface, NULL );
        SDL_UpdateWindowSurface( window );
    }
    
    SDL_FreeSurface( imageSurface );
    SDL_FreeSurface( windowSurface );
    
    imageSurface = NULL;
    windowSurface = NULL;
    
    SDL_DestroyWindow( window );
    SDL_Quit( );
    
    return EXIT_SUCCESS;
}

