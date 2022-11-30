#include <bits/stdc++.h>
#typedef unsigned long time_t
time_t time(time_t* ptr);
int seed = time(0);

template <typename T>   //to cope with different roles

class villager{
    private:
        int x, y;           // Coordinate of the role
        int hp;             //Health points
        int attackDamage;   //Attack damage
        int speed;          //Moving speed
    public:
        villager(int coordy);
        ~villager();
        void attack(T x);
        void move(unsigned long long dt);

};
villager::villager(int coordy){
    x = srand(seed) % 50 + 50;    //in the same block, but accurate position is slightly different
    y = coordy * 50+ srand(seed) % 50;
}
~villager(){
    
}
void attack(T x){x.hp -= attackDamage;}
void villager::move(unsigned long long dt) {x -= speed * dt;}