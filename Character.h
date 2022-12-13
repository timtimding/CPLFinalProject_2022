#ifndef CHARACTER_H
#define CHARACTER_H

#include "Data.h"


///����, �j�[, �C��, �Ե�, �T�⨧, �A��, ��ǩǤH, �ɥ�, �D��, �l�尭
enum characterTag {BLANK, CORIANDER, GARLIC, PIMENT, SPINACH, BEANS, FARMER, FRANKENSTEIN, MOB, BISHOP, VAMPIRE};


class Character{
    friend std::ostream& operator<<(std::ostream& output, const Character& character){
        output<<"Character: ";
        output<<"tag = "<<character._tag<<" ";
        output<<character._data<<std::endl;
        return output;
    }
public:


    ///constructor
    Character();///default constructor
    Character(const Character& character);///copy constructor
    Character(const Data& data, const characterTag& tag);///constructor with initialiation

    ///destructor
    ~Character();

    ///get data (Data object stores details)
    Data& get_data();

    ///get tag
    characterTag& get_tag();

    ///modify tag
    void modify_tag(const characterTag& tag);

    ///function of act and behavior
    virtual int useSkill(){return 0;}
    void characterMove();///switch different pictures
    void attackEnemy(Character& character);
    bool checkAlive();///check blood and show other pictures with respect to the blood

    Character& operator=(const Character& character){
        _data = character._data;
        _tag = character._tag;
        return *this;
    }

protected:

    Data _data;
    characterTag _tag;

};



#endif // CHARACTER_H
