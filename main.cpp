#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum Picture{
    Welcome,
    Button,
    Menu,
    Sample
};

class lTexture{
public:
    lTexture();

    ~lTexture();

    bool loadFromFile(std::string path);

    void free();

    void render(int, int);

    int getWidth();

    int getHeight();

private:
    SDL_Texture * gTexture;
    int width;
    int height;

};

bool init();

void close();

bool loadMedia();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

lTexture TextureSet[Sample + 1];

lTexture::lTexture(){
    gTexture = NULL;
    width = 0;
    width = 0;
}

lTexture::~lTexture(){
    free();
}

bool lTexture::loadFromFile( std::string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	gTexture = newTexture;
	return gTexture != NULL;
}

void lTexture::free()
{
	if( gTexture != NULL )
	{
		SDL_DestroyTexture( gTexture );
		gTexture = NULL;
		width = 0;
		height = 0;
	}
}


void lTexture::render(int x, int y)
{
    SDL_Rect renderQuad = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
    if(x == -1 && y == -1){
        renderQuad.x = SCREEN_WIDTH / 2 - TextureSet[Button].getWidth() / 2;
        renderQuad.y = 3 * SCREEN_HEIGHT / 4;
        renderQuad.w = this->getWidth();
        renderQuad.h = this->getHeight();
    }else{
        ;
    }
	//Set rendering space and render to screen
	SDL_RenderCopy( gRenderer, gTexture, NULL, &renderQuad );
}

int lTexture::getWidth()
{
	return width;
}

int lTexture::getHeight()
{
	return height;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !TextureSet[Welcome].loadFromFile( "img/Welcome.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !TextureSet[Menu].loadFromFile( "img/menu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !TextureSet[Button].loadFromFile( "img/buttonset.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !TextureSet[Sample].loadFromFile( "img/sample.bmp" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	for(int i = 0; i < Sample; i++)
        TextureSet[i].free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
int distance(int x, int m, int y, int n){
    return ((x - m)*(x - m) + (y - n)*(y - n));
}

bool handleEvent(SDL_Event *e, lTexture *button){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(distance(x, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, y) > ( button->getWidth() / 2) * (button->getWidth() / 2))
        return false;
    else
        return true;
}

int main( int argc, char* args[] )
{
    bool enter = false;
    bool games = false;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            TextureSet[Welcome].render(0, 0);
			bool quit = false;
			SDL_Event e;

			while( !quit )
			{
			    while(SDL_PollEvent(&e) != 0){
                    if(!enter){
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        else if(e.type == SDL_KEYUP || SDL_MOUSEBUTTONUP)
                        {
                            enter = true;
                        }

                    }else if(!games){
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        /*else if(e.key.keysym.sym == SDLK_ESCAPE){
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            TextureSet[Welcome].render(0, 0);
                            enter = false;
                        }*/
                        else if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if(handleEvent(&e ,&TextureSet[Button]) == true)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                TextureSet[Sample].render(0, 0);
                                games = true;
                            }
                            else
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                TextureSet[Menu].render(0, 0);
                                TextureSet[Button].render(-1, -1);
                            }
                        }
                    }else{
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        else if(e.key.keysym.sym == SDLK_ESCAPE){
                            games = false;
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            TextureSet[Menu].render(0, 0);
                            TextureSet[Button].render(-1, -1);

                        }
                        else
                        {
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            TextureSet[Sample].render(0,0);
                        }
                    }
                }
                //Update screen
				SDL_RenderPresent( gRenderer );
            }


			}
		}

	//Free resources and close SDL
	close();

	return 0;
}
