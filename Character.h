#ifndef CHARACTER_H
#define CHARACTER_H

#include "Data.h"
#include <iostream>

///香菜, 大蒜, 青椒, 菠菜, 三色豆, 農夫, 科學怪人, 暴民, 主教, 吸血鬼
enum characterTag {BLANK, CORIANDER, GARLIC, PIMENT, SPINACH, BEANS, FARMER, FRANKENSTEIN, MOB, VAMPIRE, BISHOP};
enum raceTag {NONE,HUMAN,VEGETABLE};

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
    ///void characterMove();///switch different pictures
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

class Human:public Character{
public:
    Human();
    Human(const Human& human);
    Human(const Data& data, const characterTag& tag);
    ~Human();
protected:
    raceTag _raceTag;
};

class Vegetable:public Character{
public:
    Vegetable();
    Vegetable(const Vegetable& vegetable);
    Vegetable(const Data& data, const characterTag& tag);
    ~Vegetable();
protected:
    raceTag _raceTag;
};

class Coriander:public Vegetable{
public:
    Coriander(int pos_x, int pos_y);
    ~Coriander(){};
};

class Garlic:public Vegetable{
public:
    Garlic(int pos_x, int pos_y);
    ~Garlic(){}
};

class Piment:public Vegetable{
public:
    Piment(int pos_x, int pos_y);
    ~Piment(){}
};

class Spinach:public Vegetable{
public:
    Spinach(int pos_x, int pos_y);
    ~Spinach(){}
};

class Beans:public Vegetable{
public:
    Beans(int pos_x, int pos_y);
    ~Beans(){}
};

class Farmer:public Human{
public:
    Farmer(int pos_x, int pos_y);
    ~Farmer(){}
};

class Frankenstein:public Human{
public:
    Frankenstein(int pos_x, int pos_y);
    ~Frankenstein(){}
};

class Mob:public Human{
public:
    Mob(int pos_x, int pos_y);
    ~Mob(){}
};

class Bishop:public Human{
public:
    Bishop(int pos_x, int pos_y);
    ~Bishop(){}
};

class Vampire:public Human{
public:
    Vampire(int pos_x, int pos_y);
    ~Vampire(){}
};


#endif // CHARACTER_H
