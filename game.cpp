#include "game.h"
Grid _myGrids[5][7];

SDL_Event Game::event;

bool isRunning = true;

int GameProgress[6] = {1, 1, 0, 0, 0, 1};

int arrMoney[5] = {50, 100, 100, 150, 150};

int frameRate = 60;

uint32_t frameDelay = 1000 / frameRate;

void Game::gameInit(){
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++){
            _myGrids[i][j].set_gridHumans(0, NULL);
            _myGrids[i][j].set_gridVegetables(0, NULL);
        }
}

void Game::showRole(){
    static int frameCount = 0;
    frameCount++;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++){
            if(_myGrids[i][j].get_vegetableNum() > 0)
                if(_myGrids[i][j].get_humanNum() == 0 || _myGrids[i][j].get_gridVegetables()[0].get_data().coolRemain() > 300){
                DrawRole(_myGrids[i][j].get_gridVegetables()[0].get_tag(), 241 + j * 114, 144 + i * 108 );
            }
            for(int k = 0; k < _myGrids[i][j].get_humanNum(); k++){
                if(_myGrids[i][j].get_vegetableNum() > 0){
                    if(_myGrids[i][j].get_gridHumans()[k].get_data().coolRemain() < 150)
                        DrawAttack(_myGrids[i][j].get_gridHumans()[k].get_tag(), _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() + k * 5 - 20, \
                        160 + i * 108 + ( k - 2) * 5, 1);
                    else if(_myGrids[i][j].get_gridHumans()[k].get_data().coolRemain() < 300)
                        DrawAttack(_myGrids[i][j].get_gridHumans()[k].get_tag(), _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() + k * 5 - 20, \
                        160 + i * 108 + ( k - 2) * 5, 0);
                    else
                        DrawRole(_myGrids[i][j].get_gridHumans()[k].get_tag(), \
                        _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() + k * 5 - 20, 160 + i * 108 + ( k - 2) * 5);
                }
                else if( _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() <= 200)
                    DrawRole(_myGrids[i][j].get_gridHumans()[k].get_tag(), \
                    _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() + k * 5 - 20, 160 + i * 108 + ( k - 2) * 5);
                else
                    DrawMove(_myGrids[i][j].get_gridHumans()[k].get_tag(), _myGrids[i][j].get_gridHumans()[k].get_data().get_pos_x() + k * 5 - 20, \
                    160 + i * 108 + ( k - 2) * 5, ((frameCount + _myGrids[i][j].get_gridHumans()[k].get_tag()) / 10) % 4 );
            }
            if(_myGrids[i][j].get_vegetableNum() > 0 && _myGrids[i][j].get_humanNum() > 0 && _myGrids[i][j].get_gridVegetables()[0].get_data().coolRemain() <= 300){
                if(_myGrids[i][j].get_gridVegetables()[0].get_data().coolRemain() < 150)
                    DrawAttack(_myGrids[i][j].get_gridVegetables()[0].get_tag(), 241 + j * 114, 144 + i * 108, 1);
                else
                    DrawAttack(_myGrids[i][j].get_gridVegetables()[0].get_tag(), 241 + j * 114, 144 + i * 108 , 0);
            }
        }
    screenShow();
}

void SetProgress(int num, int Pro){
    GameProgress[num] = Pro;
}

int& GetProgress(){
    return *GameProgress;
}

int Game::characterMove(){
    int vegetableKill = 0;
    int totalSum = 0;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            totalSum += _myGrids[i][j].get_humanNum();
    if(totalSum == 0)
        return 0;
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
        for(int k = 0; k < _myGrids[i][0].get_humanNum(); k++){
            if(_myGrids[i][0].get_gridHumans()[k].get_data().get_pos_x() > 200 && _myGrids[i][0].get_vegetableNum() == 0)
                _myGrids[i][0].get_gridHumans()[k].get_data().c_move();
        }
        for(int j = 1; j < 7; j++){
            int n = _myGrids[i][j].get_humanNum();
            if(_myGrids[i][j].get_vegetableNum() == 0)
                for(int k = 0; k < n; k++){
                    _myGrids[i][j].get_gridHumans()[k].get_data().c_move();
            }
        }
    }

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
                nMove += _myGrids[i][j - 1].get_humanNum();
                Character* iMove = new Character[nMove];
                Character* iStay = new Character[nStay];
                int cMove = _myGrids[i][j - 1].get_humanNum(), cStay = 0;

                //std::cout << "Done" << std::endl;
                if(_myGrids[i][j - 1].get_humanNum() > 0)
                    for(int k = 0; k < _myGrids[i][j - 1].get_humanNum(); k++)
                        iMove[k] = _myGrids[i][j - 1].get_gridHumans()[k];

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
    delete [] toMove;
    for(int i = 0; i < 5; i++)
            for(int j = 0; j < 7; j++)
                vegetableKill += _myGrids[i][j].gridFight();
    return vegetableKill;
}

void Game::initialize(){
    if(!init() || !loadSrc() || !loadFonts()){
        printf("Initializer error!\n");
        close();
        return;
    }
}

void Game::startSurface(){
    RenderStartSurface();
    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_KEYUP){
                this->mainMenu();
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    close();
                    isRunning = false;
                    return;
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
                    close();
                    isRunning = false;
                    return;
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
                        RenderSetting(IsSound());
                    }
                }
                else if(!IsSound())
                    if(handleEvent(&event, SOUNDON)){
                        SoundSwitch(true);
                        RenderSetting(IsSound());
                    }
            }
            else if(event.type == SDL_QUIT){
                if(leaveAlert(&event)){
                    close();
                    isRunning = false;
                    return;
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
                    close();
                    isRunning = false;
                    return;
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
                    close();
                    isRunning = false;
                    return;
                }
                else{
                    RenderTutorial();
                }
            }
        }
    }
}

void Game::GameOn(int n){
    gameInit();
    int money = 0;
    bool GameWin = false, ending = false;
    char c;
    std::ifstream inputFile;
    inputFile.open("img/gameData.dat", std::ios::in);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 6; j++)
            inputFile.ignore(20, '\n');
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
    gameTimer gt;
    RenderGame(money, gt.getStartTime());
    screenShow();
    bool isMoved = false, framed = false;
    while(isRunning){
        if(money < 3200)
            money++;
        money += 80 * characterMove();
        gt.tick();
        isMoved = true;

        while(SDL_PollEvent(&event) != 0){
            if(isMoved)
                isMoved = false;
            else{
                if(money < 3200)
                    money++;
                money += 80 * characterMove();
                gt.tick();
            }

            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(handleEvent(&event, PAUSE))
                {
                    gt.pauseRec();
                    this -> GamePause(n);
                    gt.pauseUpdate();
                    RenderGame(money, gt.getStartTime());
                    showRole();
                }
                else if(handleEvent(&event, HELP))
                {
                    gt.pauseRec();
                    this -> Tutorial();
                    RenderGame(money, gt.getStartTime());
                    gt.pauseUpdate();
                    showRole();
                }
                for(int i = 0; i < 5; i++){
                    if(money >= arrMoney[i] * 5 && handleEvent(&event, (Picture)(ROLEFARMER + i))){
                        if(placeRole(i, &gt, money))
                            money -= arrMoney[i] * 4;
                    }
                }
            }
            else if(event.type == SDL_QUIT){
                gt.pauseRec();
                if(leaveAlert(&event)){
                    close();
                    isRunning = false;
                    return;
                }
                gt.pauseUpdate();
            }
            int total_vegetableNum = 0;
            for(int i = 0; i < 5; i++)
                for(int j = 0;j< 7; j++)
                    total_vegetableNum += _myGrids[i][j].get_vegetableNum();
            if(total_vegetableNum==0 && !gt.timeOver()){
                isRunning = false;
                GameWin = true;
            }
            else if(gt.timeOver()){
                isRunning = false;
                GameWin = false;
            }

            if(gt.tickLeft() > 0)
                SDL_Delay(gt.tickLeft());
            RenderGame(money, gt.getStartTime());
            showRole();
            framed = true;
        }
        int total_vegetableNum = 0;
        for(int i = 0; i < 5; i++)
            for(int j = 0;j< 7; j++)
                total_vegetableNum += _myGrids[i][j].get_vegetableNum();
        if(total_vegetableNum==0 && !gt.timeOver()){
            isRunning = false;
            GameWin = true;
        }
        else if(gt.timeOver()){
                isRunning = false;
                GameWin = false;
        }
        if(framed)
            framed = false;
        else{
            if(gt.tickLeft() > 0)
                SDL_Delay(gt.tickLeft());
            RenderGame(money, gt.getStartTime());
            showRole();
        }
    }
    if(ending)
        return;
    isRunning = true;
    this -> GameResult(GameWin, n);
    return;
}

bool Game::placeRole(int i,gameTimer *gt, int &money){
    bool isMoved = false, framed = false;
    bool isPlacing = true, GameWin = false;;
    RenderGame(i, money, gt->getStartTime());
    showRole();
    while(isPlacing){
        if(money < 3200)
            money++;
        money += 80 * characterMove();
        isMoved = true;

        while(SDL_PollEvent(&event) != 0){
            if(money < 4000)
                money++;
            if(isMoved)
                isMoved = false;
            else{
                money += 80 * characterMove();
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                int x, y, gridY;
                SDL_GetMouseState(&x, &y);
                gridY = (y - 95) / 108;
                y = gridY * 108 + 144;
                isPlacing = false;
                if(gridY < 0 || gridY >= 5 || x > 980 || x < 500)
                    return false;
                else{
                    switch(i){
                        case 0:{
                            Farmer farmer(930, y);
                            _myGrids[gridY][6].set_gridHumans(1, &farmer);
                            break;
                        }
                        case 1:{
                            Frankenstein frank(930, y);
                            _myGrids[gridY][6].set_gridHumans(1, &frank);
                            break;
                        }
                        case 2:{
                            Mob mob(930, y);
                            _myGrids[gridY][6].set_gridHumans(1, &mob);
                            break;
                        }
                        case 3:{
                            Vampire vampire(930, y);
                            _myGrids[gridY][6].set_gridHumans(1, &vampire);
                            break;
                        }
                        case 4:{
                            Bishop bishop(930, y);
                            _myGrids[gridY][6].set_gridHumans(1, &bishop);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else if(event.type == SDL_QUIT){
                gt->pauseRec();
                if(leaveAlert(&event)){
                    close();
                    isRunning = false;
                    return 0;
                }
                else{
                    RenderPause();
                }
                gt->pauseUpdate();
            }
            int total_vegetableNum = 0;
            for(int i = 0; i < 5; i++)
                for(int j = 0;j< 7; j++)
                    total_vegetableNum += _myGrids[i][j].get_vegetableNum();
            if(total_vegetableNum==0 && !gt->timeOver()){
                isRunning = false;
                GameWin = true;
            }
            else if(gt->timeOver()){
                isRunning = false;
                GameWin = false;
            }
            if(gt->tickLeft() > 0)
                SDL_Delay(gt->tickLeft());
            RenderGame(i, money, gt->getStartTime());
            showRole();
            if(gt->timeOver()){
                isRunning = false;
                return false;
            }
            if(!isRunning)
                break;
        }
        int total_vegetableNum = 0;
        for(int i = 0; i < 5; i++)
            for(int j = 0;j< 7; j++)
                total_vegetableNum += _myGrids[i][j].get_vegetableNum();
        if(total_vegetableNum==0 && !gt->timeOver()){
            isRunning = false;
            GameWin = true;
        }
        else if(gt->timeOver()){
                isRunning = false;
                GameWin = false;
        }
        if(framed)
            framed = false;
        else{
            if(gt->tickLeft() > 0)
                SDL_Delay(gt->tickLeft());
            RenderGame(i, money, gt->getStartTime());
            showRole();
        }
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
                    close();
                    isRunning = false;
                    return;
                }
                else{
                    RenderPause();
                }
            }
        }
    }
}

void Game::GameResult(bool GameWin,int n){
    RenderResult(GameWin);
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
                    close();
                    isRunning = false;
                    return;
                }
                else{
                    RenderResult(GameWin);
                }
            }
        }
    }
}
