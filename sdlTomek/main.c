#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif
 void func(unsigned char* line[], int pixelQuantity, int operation, int contrast); //contrast=<-255,255>; operation: 0=histogram, 1=kontrast
#ifdef __cplusplus
}
#endif

const int WIDTH = 150, HEIGHT = 150;
int newContrast = 0;
const int maxContrast = 255;
const int minContrast = -255;
size_t fileSize; //rozmiar pliku obrazka: 138B header + 4*pixelQuantity B danych o pixelach
char *fileData = NULL; //tutaj trzymam oryginalny obrazek
char *tmpFileData = NULL;
unsigned int pixelQuantity=0;

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

        tmpFileData = malloc(sizeof(char) * fileSize);
	}
	else printf("Error opening the file\n");
	fclose(file);
    pixelQuantity = (fileSize-138)/4;
    printf("File size: %ld, pixels quantity: %ld\n", fileSize, (fileSize-138)/4);
}

void refactor(int operation, int contrast){
    //copyMyFile(); //jesli chcemy wykonywac operacje caly czas z tego samego obrazku to wykomentowac, jesli chcemy wykoywac operacje z orginaly to zostawic
    char* imgData = tmpFileData+138;
    unsigned char red, green, blue, alpha;
    /*for(int i=0; i<pixelQuantity; ++i){
        // blue = (short) *imgData;
        // blue &= 0xff;
        // green = (short) *(imgData+1);
        // green &= 0xff;
        // red = (short) *(imgData+2);
        // red &= 0xff;
        // alpha = (short) *(imgData+3);
        // alpha &= 0xff;
        // printf("%d: b%hi g%hi r%hi a%hi\n", i, blue, green, red, alpha );

        blue = *imgData;
        green =  *(imgData+1);
        red =  *(imgData+2);
        *imgData = (blue+10)%255;
        *(imgData+1) = (green+10)%255;
        *(imgData+2) = (red+10)%255;
        imgData+=4;
    }*/

    func(imgData, pixelQuantity, operation, contrast);
}
void copyMyFile(){
    for(int i=0; i<fileSize; ++i){
        *(tmpFileData+i) = *(fileData+i);
    }
}

int main( int argc, char *argv[] )
{
    LoadBmp("g.bmp"); //////////////////////////////////////////////          FILE NAME
    copyMyFile();
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *windowSurface = NULL;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
	    printf("ERROR\n");
    }

    SDL_Window *window = SDL_CreateWindow( "ARKO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
    windowSurface = SDL_GetWindowSurface( window );

    if ( NULL == window ) {
	    printf("ERROR\n");
        return EXIT_FAILURE;
    }

    SDL_Event windowEvent;

	SDL_RWops *data = SDL_RWFromMem(fileData, fileSize);
    imageSurface = SDL_LoadBMP_RW(data, 0);

    if( imageSurface == NULL ) {
	    printf("ERROR\n");
    }

    int workingProgram=1;
    while ( workingProgram )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if (SDL_KEYDOWN == windowEvent.type)
            {
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_LEFT:  
                        newContrast = --newContrast < minContrast ? minContrast : newContrast; 
                        printf("Contrast: %d\n", newContrast);
                        refactor(1,newContrast);
                        break;
                    case SDLK_RIGHT: 
                        newContrast = ++newContrast > maxContrast ? maxContrast : newContrast; 
                        printf("Contrast: %d\n", newContrast);
                        refactor(1,newContrast);
                        break;
                        break;
                    case SDLK_UP: //rozciagniecie histogramu
                        copyMyFile(); //przywrocenie z oryginalu
                        refactor(0, 0);
                        break;
                    case SDLK_DOWN: //przywrocenie oryginalu
                        copyMyFile();
                        printf("Original pic\n");
                        break;
                    case SDLK_ESCAPE: workingProgram=0; break;
                }
                //refactor(0,0);

                SDL_FillRect(windowSurface, NULL, 0x000000);

                SDL_RWops *data = SDL_RWFromMem(tmpFileData, fileSize);
                imageSurface = SDL_LoadBMP_RW(data, 0);
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

