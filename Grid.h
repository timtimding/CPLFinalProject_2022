#ifndef GRID_H
#define GRID_H

#include "Character.h"
#include <iostream>

class Grid{
    friend std::ostream& operator<<(std::ostream& output, const Grid& grid){
        output<<"Grid: ";
        output<<"isEmpyty = "<<grid._isEmpty<<" ";
        output<<"pos = "<<grid._pos_x<<" "<<grid._pos_y<<" ";
        output<<"humanNum = "<<grid._humanNum<<" ";
        output<<"vegetableNum = "<<grid._vegetableNum<<" ";
        if(grid._humanNum){
            output<<std::endl;
            for(int i=0;i<grid._humanNum;i++){
                output<<grid._gridHumans[i];
            }
        }
        if(grid._vegetableNum){
            output<<std::endl;
            for(int i=0;i<grid._vegetableNum;i++){
                output<<grid._gridVegetables[i];
            }
        }
        return output;
    }

public:

    ///constructor
    Grid();///default constructor
    Grid(Grid& grid);///copy constructor
    ///constructor with initialization
    Grid(bool isEmpty, int pos_x, int pos_y, int humanNum, int vegetableNum, Character* gridHumans, Character* gridVegetables);

    ///destructor
    ~Grid();

    ///maintain each round/fight on this grid
    void gridFight();

    ///get value
    bool get_isEmpty(){return _isEmpty;}
    int get_pos_x(){return _pos_x;}
    int get_pos_y(){return _pos_y;}
    int get_humanNum(){return _humanNum;}
    int get_vegetableNum(){return _vegetableNum;}
    Character* get_gridHumans(){return _gridHumans;}
    Character* get_gridVegetables(){return _gridVegetables;}

    ///set value
    void set_isEmpty(bool isEmpty){_isEmpty = isEmpty;}
    void set_pos_x(int pos_x){_pos_x = pos_x;}
    void set_pos_y(int pos_y){_pos_y = pos_y;}
    void c_move(){_pos_x -= _speed;}
    void set_humanNum(int humanNum){_humanNum = humanNum;}
    void set_vegetableNum(int vegetableNum){_vegetableNum = vegetableNum;}
    void set_gridHumans(int, Character*);
    void set_gridVegetables(int, Character*);

    Grid& operator=(const Grid& );


private:
    bool _isEmpty;
    int _pos_x;
    int _pos_y;
    int _speed;
    int _humanNum;
    int _vegetableNum;
    Character* _gridHumans;
    Character* _gridVegetables;

};

#endif // GRID_H


