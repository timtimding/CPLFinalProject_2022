#ifndef VEGETABLE_H
#define VEGETABLE_H

#include <bits/stdc++.h>
#include "people.h"
#include <SDL2.h>

class vegetable{
    friend class human;
    private:
        int x, y;           //Coordinate of the role
        int hp;             //Health points
        int attack;         //Attack points
        int cooldown;       //Cooldown time
        bool isrange;       //Range or not
        uint32_t attackPrevTime;    //Last attack time
    public:
        void vegetableGenerate(int arr[]);
        int getcoord();
        bool isRange();
        bool coolDone();
        vegetable& operator-(const people &);
        bool isDead();
};

#endif /*VEGETABLE_H*/