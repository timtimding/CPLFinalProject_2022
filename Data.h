#ifndef DATA_H
#define DATA_H

#include <ostream>
#include <iostream>
#include "SDL_total.h"

class Data{

    friend std::ostream& operator<<(std::ostream& output, const Data& data){
        output<<"Data : ";
        output<<"attack = "<<data._attack<<" ";
        output<<"blood = "<<data._blood<<" ";
        output<<"speed = "<<data._speed<<" ";
        output<<"pos = "<<data._pos_x<<" "<<data._pos_y<<" ";
        output<<"cool = "<<data._cool<<std::endl;
        return output;
    }

public:

    ///constructor
    Data();///default constructor
    Data(const Data& data);///copy constructor
    Data(const int attack, const int blood,
         const int speed, const int pos_x, const int pos_y, const int _cool, const uint32_t _coolStart);///constructor with initialization of private members

    ///destructor
    ~Data();

    ///get value
    //char* get_tag();
    int get_attack();
    int get_blood();
    int get_speed();
    int get_pos_x();
    int get_pos_y();
    int get_cool();
    int coolRemain();
    bool coolDone();
    ///modify value
    //void modify_tag(char* tag);
    void modify_attack(int);
    void modify_blood(int);
    void modify_speed(int);
    void modify_pos_x(int);
    void modify_pos_y(int);
    void c_move();

    ///set value
    //void set_tag(char* tag);
    void set_attack(int);
    void set_blood(int);
    void set_speed(int);
    void set_pos_x(int);
    void set_pos_y(int);
    void set_cool(int);
    void set_coolStart();

    ///operator overloading
    ///assignment operator
    Data& operator=(const Data& data){
        //_tag = data._tag;
        _attack = data._attack;
        _blood = data._blood;
        _speed = data._speed;
        _pos_x = data._pos_x;
        _pos_y = data._pos_y;
        _cool = data._cool;
        _coolStart = data._coolStart;
        return *this;
    }
private:
    //char* _tag;
    int _attack;
    int _blood;
    int _speed;
    int _pos_x;
    int _pos_y;
    int _cool;
    uint32_t _coolStart;
};

#endif // DATA_H
