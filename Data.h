#ifndef DATA_H
#define DATA_H

#include <ostream>

class Data{

    friend std::ostream& operator<<(std::ostream& output, const Data& data){
        output<<"Data : ";
        output<<"attack = "<<data._attack<<" ";
        output<<"shield = "<<data._shield<<" ";
        output<<"blood = "<<data._blood<<" ";
        output<<"speed = "<<data._speed<<" ";
        output<<"pos = "<<data._pos_x<<" "<<data._pos_y<<std::endl;
        return output;
    }

public:

    ///constructor
    Data();///default constructor
    Data(const Data& data);///copy constructor
    Data(const double attack, const double shield, const double blood,
         const double speed, const int pos_x, const int pos_y);///constructor with initialization of private members

    ///destructor
    ~Data();

    ///get value
    //char* get_tag();
    double get_attack();
    double get_shield();
    double get_blood();
    double get_speed();
    int get_pos_x();
    int get_pos_y();

    ///modify value
    //void modify_tag(char* tag);
    void modify_attack(double delta);
    void modify_shield(double delta);
    void modify_blood(double delta);
    void modify_speed(double delta);
    void modify_pos_x(int delta);
    void modify_pos_y(int delta);

    ///set value
    //void set_tag(char* tag);
    void set_attack(double attack);
    void set_shield(double shield);
    void set_blood(double blood);
    void set_speed(double speed);
    void set_pos_x(int pos_x);
    void set_pos_y(int pos_y);

    ///operator overloading
    ///assignment operator
    Data& operator=(const Data& data){
        //_tag = data._tag;
        _attack = data._attack;
        _shield = data._shield;
        _blood = data._blood;
        _speed = data._speed;
        _pos_x = data._pos_x;
        _pos_y = data._pos_y;
        return *this;
    }



private:
    //char* _tag;
    double _attack;
    double _shield;
    double _blood;
    double _speed;
    int _pos_x;
    int _pos_y;

};

#endif // DATA_H
