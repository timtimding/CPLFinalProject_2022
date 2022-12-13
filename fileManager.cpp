#include "fileManager.h"

bool loadSrc(){
    bool success = true;
    std::ifstream dataIn;
    dataIn.open("img/PictureList.txt");
    int Progress[5] = {1, 0, 0, 0, 0};
    for(int i = 0; i < 5; i++){
        SetProgress(i, Progress[i]);
    }
    char name[40];
    Picture n;
    while(!dataIn.eof()){
        dataIn >> name >> n;
        loadMedia(&name, n);
    }
    dataIn.close();
    if(!loadMedia("img/Welcome.png", WELCOME))
        success = false;
    if(!loadMedia("img/really.png", ALERT))
        success = false;
    if(!loadMedia("img/menu.png", MENU))
        success = false;
    if(!loadMedia("img/StartPlayingButton.png", STARTPLAYINGBUTTON))
        success = false;
    if(!loadMedia("img/SettingButton.png", SETTINGBUTTON))
        success = false;
    if(!loadMedia("img/TutorialButton.png", TUTORIALBUTTON))
        success = false;
    if(!loadMedia("img/BackButton.png", BACKBUTTON))
        success = false;
    if(!loadMedia("img/Setting.png", SETTING))
        success = false;
    if(!loadMedia("img/Dragger.png", DRAGGER))
        success = false;
    if(!loadMedia("img/SoundBar.png", SOUNDBAR))
        success = false;
    if(!loadMedia("img/SoundStatus.png", SOUNDSTATUS))
        success = false;
    if(!loadMedia("img/SoundOn.png", SOUNDON))
        success = false;
    if(!loadMedia("img/SoundOff.png", SOUNDOFF))
        success = false;
    if(!loadMedia("img/Tutorial.png", TUTORIAL))
        success = false;
    if(!loadMedia("img/Selector.png", SELECTOR))
        success = false;
    if(!loadMedia("img/Level10.png", LEVEL1))
        success = false;
    if(!loadMedia("img/Level20.png", LEVEL2))
        success = false;
    if(!loadMedia("img/Level30.png", LEVEL3))
        success = false;
    if(!loadMedia("img/Level40.png", LEVEL4))
        success = false;
    if(!loadMedia("img/Level50.png", LEVEL5))
        success = false;
    if(!loadMedia("img/Locked.png", LOCKED))
        success = false;
    if(!loadMedia("img/GameOn.png", GAMEON))
        success = false;
    if(!loadMedia("img/Pause.png", PAUSE))
        success = false;
    if(!loadMedia("img/Help.png", HELP))
        success = false;
    if(!loadMedia("img/PauseList.png", PAUSELIST))
        success = false;
    if(!loadMedia("img/Exit.png", LEAVE))
        success = false;
    if(!loadMedia("img/Restart.png", RESTART))
        success = false;
    if(!loadMedia("img/Resume.png", RESUME))
        success = false;
    if(!loadMedia("img/sample.bmp", GAMERESULT))
        success = false;
    if(!loadMedia("img/BackToSelector.png", BACKTOSELECTOR))
        success = false;
    if(!loadMedia("img/PlayAgain.png", AGAIN))
        success = false;
    if(!loadMedia("img/sample.bmp", SAMPLE))
        success = false;
    if(!loadMedia("img/Corianderbg.png", CORIANDER))
        success = false;
    if(!success)
        std::cout << "Error in loading picture!" << std::endl;
    return success;
}


bool loadFonts(){
    if(!loadFont("img/Teko-Regular.ttf", 28)){
        std::cout << "Error in loading Fonts!" <<  SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

