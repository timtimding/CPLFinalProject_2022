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
void SetProgress(int, int);
    friend std::ostream& operator<<(std::ostream& output,const Game *gm){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 7; j++){
            output << gm->_myGrids[i][j].get_humanNum();}
            output << "\n";
        }
        output << "\n";
        return output;
    }
    public:
        Game(){
            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 7; j++){
                    _myGrids[i][j].set_gridHumans(0, NULL);
                    _myGrids[i][j].set_gridVegetables(0, NULL);
                }
        }
        static bool isRunning;
        static SDL_Event event;
        static int frameCount;
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
    private:
        static Grid _myGrids[5][7];
};


#endif // GAME_H
