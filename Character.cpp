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

///function of act and behavior

/*
///switch different pictures
void Character::characterMove(){
    _data.modify_pos_x(1);///move 1 unit, maybe 2, 3, or 4, depending on the speed
    ///move the picture to left, 1 grid, needs animation

    ///original grid --> next grid
}
*/

///show attack image, special effect, or blood remaining
void Character::attackEnemy(Character& character){
    character._data.modify_blood(-1*_data.get_attack());
    ///animation?
}

///check blood and show other pictures with respect to the blood
bool Character::checkAlive(){
    return (_data.get_blood()>0);
}




