#ifndef GAME_H
#define GAME_H

#include "SDL_total.h"
#include <iostream>
#include <stdio.h>
#include "media.h"
#include "Texture.h"
#include "Rendering.h"
#include "fileManager.h"

void SetProgress(int, int);

class Game{
    public:
        static SDL_Event event;

        void initialize();      //finished

        void startSurface();    //

        void mainMenu();

        void Tutorial();

        void Settings();

        void Select();

        void GameOn(int);

        void GamePause(int);

        void GameResult(bool, int);
};

#endif // GAME_H
