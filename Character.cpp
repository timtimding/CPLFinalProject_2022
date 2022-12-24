#include "Character.h"
#include <iostream>
///constructor
///default constructor
Character::Character(){
    _tag = BLANK;
}

///copy constructor
Character::Character(const Character& character){
    _data = character._data;
    _tag = character._tag;
}

///constructor with initialization
Character::Character(const Data& data, const characterTag& tag){
    _data = data;
    _tag = tag;
}

///destructor
Character::~Character(){}

///get data (Data object stores details)
Data& Character::get_data(){return _data;}

///get tag
characterTag& Character::get_tag(){return _tag;}

///modify tag
void Character::modify_tag(const characterTag& tag){_tag = tag;}

///show attack image, special effect, or blood remaining
void Character::attackEnemy(Character& character){
    character._data.modify_blood(-1*_data.get_attack());
}

///check blood and show other pictures with respect to the blood
bool Character::checkAlive(){
    return (_data.get_blood()>0);
}


Human::Human():Character(){
    _raceTag = HUMAN;
}

Human::Human(const Human& human){
    _data = human._data;
    _tag = human._tag;
    _raceTag = human._raceTag;
}

Human::Human(const Data& data, const characterTag& tag):Character(data, tag){
    _raceTag = HUMAN;
}

Human::~Human(){}

Vegetable::Vegetable():Character(){
    _raceTag = VEGETABLE;
}

Vegetable::Vegetable(const Vegetable& vegetable){
    _data = vegetable._data;
    _tag = vegetable._tag;
    _raceTag = vegetable._raceTag;
}

Vegetable::Vegetable(const Data& data, const characterTag& tag):Character(data, tag){
    _raceTag = VEGETABLE;
}

Vegetable::~Vegetable(){}

Coriander::Coriander(int pos_x, int pos_y){
    _data.set_attack(5);
    _data.set_blood(100);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(3000);
    _data.set_coolStart();
    _raceTag = VEGETABLE;
    _tag = CORIANDER;
}

Garlic::Garlic(int pos_x, int pos_y){
    _data.set_attack(10);
    _data.set_blood(150);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(3000);
    _data.set_coolStart();
    _raceTag = VEGETABLE;
    _tag = GARLIC;
}

Piment::Piment(int pos_x, int pos_y){
    _data.set_attack(10);
    _data.set_blood(180);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(2000);
    _data.set_coolStart();
    _raceTag = VEGETABLE;
    _tag = PIMENT;
}

Spinach::Spinach(int pos_x, int pos_y){
    _data.set_attack(10);
    _data.set_blood(120);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(2000);
    _data.set_coolStart();
    _raceTag = VEGETABLE;
    _tag = SPINACH;
}

Beans::Beans(int pos_x, int pos_y){
    _data.set_attack(5);
    _data.set_blood(150);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(4000);
    _data.set_coolStart();
    _raceTag = VEGETABLE;
    _tag = BEANS;
}

Farmer::Farmer(int pos_x, int pos_y){
    _data.set_attack(5);
    _data.set_blood(100);
    _data.set_speed(2);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(4000);
    _data.set_coolStart();
    _raceTag = HUMAN;
    _tag = FARMER;
}

Frankenstein::Frankenstein(int pos_x, int pos_y){
    _data.set_attack(10);
    _data.set_blood(150);
    _data.set_speed(2);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(2000);
    _data.set_coolStart();
    _raceTag = HUMAN;
    _tag = FRANKENSTEIN;
}

Mob::Mob(int pos_x, int pos_y){
    _data.set_attack(10);
    _data.set_blood(100);
    _data.set_speed(3);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(2000);
    _data.set_coolStart();
    _raceTag = HUMAN;
    _tag = MOB;
}

Bishop::Bishop(int pos_x, int pos_y){
    _data.set_attack(5);
    _data.set_blood(300);
    _data.set_speed(1);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(5000);
    _data.set_coolStart();
    _raceTag = HUMAN;
    _tag = BISHOP;
}

Vampire::Vampire(int pos_x, int pos_y){
    _data.set_attack(20);
    _data.set_blood(30);
    _data.modify_speed(4);
    _data.set_pos_x(pos_x);
    _data.set_pos_y(pos_y);
    _data.set_cool(300);
    _data.set_coolStart();
    _raceTag = HUMAN;
    _tag = VAMPIRE;
}






