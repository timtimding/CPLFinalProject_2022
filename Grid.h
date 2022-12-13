#ifndef GRID_H
#define GRID_H

#include "Character.h"

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

    int get_humanNum(){
        return _humanNum;
    }

    int get_vegetableNum(){
        return _vegetableNum;
    }

    Character* get_gridHumans(){
        return _gridHumans;
    }

    Character* get_gridVegetables(){
        return _gridVegetables;
    }

    Grid& operator=(const Grid& grid){
        _isEmpty = grid._isEmpty;
        _pos_x = grid._pos_x;
        _pos_y = grid._pos_y;
        _humanNum = grid._humanNum;
        _vegetableNum = grid._vegetableNum;
        if(!_humanNum){
            _gridHumans = NULL;
        }
        else{
            delete [] _gridHumans;
            _gridHumans = new Character[_humanNum];
            for(int i=0;i<_humanNum;i++){
                _gridHumans[i] = grid._gridHumans[i];
            }
        }
        if(!_vegetableNum){
            _gridVegetables = NULL;
        }
        else{
            delete [] _gridVegetables;
            _gridVegetables = new Character[_vegetableNum];
            for(int i=0;i<_vegetableNum;i++){
                _gridVegetables[i] = grid._gridVegetables[i];
            }
        }
        return *this;
    }


private:
    bool _isEmpty;
    int _pos_x;
    int _pos_y;
    int _humanNum;
    int _vegetableNum;
    Character* _gridHumans;
    Character* _gridVegetables;

};

#endif // GRID_H


