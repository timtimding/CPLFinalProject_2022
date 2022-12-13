#include "game.h"

SDL_Event Game::event;

bool isRunning = true;

int GameProgress[6] = {1, 1, 0, 0, 0, 1};

void SetProgress(int num, int Pro){
    GameProgress[num] = Pro;
}

void Game::initialize(){
    if(!init() || !loadSrc() || !loadFonts()){
        printf("Initializer error!\n");
        close();
    }
}

void Game::startSurface(){
    RenderStartSurface();
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_KEYUP)
            {
                this->mainMenu();
                RenderStartSurface();
            }
            else if(event.type == SDL_QUIT)
            {
                std::cout << "Time to quit" <<std::endl;
                if(leaveAlert(&event))
                    close();
                else
                    RenderStartSurface();
            }
        }
    }
}

void Game::mainMenu(){
    RenderMenu();
    std::cout << "Menu is here!" << std::endl;
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_BUTTON_LEFT)
            {
                if(handleEvent(&event, TUTORIALBUTTON))
                {
                    this->Tutorial();
                    RenderMenu();
                }
                else if(handleEvent(&event, SETTINGBUTTON))
                {
                    this->Settings();
                    RenderMenu();
                }
                else if(handleEvent(&event, STARTPLAYINGBUTTON))
                {
                    this->Select();
                    RenderMenu();
                }
            }
            else if(event.key.keysym.sym == SDLK_ESCAPE)
                return;
            else if(event.type == SDL_QUIT)
            {
                std::cout << "Time to quit" <<std::endl;
                if(leaveAlert(&event))
                    close();
                else
                    RenderMenu();
            }
        }
    }
}
void Game::Settings(){
    RenderSetting(IsSound());
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, DRAGGER)){
                    std::cout << "Pressed!" << std::endl;
                    setSound(&event);
                }
                else if(handleEvent(&event, SOUNDBAR)){
                    clickSetSound(&event);
                }
                else if(handleEvent(&event, BACKBUTTON)){
                    return;
                }
                else if(IsSound()){
                    if(handleEvent(&event, SOUNDON)){
                        SoundSwitch(false);
                        RenderSetting(false);
                    }
                }
                else if(!IsSound())
                    if(handleEvent(&event, SOUNDON)){
                        SoundSwitch(true);
                        RenderSetting(true);
                    }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event))
                {
                    close();
                }
                else
                {
                    RenderSetting(IsSound());
                }
            }
        }
    }
}

void Game::Tutorial(){
    std::cout << "Enter Tutorial" << std::endl;
    RenderTutorial();
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, BACKBUTTON)){
                    return;
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event))
                {
                    close();
                }
                else
                {
                    RenderTutorial();
                }
            }
        }
    }
}

void Game::Select(){
    RenderSelect(GameProgress);
    std::cout << "Enter Selector" << std::endl;
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, BACKBUTTON)){
                    return;
                }
                for(int i = 0; i < 5; i++){
                    if(GameProgress[i] == 1)
                        if(handleEvent(&event, (Picture)(LEVEL1 + i))){
                            std::cout << "select " << i << std::endl;
                            this -> GameOn(i);
                            RenderSelect(GameProgress);
                        }
                }
            }
            else if(event.type == SDL_QUIT)
            {
                if(leaveAlert(&event))
                {
                    close();
                }
                else
                {
                    RenderTutorial();
                }
            }
        }
    }
}

void Game::GameOn(int n){
    bool GameWin = false;
    RenderGame();
    std::cout << "GameStart!" << std::endl;
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            //TEST
            if(event.type == SDL_KEYDOWN){
                std::cout << "Pressed" << std::endl;
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    GameWin = true;
                    isRunning = false;
                    break;
                }
                else if(event.key.keysym.sym == SDLK_q)
                {
                    GameWin = false;
                    isRunning = false;
                    break;
                }
            }//TEST
            if(event.type == SDL_MOUSEBUTTONUP){
                if(handleEvent(&event, PAUSE))
                {
                    this -> GamePause(n);
                    RenderGame();
                }
                else if(handleEvent(&event, HELP))
                {
                    this ->Tutorial();
                    RenderGame();
                }
                //Add controller here;
            }
            else if(event.type == SDL_QUIT)
            {
                if(leaveAlert(&event))
                {
                    close();
                }
                else
                {
                    RenderGame();
                }
            }
        }
    }
    isRunning = true;
    std::cout << "Game Ends!" << std::endl;
    this -> GameResult(GameWin, n);
    return;
}

void Game::GamePause(int n){
    RenderPause();
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP){
                if(handleEvent(&event, LEAVE))
                {
                    this -> Select();
                }
                else if(handleEvent(&event, RESTART))
                {
                    this ->GameOn(n);
                }
                else if(handleEvent(&event, RESUME))
                {
                    return;
                }
            }
            else if(event.type == SDL_QUIT)
            {
                if(leaveAlert(&event))
                {
                    close();
                }
                else
                {
                    RenderGame();
                }
            }
        }
    }
}

void Game::GameResult(bool GameWin,int n){
    RenderResult();
    if(GameProgress[n + 1] == 0)
        if(GameWin)
            GameProgress[n + 1] = 1;
    while(isRunning){
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_MOUSEBUTTONUP){
                if(handleEvent(&event, BACKTOSELECTOR))
                {
                    return;
                }
                else if(handleEvent(&event, AGAIN))
                {
                    this -> GameOn(n);
                }
            }
        }
    }
}

/*
void game(){
    while( !quit )
    {
        while(SDL_PollEvent(&event) != 0){

                        /*else if(e.key.keysym.sym == SDLK_ESCAPE){
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            TextureSet[Welcome].render(0, 0);
                            enter = false;
                        }
            }else{
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if(e.key.keysym.sym == SDLK_ESCAPE){
                games = false;
                screenRefresh();
                Draw(MENU, 0, 0);
                Draw(BUTTON, -1, -1);
            }
            else
            {
                screenRefresh();
                Draw(SAMPLE, 0, 0);
            }
        }
    }
    screenShow();
}
*/
