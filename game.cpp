#include "game.h"
Grid _myGrids[5][7];

SDL_Event Game::event;

bool isRunning = true;

int GameProgress[6] = {1, 1, 0, 0, 0, 1};

int arrMoney[5] = {50, 100, 100, 150, 150};

int frameRate = 60;

uint32_t frameDelay = 1000 / frameRate;

void Game::endGame(){
    isRunning = false;
}

void Game::DrawVegetable(){
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            if(_myGrids[i][j].get_vegetableNum())
                DrawRole(_myGrids[i][j].get_gridVegetables()[0].get_tag(), 241 + j * 114, 144 + i * 108 );
}

void Game::DrawHuman(){;}/*{
    static int frameCount = 0;
    frameCount++;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++)
                if(i > 0){
    std::cout << "In";
                    DrawMove(_myGrids[i][j].get_gridHumans()[k].get_tag(), _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x(), \
                        _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_y(), (frameCount + _myGrids[i][j].get_gridHumans()[k].get_tag()) / 4 % 4);

                }
                else{
                    DrawRole(_myGrids[i][j].get_gridHumans()[k].get_tag(), _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x(), \
                        _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_y());}
}*/

void SetProgress(int num, int Pro){
    GameProgress[num] = Pro;
}

int& GetProgress(){
    return *GameProgress;
}

void Game::characterMove(){
    int totalSum = 0;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            totalSum += _myGrids[i][j].get_humanNum();
    if(totalSum == 0)
        return;
    static int frameCount = 0;
    frameCount++;
    bool*** toMove = new bool**[5];
    for(int i=0;i<5;i++)
        toMove[i] = new bool*[7];
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++){
            toMove[i][j] = new bool[20];
                for(int k = 0; k < 20; k++)
                    toMove[i][j][k] = false;
        }
    for(int i = 0; i < 5; i++){
        for(int j = 1; j < 7; j++){
            int n = _myGrids[i][j].get_humanNum();
            std::cout << n;
            for(int k = 0; k < n; k++){
                _myGrids[i][j].get_gridHumans()[k].get_data().c_move();
            }
        }
            std::cout << std::endl;}

    for(int i = 0;i < 5; i++){
        for(int j=6;j>=1;j--){
            for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++)
                if(_myGrids[i][j].get_humanNum()!=0 && _myGrids[i][j].get_vegetableNum()==0)
                    if((_myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() - 241) / 114 != j){
                        toMove[i][j][k] = true;
                    }
        }
    }
    for(int i=0;i<5;i++)
        for(int j=1; j < 7;j++)
            if(_myGrids[i][j].get_humanNum() > 0){
                int nStay = 0, nMove = 0;
                for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++){
                    if(toMove[i][j][k]){
                        nMove++;
                    }
                    else{
                        nStay++;
                    }
                }
                int jNum = _myGrids[i][j - 1].get_humanNum();
                if(jNum > 0){
                    Character* iMove = new Character[jNum + nMove];
                    Character* iStay = new Character[nStay];

                    int cMove = 0, cStay = 0;
                    for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++)
                        iMove[k] = _myGrids[i][j - 1].get_gridHumans()[k];
                    for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++){
                        if(toMove[i][j][k]){
                            iMove[_myGrids[i][j - 1].get_humanNum() + cMove] = _myGrids[i][j].get_gridHumans()[k];
                            cMove++;
                        }
                        else{
                            iStay[cStay] = _myGrids[i][j].get_gridHumans()[k];
                            cStay++;
                        }
                    }

                    _myGrids[i][j].set_gridHumans(0,NULL);
                    _myGrids[i][j].set_gridHumans(nStay, iStay);
                    _myGrids[i][j-1].set_gridHumans(0,NULL);
                    _myGrids[i][j-1].set_gridHumans(jNum + nMove, iMove);
                    delete [] iStay;
                    delete [] iMove;
                }
                else{
                    int cMove = 0, cStay = 0;
                    Character* iMove = new Character[nMove];
                    Character* iStay = new Character[nStay];
                    for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++){
                        if(toMove[i][j][k]){
                            iMove[cMove] = _myGrids[i][j].get_gridHumans()[k];
                            cMove++;
                        }
                        else{
                            iStay[cStay] = _myGrids[i][j].get_gridHumans()[k];
                            cStay++;
                        }
                    }

                    _myGrids[i][j].set_gridHumans(0,NULL);
                    _myGrids[i][j].set_gridHumans(nStay, iStay);
                    _myGrids[i][j-1].set_gridHumans(0,NULL);
                    _myGrids[i][j-1].set_gridHumans(nMove, iMove);
                    delete [] iStay;
                    delete [] iMove;
                }
            }
    delete [] toMove;
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
            if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_KEYUP){
                this->mainMenu();
                RenderStartSurface();
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                }
                else
                    RenderStartSurface();
            }
        }
    }
}

void Game::mainMenu(){
    RenderMenu();
    SDL_Delay(2000);
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
                if(leaveAlert(&event)){
                    endGame();
                }else
                    RenderMenu();
            }
        }
    }
}
void Game::Settings(){
    RenderSetting(IsSound());
    SDL_Delay(2000);
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {

                if(handleEvent(&event, DRAGGER)){
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
                if(leaveAlert(&event)){
                    endGame();
                }
                else{
                    RenderSetting(IsSound());
                }
            }
        }
    }
}

void Game::Tutorial(){
    RenderTutorial();
    SDL_Delay(2000);
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, BACKBUTTON)){
                    return;
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                }
                else{
                    RenderTutorial();
                }
            }
        }
    }
}

void Game::Select(){
    RenderSelect(GameProgress);
    SDL_Delay(2000);
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, BACKBUTTON)){
                    this -> mainMenu();
                }
                for(int i = 0; i < 5; i++){
                    if(GameProgress[i] == 1){
                        if(handleEvent(&event, (Picture)(LEVEL1 + i))){
                            this -> GameOn(i);
                            RenderSelect(GameProgress);
                        }
                    }
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                }
                else{
                    RenderTutorial();
                }
            }
        }
    }
}

void Game::GameOn(int n){
    int money = 0;
    bool isPlacing = false, GameWin = false, ending = false;
    uint32_t startTime, frameTick, timeLeft, pauseTime;
    RenderGame(money);
    startTime = SDL_GetTicks();
    char c;
    std::ifstream inputFile;
    inputFile.open("img/gameData.dat", std::ios::in);
    for(int i=0;i<5;i++){
        for(int j=0;j<7;j++){
            inputFile.get(c);
            switch(c){
                case '*':
                    break;
                case 'G':{
                    Garlic garlic(i,j);
                    _myGrids[i][j].set_gridVegetables(1, &garlic);
                    break;
                }
                case 'C':{
                    Coriander coriander(i,j);
                    _myGrids[i][j].set_gridVegetables(1, &coriander);
                    break;
                }
                case 'B':{
                    Beans beans(i,j);
                    _myGrids[i][j].set_gridVegetables(1, &beans);
                    break;
                }
                case 'P':{
                    Piment piment(i,j);
                    _myGrids[i][j].set_gridVegetables(1, &piment);
                    break;
                }
                case 'S':{
                    Spinach spinach(i,j);
                    _myGrids[i][j].set_gridVegetables(1, &spinach);
                    break;
                }
                default:
                    break;
            }
        }
        inputFile.ignore(20, '\n');
    }
    bool isMoved = false;
    while(isRunning){
        if(money < 3200)
            money++;
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 7; j++){
                _myGrids[i][j].gridFight();
            }
        characterMove();
        RenderGame(money);
        DrawVegetable();
        DrawHuman();
        screenShow();
        isMoved = true;
        while(SDL_PollEvent(&event) != 0){
            if(isMoved)
                isMoved = false;
            else{
                for(int i = 0; i < 5; i++)
                    for(int j = 0; j < 7; j++){
                        _myGrids[i][j].gridFight();
                    }
                RenderGame(money);
                characterMove();
                DrawVegetable();
                DrawHuman();
                screenShow();
            }
            if(money < 4000)
                money++;
            frameTick = SDL_GetTicks();
            //TEST
            if(event.type == SDL_KEYDOWN)
            {
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

            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, PAUSE))
                {
                    pauseTime = SDL_GetTicks();
                    this -> GamePause(n);
                    startTime += (SDL_GetTicks() - pauseTime);
                    RenderGame(money);
                    DrawVegetable();
                    DrawHuman();
                    screenShow();
                }
                else if(handleEvent(&event, HELP))
                {
                    this -> Tutorial();
                    RenderGame(money);
                    DrawVegetable();
                    DrawHuman();
                    screenShow();
                }
                for(int i = 0; i < 5; i++){
                    if(money >= arrMoney[i] * 5 && handleEvent(&event, (Picture)(ROLEFARMER + i))){
                        if(placeRole(i, startTime, money))
                            money -= arrMoney[i] * 5;
                    }
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                    ending = true;
                }
            }
            int total_vegetableNum = 0;
            for(int i = 0; i < 5; i++)
                for(int j = 0;j< 7; j++)
                    total_vegetableNum += _myGrids[i][j].get_vegetableNum();
            if(total_vegetableNum==0 && SDL_GetTicks() - startTime <= 1000*120){
                isRunning = false;
                GameWin = true;
            }
            timeLeft = SDL_GetTicks() - frameTick;
            if(timeLeft < frameDelay)
                SDL_Delay(frameDelay - timeLeft);
            RenderGame(money);
            DrawVegetable();
            DrawHuman();
            screenShow();
        }
        if(SDL_GetTicks() - startTime >= 1000*120){
                isRunning = false;
                GameWin = false;
        }
        RenderGame(money);
        DrawVegetable();
        DrawHuman();
        screenShow();
    }
    if(ending)
        return;
    isRunning = true;
    this -> GameResult(GameWin, n);
    return;
}

bool Game::placeRole(int i,uint32_t timer, int &money){
    bool isMoved = false;
    int frametime;
    bool isPlacing = true;
    RenderGame(i, money);
    DrawVegetable();
    DrawHuman();
    while(isPlacing){
        if(money < 3200)
            money++;
        characterMove();
        for(int k = 0; k < 5; k++)
            for(int j = 0; j < 7; j++)
                _myGrids[k][j].gridFight();
        isMoved = true;

        while(SDL_PollEvent(&event) != 0){
            if(money < 4000)
                money++;
            if(isMoved)
                isMoved = false;
            else{
                for(int k = 0; k < 5; k++)
                    for(int j = 0; j < 7; j++)
                        _myGrids[k][j].gridFight();
                characterMove();
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                int x, y, gridY;
                SDL_GetMouseState(&x, &y);
                x = ((x - 184) / 114) * 114 + 241;
                gridY = (y - 95) / 108;
                y = gridY * 108 + 144;
                isPlacing = false;
                if(gridY < 0 || gridY >= 5)
                    return false;
                else{
                    switch(i){
                        case 0:{
                            Farmer farmer(x, y);
                            _myGrids[gridY][6].set_gridHumans(1, &farmer);
                            break;
                        }
                        case 1:{
                            Frankenstein frank(x, y);
                            _myGrids[gridY][6].set_gridHumans(1, &frank);
                            break;
                        }
                        case 2:{
                            Mob mob(x, y);
                            _myGrids[gridY][6].set_gridHumans(1, &mob);
                            break;
                        }
                        case 3:{
                            Vampire vampire(x, y);
                            _myGrids[gridY][6].set_gridHumans(1, &vampire);
                            break;
                        }
                        case 4:{
                            Bishop bishop(x, y);
                            _myGrids[gridY][6].set_gridHumans(1, &bishop);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            RenderGame(i, money);
            DrawVegetable();
            DrawHuman();
            screenShow();
            if(SDL_GetTicks() - timer > 1000 * 120){
                isRunning = false;
                return false;
            }
            if(!isRunning)
                break;
            screenShow();
        }
        RenderGame(i,money);
        DrawVegetable();
        DrawHuman();
        screenShow();
    }
    return true;
}

void Game::GamePause(int n){
    RenderPause();
    SDL_Delay(1000);
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP){
                if(handleEvent(&event, LEAVE)){
                    this -> Select();
                }
                else if(handleEvent(&event, RESTART)){
                    this ->GameOn(n);
                }
                else if(handleEvent(&event, RESUME)){
                    return;
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                }
                else{
                    RenderPause();
                }
            }
        }
    }
}

void Game::GameResult(bool GameWin,int n){
    RenderResult();
    SDL_Delay(2000);
    if(GameProgress[n + 1] == 0)
        if(GameWin)
            GameProgress[n + 1] = 1;
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP){
                if(handleEvent(&event, BACKTOSELECTOR)){
                    return;
                }
                else if(handleEvent(&event, AGAIN)){
                    this -> GameOn(n);
                }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    endGame();
                }
                else{
                    RenderResult();
                }
            }
        }
    }
}
