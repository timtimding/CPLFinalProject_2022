#include "Game.h"

void Game::characterMove(){
    for(int i=0;i<5;i++){
        for(int j=6;j>=1;j--){
            if(_myGrids[i][j].get_humanNum()!=0 && _myGrids[i][j].get_vegetableNum()==0){
                ///
                int tempNum = _myGrids[i][j].get_humanNum()+_myGrids[i][j-1].get_humanNum();
                Character* temp = new
                for(int k=0;k<)
            }
        }
    }

}
