#include <bits/stdc++.h>
#include <SDL2.h>

/*
class people{
    friend class vegetable;
    private:
        int x, y;           //Coordinate of the role
        int hp;             //Health points
        int attack;         //Attack points
        int speed;          //Speed
        int cooldown;       //Cooldown time
        bool isRange;       //Range or not
    public:
        people(int arr[]){
            x = arr[0];
            y = arr[1];
            hp = arr[2];
            speed = arr[3];
            cooldown = arr[4];
            isRange = (arr[5] > 0) ? true : false;
        }
        bool coolDone();
};*/
peopleGenetate(int arr[]){
            x = arr[0];
            y = arr[1];
            hp = arr[2];
            speed = arr[3];
            cooldown = arr[4];
            isrange = (arr[5] > 0) ? true : false;
}

int getcoord(){
   return (x / 100 * 10 + y / 100);
}

void move(){
    x -= speed;
    y += rand() % 10 - 5;
}

bool isRange() {
    return isrange;
}

bool coolDone(){
    if( SDL_GetTicks() - attackPrevTime >= cooldown)
        return true;
    else
        return false;
}

people& operator-(const vegetable &v){
    hp -= v.attack;
    v.attackPrevTime = SDL_GetTicks();
    return *this;
}