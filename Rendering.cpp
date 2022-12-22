#include "Rendering.h"
void RenderStartSurface(){
    screenRefresh();
    Draw(WELCOME, 0, 0, 0, 0);
    screenShow();
}

void RenderMenu(){
    screenRefresh();
    Draw(MENU, 0, 0, 0, 0);
    Draw(STARTPLAYINGBUTTON, SCREEN_WIDTH / 2 - 20 - 174, SCREEN_HEIGHT / 2, -1, -1);
    Draw(SETTINGBUTTON, SCREEN_WIDTH / 2+ 20 + 174, SCREEN_HEIGHT / 2 - 10 - 120, -1, -1);
    Draw(TUTORIALBUTTON, SCREEN_WIDTH / 2+ 20 + 174, SCREEN_HEIGHT / 2 + 10 + 120, -1, -1);
    screenShow();
}

void RenderSelect(int n[]){
    screenRefresh();
    Draw(SELECTOR, 0, 0, 0, 0);
    for(int i = 0; i < 5; i++){
        if(n[i] == 1)
            Draw((Picture)(LEVEL1 + i), SCREEN_WIDTH / 2 + (i - 2) * 200, SCREEN_HEIGHT / 2, -1, -1);
        else
            Draw((Picture)(LOCKED), SCREEN_WIDTH / 2 + (i - 2) * 200, SCREEN_HEIGHT / 2, -1, -1);
    }
    Draw(BACKBUTTON, SCREEN_WIDTH / 2, SCREEN_HEIGHT *4 / 5, -1, -1);
    screenShow();
}

void RenderSetting(bool Sound){
    screenRefresh();
    Draw(SETTING, 0, 0, 0, 0);
    Draw(( IsSound() ? SOUNDON : SOUNDOFF), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5, -1, -1);
    Draw(SOUNDBAR, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 5, -1, -1);
    if(Sound)
        Draw(SOUNDSTATUS, 0, 0, -2, -2);
    Draw(DRAGGER, 0, 0, -2, -2);
    Draw(BACKBUTTON, SCREEN_WIDTH / 2, SCREEN_HEIGHT *4 / 5, -1, -1);
    screenShow();
}

int cost[5] = {50, 100, 100, 150, 150};

void RenderGame(int money){
    screenRefresh();
    Draw(GAMEON, 0, 0, 0, 0);
    Draw(PAUSE, SCREEN_WIDTH * 7/8, SCREEN_HEIGHT / 10, -1, -1);
    Draw(HELP, SCREEN_WIDTH * 7/8 + 90, SCREEN_HEIGHT / 10, -1, -1);
    for(int i = 0; i < 5; i++)
        Draw( money / 5 >= cost[i] ? (Picture)(ROLEFARMER + i) : (Picture)(ROLEFARMERN + i), SCREEN_WIDTH -90, SCREEN_HEIGHT /4 + i* 95, -1, -1);
    showMoney(money / 5, SCREEN_WIDTH -90, SCREEN_HEIGHT / 4 + 5 * 95);
}

void RenderGame(int n, int money){
    screenRefresh();
    Draw(GAMEON, 0, 0, 0, 0);
    Draw(PAUSE, SCREEN_WIDTH * 7/8, SCREEN_HEIGHT / 10, -1, -1);
    Draw(HELP, SCREEN_WIDTH * 7/8 + 90, SCREEN_HEIGHT / 10, -1, -1);
    for(int i = 0; i < 5; i++)
        Draw( money / 5 >= cost[i] ? (Picture)(ROLEFARMER + i): (Picture)(ROLEFARMERN + i), SCREEN_WIDTH -90, SCREEN_HEIGHT /4 + i* 95, -1, -1);
    int x, y;
    SDL_GetMouseState(&x, &y);
    showMoney(money / 5, SCREEN_WIDTH -90, SCREEN_HEIGHT / 4 + 5 * 95);
    Draw((Picture)(PLACEFARMER + n), x - 50, y - 144 , 100, 144);
}

void RenderResult(){
    screenRefresh();
    Draw(SAMPLE, 0, 0, 0, 0);
    Draw(AGAIN, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, -1, -1);
    Draw(BACKTOSELECTOR, SCREEN_WIDTH / 2 + 136, SCREEN_HEIGHT / 2, -1, -1);
    screenShow();
}

void RenderPause(){
    Draw(PAUSELIST, 0, 0, 0, 0);
    for(int i = 0; i < 3; i++){
        Draw((Picture)(LEAVE + i), SCREEN_WIDTH / 2 + (i - 1) * 100, SCREEN_HEIGHT / 2, -1, -1);
    }
    screenShow();
}

void RenderTutorial(){
    screenRefresh();
    Draw(TUTORIAL, 0, 0, 0, 0);
    Draw(BACKBUTTON, SCREEN_WIDTH / 2, SCREEN_HEIGHT *4 / 5, -1, -1);
    screenShow();
}

void showRole(){
}

void ShowAlert(){
    Draw(ALERT, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    screenShow();
}
