#ifndef PEOPLE_H
#define PEOPLE_H

#include <bits/stdc++.h>
#include "vegetable.h"
#include <SDL2.h>

class people{
    friend class vegetable;
    private:
        int x, y;           //Coordinate of the role
        int hp;             //Health points
        int attack;         //Attack points
        int speed;          //Speed
        int cooldown;       //Cooldown time
        bool isrange;       //Range or not
        uint32_t attackPrevTime;    //Last attack time 
    public:
        void peopleGenerate(int [])
        int getcoord();
        void move();
        bool isRange();
        bool coolDone();    //examine whether cooldown is finished
        people& operator-(const vegetable &);
};

#endif /*PEOPLE_H*/