#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include "SDL_total.h"
#include "Rendering.h"
#include <string>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Character.h"

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
    ROLECORIANDER, ROLEGARLIC, ROLEPIMENT, ROLESPINACH, ROLEBEANS,
    PLACEFARMER, PLACEMOB, PLACEFRANK, PLACEVAMP, PLACEBISHOP, ///placing role & standing
    ROLEFARMER, ROLEMOB, ROLEFRANK, ROLEVAMP, ROLEBISHOP,
    ROLEFARMERN, ROLEMOBN, ROLEFRANKN, ROLEPVAMPN, ROLEBISHOPN,
    SAMPLE
};
enum Movement{
FARMERMOVE, MOBMOVE, FRANKRMOVE, VAMPMOVE, BISHOPMOVE,
MOVEMENTTOTAL
};
enum Attack{
    FARMERATTACK, MOBATTACK, FRANKATTACK, VAMPATTACK, BISHOPATTACK,
    CORIANDERATTACK, GARLICATTACK, PIMENTATTACK, SPINACHATTACK, BEANSATTACK,
    ATTACKTOTAL
};

int getSound();

void setSoundOn(bool);

void setSoundLoud(int);

bool init();

void close();

bool leaveAlert(SDL_Event *);

void screenShow();

void screenRefresh();

void DrawGrayScreen();

void Draw(Picture, int, int, int, int);

void DrawMove(characterTag, int, int, int);

void DrawRole(characterTag, int, int);

void DrawAttack(Attack, int, int, int);

void showMoney(int, int, int);

void setSound(SDL_Event *);

void clickSetSound(SDL_Event *);

bool IsSound();

void SoundSwitch(bool);

bool loadMedia(std::string, Picture);

bool loadMusic(const char *path);

bool loadFont(const char *, int);

void playMusic();

void pauseMusic();

void resumeMusic();

bool handleEvent(SDL_Event *, Picture);

class lTexture{
friend void Draw(Picture, int, int, int, int);

friend void DrawMove(characterTag, int, int, int);

friend void DrawAttack(Attack, int, int, int);

friend void showMoney(int, int, int);

friend void DrawRole(characterTag, int, int);

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


#endif // TEXTURE_H
