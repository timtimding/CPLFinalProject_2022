#include "Texture.h"

lTexture TextureSet[SAMPLE + 1], gTextTexture;

lTexture MovementSet[MOVEMENTTOTAL];

lTexture AttackSet[ATTACKTOTAL];

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

Mix_Music *gMusic = NULL;

TTF_Font* gFont = NULL;

SDL_Color textColor = {0, 0, 0, 255};

int SoundLoud = 50;

bool SoundOn = true;

std::stringstream writeText;

bool IsSound(){
    return SoundOn;
}

int getSound(){
    return SoundLoud;
}

void setSoundOn(bool sd){
    SoundOn = sd;
}

void setSoundLoud(int n){
    SoundLoud = n;
}

void SoundSwitch(bool s){
    int temp;
    SoundOn = s;
    if(!s)
        temp = Mix_VolumeMusic(0);
    else
        temp = Mix_VolumeMusic(SoundLoud);
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
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
		gWindow = SDL_CreateWindow( "No Coriander!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
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

				//Initialize Audio;
                Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,AUDIO_S16, 2, 2048);

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
    gTextTexture.free();
    //for(int i = 0; i < TOTAL; i++)
    //    MovementSet[i].free();

    TTF_CloseFont( gFont );
	gFont = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
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
            if(x >= SCREEN_WIDTH * 7 / 8 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH * 7 / 8 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 10 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 10 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case HELP:
            if(x >= SCREEN_WIDTH * 7 / 8 - TextureSet[n].getWidth() / 2 + 90 && x <= SCREEN_WIDTH * 7 / 8 + TextureSet[n].getWidth() / 2 + 90 && \
            y >= SCREEN_HEIGHT / 10 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 10 + TextureSet[n].getHeight() / 2)
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
            if(x >= SCREEN_WIDTH / 2 - 100 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 100 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case RESTART:
            if(x >= SCREEN_WIDTH / 2 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case RESUME:
            if(x >= SCREEN_WIDTH / 2 + 100 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 + 100 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT / 2 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT / 2 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case SOUNDON:
            if(x >= SCREEN_WIDTH / 2 - 50 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH / 2 - 50 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT * 2 / 5 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT * 2 / 5 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case DRAGGER:
            return(!(distance(x, SCREEN_WIDTH / 2 + (SoundLoud - 64) * TextureSet[SOUNDBAR].getWidth() / 128, \
                y, SCREEN_HEIGHT * 3 / 5) > ( TextureSet[n].getWidth() / 2) * (TextureSet[n].getWidth() / 2)));
            break;
        case SOUNDBAR:
            return(x <= SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2 && x >= SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2 && \
                   y >= SCREEN_HEIGHT * 3 / 5 - TextureSet[SOUNDBAR].getHeight() / 2 && y <= SCREEN_HEIGHT * 3 / 5 + TextureSet[SOUNDBAR].getHeight() / 2);
            break;
        case ROLEFARMER:
            if(x >= SCREEN_WIDTH - 90 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH - 90 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT /4 - TextureSet[n].getHeight() / 2 && y <= SCREEN_HEIGHT /4 + TextureSet[n].getHeight() / 2)
                return true;
            else
                return false;
            break;
        case ROLEMOB:
            if(x >= SCREEN_WIDTH - 90 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH  - 90 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT /4 - TextureSet[n].getHeight() / 2 + 95 && y <= SCREEN_HEIGHT /4 + TextureSet[n].getHeight() / 2 + 95)
                return true;
            else
                return false;
            break;
        case ROLEFRANK:
            if(x >= SCREEN_WIDTH - 90 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH - 90 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT /4 - TextureSet[n].getHeight() / 2 + 190 && y <= SCREEN_HEIGHT /4 + TextureSet[n].getHeight() / 2 + 190)
                return true;
            else
                return false;
            break;
        case ROLEVAMP:
            if(x >= SCREEN_WIDTH - 90 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH - 90 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT /4 - TextureSet[n].getHeight() / 2 + 285 && y <= SCREEN_HEIGHT /4 + TextureSet[n].getHeight() / 2 + 285)
                return true;
            else
                return false;
            break;
        case ROLEBISHOP:
            if(x >= SCREEN_WIDTH - 90 - TextureSet[n].getWidth() / 2 && x <= SCREEN_WIDTH - 90 + TextureSet[n].getWidth() / 2 && \
            y >= SCREEN_HEIGHT /4 - TextureSet[n].getHeight() / 2 + 380 && y <= SCREEN_HEIGHT /4 + TextureSet[n].getHeight() / 2 + 380)
                return true;
            else
                return false;
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

void DrawGrayScreen(){
    SDL_SetRenderTarget(gRenderer, NULL);
    //SDL_SetTextureAlphaMod( gTexture, 120 );
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
}

void DrawMove(characterTag n, int x, int y, int f){     ///f-> frame (which frame, 0, 1, 2 or 3)
    SDL_Rect renderQuad = {x - MovementSet[n].getWidth() / 2, y - MovementSet[n].getHeight() / 2, \
    144 * MovementSet[n].getWidth() / MovementSet[n].getHeight() , 144};
    SDL_Rect clip = {f * MovementSet[n].getWidth() / 4, 0, MovementSet[n].getWidth() / 4, MovementSet[n].getHeight()};
    SDL_RenderCopy( gRenderer, MovementSet[n].gTexture, &clip, &renderQuad );
    std::cout << "Animation!" << std::endl;
}

void DrawAttack(Attack n, int x, int y, int f){   ///f-> frame (which frame, 0 or 1)
    SDL_Rect renderQuad = { x * 100 +100, y * 100 + 20, 144 * MovementSet[n].getWidth() / MovementSet[n].getHeight() , 144};
    SDL_Rect clip = {f * AttackSet[n].getWidth() / 4, 0, AttackSet[n].getWidth() / 4, AttackSet[n].getHeight()};
    SDL_RenderCopy( gRenderer, AttackSet[n].gTexture, &clip, &renderQuad );
}

void DrawRole(characterTag t, int x, int y){
    int n = t - 1 + ROLECORIANDER;
    SDL_Rect renderQuad = {x - 144 * TextureSet[n].getWidth() / TextureSet[n].getHeight() / 2, \
    y - 100, 144 * TextureSet[n].getWidth() / TextureSet[n].getHeight() , 144};
    SDL_RenderCopy( gRenderer, TextureSet[n].gTexture, NULL, &renderQuad );
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
                    renderQuad.x = SCREEN_WIDTH / 2 + (SoundLoud - 64) * TextureSet[SOUNDBAR].getWidth() / 128 - TextureSet[n].getWidth() / 2;
                    renderQuad.y =  SCREEN_HEIGHT * 3 / 5 - TextureSet[n].getHeight() / 2;
                    renderQuad.w = TextureSet[n].getWidth();
                    renderQuad.h = TextureSet[n].getHeight();
                    break;
                /*case SOUNDON:
                    renderQuad.x = SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2;
                    renderQuad.y = SCREEN_HEIGHT * 3 / 5 - TextureSet[SOUNDBAR].getHeight() / 2;
                    renderQuad.w = TextureSet[SOUNDBAR].getWidth() * SoundLoud / 100;
                    renderQuad.h = TextureSet[SOUNDBAR].getHeight();
                    break;*/
                case SOUNDSTATUS:
                    renderQuad.x = SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2;
                    renderQuad.y =  SCREEN_HEIGHT * 3 / 5 - TextureSet[n].getHeight() / 2;
                    renderQuad.w = TextureSet[SOUNDBAR].getWidth() * SoundLoud / 128;
                    renderQuad.h = TextureSet[n].getHeight();
                    break;
                default:
                    break;
            }
        }
    }
	SDL_RenderCopy( gRenderer, TextureSet[n].gTexture, NULL, &renderQuad );
}

void showMoney(int num, int x, int y){
    writeText.str("");
    writeText << std::setw(5) << "$" << num;
    gTextTexture.loadFromRenderedText(writeText.str().c_str(), textColor);
    SDL_Rect renderQuad = {x - gTextTexture.getWidth() / 2,y - gTextTexture.getHeight() / 2, gTextTexture.getWidth(), gTextTexture.getHeight()};
    SDL_RenderCopy( gRenderer, gTextTexture.gTexture, NULL, &renderQuad );
}

void setSound(SDL_Event *e){
    int x, y;
    bool holding = true;
    while(holding){
        while(SDL_PollEvent(e) != 0){
            if(e->type == SDL_MOUSEBUTTONUP)
                holding = false;
            if(e->type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&x, &y);
                if(x > SCREEN_WIDTH / 2 - TextureSet[SOUNDBAR].getWidth() / 2 && x < SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2){
                    SoundLoud = 128 * (x - SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2) / TextureSet[SOUNDBAR].getWidth();
                    SoundSwitch(SoundOn);
                    RenderSetting(SoundOn);
                    std::cout << SoundLoud << std::endl;
                }
            }
        }
    }

}

void clickSetSound(SDL_Event *e){
    int x, y;
    SDL_GetMouseState(&x, &y);
    SoundLoud = 128 * (x - SCREEN_WIDTH / 2 + TextureSet[SOUNDBAR].getWidth() / 2) / TextureSet[SOUNDBAR].getWidth();
    std::cout << SoundLoud << std::endl;
    RenderSetting(IsSound());
}

void playMusic(){
    std::cout << Mix_PlayMusic(gMusic, -1) << std::endl;
    printf("%s\n", Mix_GetError());
}

void pauseMusic(){
    Mix_PauseMusic();
    std::cout << "Music Paused!" << std::endl;
}

void resumeMusic(){
    Mix_ResumeMusic();
    std::cout << "Music Resumed!" << std::endl;
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
    if(!success)
        std::cout << path << "error" << std::endl;
	return success;
}
bool loadMusic(const char * path)
{
    bool success = true;
    gMusic = Mix_LoadMUS(path);
    if(gMusic == NULL){
        std::cout << path << "error" << std::endl;
        success = false;
    }
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
