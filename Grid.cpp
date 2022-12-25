#include "Grid.h"

///default constructor
Grid::Grid(){
    _isEmpty = true;
    _pos_x = 0;
    _pos_y = 0;
    _humanNum = 0;
    _vegetableNum = 0;
    _gridHumans = NULL;
    _gridVegetables = NULL;
}


///copy constructor
Grid::Grid(Grid& grid){
    _isEmpty = grid._isEmpty;
    _pos_x = grid._pos_x;
    _pos_y = grid._pos_y;
    _humanNum = grid._humanNum;
    _vegetableNum = grid._vegetableNum;
    if(!_humanNum){
        _gridHumans = NULL;
    }
    else{
        _gridHumans = new Character[_humanNum];
        for(int i=0;i<_humanNum;i++){
            _gridHumans[i] = grid._gridHumans[i];
        }
    }

    if(!_vegetableNum){
        _gridVegetables = NULL;
    }
    else{
        _gridVegetables = new Character[_vegetableNum];
        for(int i=0;i<_vegetableNum;i++){
            _gridVegetables[i] = grid._gridVegetables[i];
        }
    }
}

///constructor with initialization
Grid::Grid(bool isEmpty, int pos_x, int pos_y, int humanNum, int vegetableNum, Character* gridHumans, Character* gridVegetables){
    _isEmpty = isEmpty;
    _pos_x = pos_x;
    _pos_y = pos_y;
    _humanNum = humanNum;
    _vegetableNum = vegetableNum;
    if(!_humanNum){
        _gridHumans = NULL;
    }
    else{
        _gridHumans = new Character[_humanNum];
        for(int i=0;i<_humanNum;i++){
            _gridHumans[i] = gridHumans[i];
        }
    }
    if(!_vegetableNum){
        _gridVegetables = NULL;
    }
    else{
        _gridVegetables = new Character[_vegetableNum];
        for(int i=0;i<_vegetableNum;i++){
            _gridVegetables[i] = gridVegetables[i];
        }

    }
}


///destructor
Grid::~Grid(){
    delete [] _gridHumans;
    delete [] _gridVegetables;
}

///maintain each round/fight on this grid
int Grid::gridFight(){
    if(_isEmpty){
        ///std::cout << "EMPTY" << std::endl;
        return 0;
    }
    else if((_humanNum*_vegetableNum) == 0){
        //std::cout << "noFight" <<std::endl;
        return 0;
    }
    else{
        ///blood --
        for(int i=0;i<_humanNum;i++){
            for(int j=0;j<_vegetableNum;j++){
                if(_gridHumans[i].get_data().coolDone()){
                    _gridHumans[i].attackEnemy(_gridVegetables[j]);
                    _gridHumans[i].get_data().set_coolStart();
                }
                if(_gridVegetables[i].get_data().coolDone()){
                    _gridVegetables[j].attackEnemy(_gridHumans[i]);
                    _gridVegetables[j].get_data().set_coolStart();
                }
            }
        }
        ///check alive
        int casualtyHuman = 0;
        int casualtyVegetable = 0;

        for(int i=0;i<_humanNum;i++){
            if(_gridHumans[i].checkAlive()){
                continue;
            }
            else{
                casualtyHuman+=1;
                _gridHumans[i].modify_tag(BLANK);
            }
        }

        for(int j=0;j<_vegetableNum;j++){
            if(_gridVegetables[j].checkAlive()){
                continue;
            }
            else{
                casualtyVegetable+=1;
                _gridVegetables[j].modify_tag(BLANK);
            }
        }
        ///reallocate the dynamic arrays
        if(casualtyHuman){
            Character* temp = new Character[_humanNum-casualtyHuman];
            for(int i=0;i<_humanNum;i++){
                if(_gridHumans[i].get_tag()!=BLANK){
                    temp[i] = _gridHumans[i];
                }
            }
            _humanNum -= casualtyHuman;
            delete [] _gridHumans;
            _gridHumans = new Character[_humanNum];
            for(int i=0;i<_humanNum;i++){
                _gridHumans[i] = temp[i];
            }
            delete [] temp;
        }
        if(casualtyVegetable){
            Character* temp = new Character[_vegetableNum-casualtyVegetable];
            for(int j=0;j<_vegetableNum;j++){
                if(_gridVegetables[j].get_tag()!=BLANK){
                    temp[j] = _gridVegetables[j];
                }
            }
            _vegetableNum -= casualtyVegetable;
            delete [] _gridVegetables;
            _gridVegetables = new Character[_vegetableNum];
            for(int j=0;j<_vegetableNum;j++){
                _gridVegetables[j] = temp[j];
            }
            delete [] temp;
        }
        if(!(_humanNum+_vegetableNum)){
            _isEmpty = true;
        }
        return casualtyVegetable;
    }

}
void Grid::set_gridHumans(int humanNum, Character* gridHumans){
    if(humanNum > 0){
        set_isEmpty(false);
        Character* temp = new Character[_humanNum];
        for(int i=0;i<_humanNum;i++){
            temp[i] = _gridHumans[i];
        }
        delete [] _gridHumans;
        _gridHumans = new Character[_humanNum+humanNum];
        for(int i=0;i<_humanNum;i++){
            _gridHumans[i] = temp[i];
        }

        for(int i=0+_humanNum;i<humanNum+_humanNum;i++){
            _gridHumans[i] = gridHumans[i];
        }
        _humanNum += humanNum;
    }
    else{
        set_isEmpty(true);
        _humanNum = 0;
        delete [] _gridHumans;
        _gridHumans = NULL;
    }
}
void Grid::set_gridVegetables(int vegetableNum, Character* gridVegetables){
    if(vegetableNum){
        set_isEmpty(false);
        _vegetableNum = vegetableNum;
        delete [] _gridVegetables;
        _gridVegetables = new Character[vegetableNum];
        for(int i=0;i<vegetableNum;i++){
            _gridVegetables[i] = gridVegetables[i];
        }
    }
    else{
        set_isEmpty(true);
        _vegetableNum = 0;
        delete [] _gridVegetables;
        _gridVegetables = NULL;
    }
}

Grid& Grid::operator=(const Grid& grid){
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
