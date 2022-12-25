#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "SDL_total.h"

class gameTimer{
public:
    gameTimer(){
        startTime = SDL_GetTicks();
        frameDelay = 1000 / 60;
    }
    uint32_t getStartTime(){return startTime;}
    void tick(){frameTick = SDL_GetTicks();}
    void pauseRec(){pauseTime = SDL_GetTicks();}
    void pauseUpdate(){startTime += (SDL_GetTicks() - pauseTime);}
    bool timeOver(){return (SDL_GetTicks() - startTime > 1000*120);}
    int tickLeft(){return frameDelay - (SDL_GetTicks() - frameTick);}

private:
    uint32_t startTime;
    uint32_t frameTick;
    uint32_t timeLeft;
    uint32_t pauseTime;
    uint32_t frameDelay;
};
#endif // GAMETIMER_H
