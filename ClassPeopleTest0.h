#ifndef CLASSPEOPLETEST0_H
#define CLASSPEOPLETEST0_H

#include <bits/stdc++.h>

//template <typename T>
class villager{
    friend int main();
    private:
        int seed;
        int x, y;           // Coordinate of the role
        int hp;             //Health points
        int attackDamage;   //Attack damage
        int speed;          //Moving speed
        bool poisoned;
    public:
        villager::villager(int coordy){
            x = srand(seed) % 50 + 50;    //in the same block, but accurate position is slightly different
            y = coordy * 50 + srand(seed) % 50;
            poisoned = false;
            attackDamage = 5;
            hp = 100;
            speed = 5;
            seed = time(0);
        }
        //~villager();
        //void attack(T x);
        //void move(unsigned long long dt);
        void move();
};

#endif /*CLASSPEOPLETEST0_H*/