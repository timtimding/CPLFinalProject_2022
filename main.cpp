#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Texture.h"
#include "game.h"
#include "Test.h"



int frameRate = 50;
int frameDelay = 1000 / frameRate;
Game *game = NULL;

int main( int argc, char* args[] )
{
    unsigned long timeStart, timeLen;
    game->initialize();
    game->startSurface();


    /*while(isRunning){
        timeStart = SDL_GetTicks();


        screenShow();
        timeLen = SDL_GetTicks() - timeStart();
        if(timeLen < frameDelay)
            SDL_Delay(timeLen - frameDelay);
    }*/

	close();
    return 0;
}
