#include "Data.h"

Data::Data(){
    //_tag = "undefined";
    _attack = 0;
    _shield = 0;
    _blood = 0;
    _speed = 0;
    _pos_x = 0;
    _pos_y = 0;
}

Data::Data(const Data& data){
    //_tag = data._tag;
    _attack = data._attack;
    _shield = data._shield;
    _blood = data._blood;
    _speed = data._speed;
    _pos_x = data._pos_x;
    _pos_y = data._pos_y;
}

Data::Data(const double attack, const double shield, const double blood,
           const double speed, const int pos_x, const int pos_y){
    //_tag = tag;
    _attack = attack;
    _shield = shield;
    _blood = blood;
    _speed = speed;
    _pos_x = pos_x;
    _pos_y = pos_y;
}

Data::~Data(){}


//char* Data::get_tag(){return _tag;}
double Data::get_attack(){return _attack;}
double Data::get_shield(){return _shield;}
double Data::get_blood(){return _blood;}
double Data::get_speed(){return _speed;}
int Data::get_pos_x(){return _pos_x;}
int Data::get_pos_y(){return _pos_y;}


//void Data::modify_tag(char* tag){_tag = tag;}
void Data::modify_attack(double delta){_attack += delta;}
void Data::modify_shield(double delta){_shield += delta;}
void Data::modify_blood(double delta){_blood += delta;}
void Data::modify_speed(double delta){_speed += delta;}
void Data::modify_pos_x(int delta){_pos_x += delta;}
void Data::modify_pos_y(int delta){_pos_y += delta;}


//void Data::set_tag(char* tag){_tag = tag;}
void Data::set_attack(double attack){_attack = attack;}
void Data::set_shield(double shield){_shield = shield;}
void Data::set_blood(double blood){_blood = blood;}
void Data::set_speed(double speed){_speed = speed;}
void Data::set_pos_x(int pos_x){_pos_x = pos_x;}
void Data::set_pos_y(int pos_y){_pos_y = pos_y;}
