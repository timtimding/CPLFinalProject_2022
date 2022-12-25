#ifndef GAME_H
#define GAME_H

#include "SDL_total.h"
#include <iostream>
#include <stdio.h>
#include "Texture.h"
#include "Rendering.h"
#include "fileManager.h"
#include "Grid.h"
#include <fstream>
#include <iomanip>
#include "gameTimer.h"

int & GetProgress();

void SetProgress(int, int);

class Game{
    public:

        static SDL_Event event;

        void initialize();

        void startSurface();

        void mainMenu();

        void Tutorial();

        void Settings();

        void Select();

        void GameOn(int);

        bool placeRole(int , gameTimer*, int &);

        void GamePause(int);

        void GameResult(bool, int);

        void gameInit();

        int characterMove();

        void showRole();
};


#endif // GAME_H
