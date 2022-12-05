#include <bits/stdc++.h>
#include "ClassPeopleTest0.h"
// #typedef unsigned long time_t
// time_t time(time_t* ptr);


template <typename T>   //to cope with different roles

class villager{
    friend int main();
    private:
        int x, y;           // Coordinate of the role
        int hp;             //Health points
        int attackDamage;   //Attack damage
        int speed;          //Moving speed
        bool poisoned;
    public:
        villager(int coordy);
        ~villager();
        void attack(T x);
        void move(unsigned long long dt);
};

villager::~villager(){
    delete[] *this;
}

void attack(T x){x.hp -= attackDamage;}
void villager::move() {x -= speed;}