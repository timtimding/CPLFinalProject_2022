#include "Texture.h"

lTexture TextureSet[SAMPLE + 1], gTextTexture;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

int SoundLoud = 50;

bool SoundOn = true;

bool IsSound(){
    return SoundOn;
}

void SoundSwitch(bool s){
    SoundOn = s;
}

bool leaveAlert(SDL_Event *e){
    ShowAlert();
    while(true){
    while(SDL_PollEvent(e) != 0){
        if(e->type == SDL_QUIT){
            return true;
        }else if(e->type == SDL_KEYDOWN){
            switch(e->key.keysym.sym)
            {
                case SDLK_y:
                    return true;
                    break;
                case SDLK_RETURN:
                    return true;
                    break;
                case SDLK_n:
                    std::cout << "I dont wanna leave" << std::endl;
                    screenRefresh();
                    return false;
                    break;
                default:
                    break;
            }
        }
    }
    }
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	//Free loaded images
	for(int i = 0; i < SAMPLE; i++)
        TextureSet[i].free();

    TTF_CloseFont( gFont );
	gFont = NULL;

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

bool handleEvent(SDL_Event *e, Picture n){
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch(n){
        case STARTPLAYINGBUTTON:
            if(x <= SCREEN_WIDTH / 2 - 20 && x >= SCREEN_WIDTH / 2 - 20 - TextureSet[n].getWidth() && \
                y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2 && y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case SETTINGBUTTON:
            if(x >= SCREEN_WIDTH / 2 + 20 && x <= SCREEN_WIDTH / 2 + 20 + TextureSet[n].getWidth() && \
                y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() - 10 && y <= SCREEN_HEIGHT / 2 - 10)
                return true;
            else
                return false;
            break;
        case BACKBUTTON:
            if(x <= SCREEN_WIDTH / 2 + TextureSet[n].getWidth() / 2 && x >= SCREEN_WIDTH / 2 - TextureSet[n].getWidth() / 2 && \
                y >= SCREEN_HEIGHT *4 / 5 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT * 4 / 5 + TextureSet[n].getHeight() / 2){
                std::cout << "Clicked" << std::endl;
                return true;
            }
            else
                return false;
            break;
        case TUTORIALBUTTON:
            if(x >= SCREEN_WIDTH / 2 + 20 && x <= SCREEN_WIDTH / 2 + 20 + TextureSet[n].getWidth() && \
                y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() + 10 && y >= SCREEN_HEIGHT / 2 + 10)
                return true;
            else
                return false;
            break;
        case PAUSE:
            if(x >= SCREEN_WIDTH * 5 / 6 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH * 5 / 6 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 5 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 5 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case HELP:
            if(x >= SCREEN_WIDTH * 5 / 6 - TextureSet[n].getWidth() / 2 + 90 && x <= SCREEN_WIDTH * 5 / 6 + TextureSet[n].getWidth() / 2 + 90&& \
            y >= SCREEN_HEIGHT / 5 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 5 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case AGAIN:
            if(x >= SCREEN_WIDTH / 2 - 136 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 136 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEVEL1:
            if(x >= SCREEN_WIDTH / 2 - 400 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 400 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEVEL2:
            if(x >= SCREEN_WIDTH / 2 - 200 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 200 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEVEL3:
            if(x >= SCREEN_WIDTH / 2 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEVEL4:
            if(x >= SCREEN_WIDTH / 2 + 200 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + 200 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEVEL5:
            if(x >= SCREEN_WIDTH / 2 + 400 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + 400 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case BACKTOSELECTOR:
            if(x >= SCREEN_WIDTH / 2 + 100 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + 100 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case LEAVE:
            if(x >= SCREEN_WIDTH / 2 - 150 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 150 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case SOUNDON:
            if(x >= SCREEN_WIDTH / 2 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT * 2 / 5 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT * 2 / 5 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case RESTART:
            if(x >= SCREEN_WIDTH / 2 - 50 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 50 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case RESUME:
            if(x >= SCREEN_WIDTH / 2 + 50 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + 50 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case DRAGGER:
            return(!(distance(x, SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() * (SoundLoud - 50) / 100, y, SCREEN_HEIGHT * 3 / 5 - TextureSet[SOUNDBAR].getHeight() / 2) > ( TextureSet[n].getWidth() / 2) * (TextureSet[n].getWidth() / 2)));
            break;
        case SOUNDBAR:
            return(x <= SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2 && x >= SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2 && y >= SCREEN_HEIGHT * 3 / 5 - TextureSet[SOUNDBAR].getHeight() / 2 && y <= SCREEN_HEIGHT * 3 / 5 + TextureSet[SOUNDBAR].getHeight() / 2);
            break;
        default:
            break;
    }
    return false;
}

void screenRefresh(){
    SDL_SetRenderDrawColor( gRenderer, 0, 0xFF, 0xFF, 0 );
    SDL_RenderClear( gRenderer );
}

void screenShow(){
    SDL_RenderPresent( gRenderer );
}

void drawGrayScreen(){
    SDL_SetRenderTarget(gRenderer, NULL);
    //SDL_SetTextureAlphaMod( gTexture, 120 );
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
}


void Draw(Picture n, int x, int y, int w, int h){
    SDL_Rect renderQuad = { x, y, w, h};
    if(w == 0 && h == 0){
        renderQuad.w = SCREEN_WIDTH;
        renderQuad.h = SCREEN_HEIGHT;
    }
    else if(w == -1 && h == -1){
        renderQuad.x -= TextureSet[n].getWidth() / 2;
        renderQuad.y -= TextureSet[n].getHeight() / 2;
        renderQuad.w = TextureSet[n].getWidth();
        renderQuad.h = TextureSet[n].getHeight();
    }
    else if(w == -2 && h == -2){
        {
            switch(n){
                case DRAGGER:
                    renderQuad.x = SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() * (SoundLoud - 50) / 100- TextureSet[n].getWidth() / 2;
                    renderQuad.y =  SCREEN_HEIGHT * 3 / 5 - TextureSet[n].getHeight() / 2;
                    renderQuad.w = TextureSet[n].getWidth();
                    renderQuad.h = TextureSet[n].getHeight();
                    break;
                case SOUNDON:
                    renderQuad.x = SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2;
                    renderQuad.y = SCREEN_HEIGHT * 3 / 5 - TextureSet[SOUNDBAR].getHeight() / 2;
                    renderQuad.w = TextureSet[SOUNDBAR].getWidth() * SoundLoud / 100;
                    renderQuad.h = TextureSet[SOUNDBAR].getHeight();
                    break;
                case SOUNDSTATUS:
                    renderQuad.x = SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2;
                    renderQuad.y =  SCREEN_HEIGHT * 3 / 5 - TextureSet[n].getHeight() / 2;
                    renderQuad.w = TextureSet[SOUNDBAR].getWidth() * SoundLoud / 100;
                    renderQuad.h = TextureSet[n].getHeight();
                    break;
                default:
                    break;
            }
        }
    }
	SDL_RenderCopy( gRenderer, TextureSet[n].gTexture, NULL, &renderQuad );
}

void setSound(SDL_Event *e){std::cout << SoundLoud << std::endl;
    int x, y;
    while(SDL_PollEvent(e) != 0){

        if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&x, &y);
            if(x < (SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth()) || x > (SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth())){
                SoundLoud = (x - (SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth()) / TextureSet[SOUNDBAR].getWidth());
                Draw(SOUNDON, -1, -1, -1, -1);
                Draw(DRAGGER,-1, -1, -1, -1);
                screenShow();
            }
        }
        else
            return;
    }

}

void clickSetSound(SDL_Event *e){
    int x, y;
    SDL_GetMouseState(&x, &y);
    SoundLoud = 100 * (x - SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2) / TextureSet[SOUNDBAR].getWidth();
    std::cout << SoundLoud << std::endl;
    RenderSetting(IsSound());
}

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

bool loadMedia(std::string path, Picture n)
{
    bool success = true;
    if(!TextureSet[n].loadFromFile( path ))
        success = false;
	return success;
}

bool loadFont(const char * path, int n){
    bool success = true;
    gFont = TTF_OpenFont( path, n );
    if( gFont == NULL )
        success = false;
    return success;
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

int lTexture::getWidth()
{
	return width;
}

int lTexture::getHeight()
{
	return height;
}

bool lTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
        gTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( gTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	return gTexture != NULL;
}

void lTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( gTexture, red, green, blue );
}
