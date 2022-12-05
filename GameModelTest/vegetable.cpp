#include <bits/stdc++.h>
#include "vegetable.h"
#include "people.h"
#include <SDL2.h>

/*
class vegetable{
    friend class human;
    private:
        int x, y;           //Coordinate of the role
        int hp;             //Health points
        int attack;         //Attack points
        int cooldown;       //Cooldown time
        bool isRange;       //Range or not
    public:
        vegetable(int arr[]){
            x = arr[0];
            y = arr[1];
            hp = arr[2];
            attack = arr[3];
            cooldown = arr[4];
            isRange = (arr[5] > 0) ? true : false;
        }
        ~vegetable(){
        }
        int getcoord(){
            return (x / 100 * 10 + y / 100);
        }
};*/
void vegetableGenerate(int arr[]){
            x = arr[0];
            y = arr[1];
            hp = arr[2];
            attack = arr[3];
            cooldown = arr[4];
            isrange = (arr[5] > 0) ? true : false;
            attackPrevTime = SDL_getTicks();
}

int getcoord(){
    return (x / 100 * 10 + y / 100);
}

bool isRange(){
    return isRange;
}

bool coolDone(){
    if( SDL_GetTicks() - attackPrevTime >= cooldown)
        return true;
    else
        return false;
}

vegetable & operator-(const people &p){
    hp -= p.attack;
    p.attackPrevTime = SDL_GetTicks();
    return *this;
}

bool isDead(){
    return (hp > 0);
}