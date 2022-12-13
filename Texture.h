#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include "SDL_total.h"
#include "Rendering.h"
#include <string>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum Picture{
    WELCOME, ALERT,
    MENU, STARTPLAYINGBUTTON, SETTINGBUTTON, TUTORIALBUTTON, BACKBUTTON,
    SETTING, DRAGGER, SOUNDBAR, SOUNDSTATUS, SOUNDON, SOUNDOFF,
    TUTORIAL,
    SELECTOR, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LOCKED,
    GAMEON, PAUSE, HELP, PAUSELIST, LEAVE, RESTART, RESUME,
    GAMERESULT, BACKTOSELECTOR, AGAIN,
    CORIANDER,
    SAMPLE
};

bool init();

void close();

bool leaveAlert(SDL_Event *);

void screenShow();

void screenRefresh();

void drawGrayScreen();

void Draw(Picture, int, int, int, int);

void setSound(SDL_Event *);

void clickSetSound(SDL_Event *);

bool IsSound();

void SoundSwitch(bool);

bool loadMedia(std::string, Picture);

bool loadFont(const char *, int);

class lTexture{
friend void Draw(Picture, int, int, int, int);
friend void RenderSetting();
public:
    lTexture();

    ~lTexture();

    bool loadFromFile(std::string path);

    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    void free();

    int getWidth();

    int getHeight();

private:

    SDL_Texture * gTexture;
    int width;
    int height;

};

bool handleEvent(SDL_Event *, Picture);

#endif // TEXTURE_H
