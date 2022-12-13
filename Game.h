#ifndef GAME_H
#define GAME_H

#include "Grid.h"

class Game{
public:

    ///constructor
    Game();///default constructor

    void characterMove();

private:
    int _time;
    int _money;
    int _gridUnit;
    Grid _myGrids[5][7];

};

#endif // GAME_H
