#include <bits/stdc++.h>
#include "people.h"
#include "vegetable.h"

int tmp;
int main(){
    vegetable **vegeArray;
    *vegeArray = new vegetable[7];
    for(int i = 0; i < 7; i++)
        vegeArray[i] = new vegetable[11];

    people **peopleArray;
    *peopleArray = new people[7];
    for(int i = 0; i < 7; i++)
        peopleArray[i] = new people[10] = NULL;  

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 10; j++){
            temp = peopleArray[i][j].getcoord();
            if(vegeArray[tmp % 10][tmp / 10] != NULL){
                if(peopleArray[i][j].coolDone())
                    vegeArray[tmp % 10][tmp / 10] - peopleArray[i][j];
                if(vegeArray[i][j].coolDone() && !vegeArray.isRange())
                    peopleArray[i][j] - vegeArray[tmp % 10][tmp / 10];
            }
            if(vegeArray[tmp % 10 - 1][tmp / 10] != NULL && vegeArray[tmp % 10 - 1][tmp / 10].coolDone() && vegeArray[tmp % 10 - 1][tmp / 10].isRange())  //down
                peopleArray[i][j] - vegeArray[tmp % 10 - 1][tmp / 10];

            if(vegeArray[tmp % 10 + 1][tmp / 10] != NULL && vegeArray[tmp % 10 + 1][tmp / 10].coolDone() && vegeArray[tmp % 10 + 1][tmp / 10].isRange())  //up
                peopleArray[i][j] - vegeArray[tmp % 10 + 1][tmp / 10];

            if(vegeArray[tmp % 10 ][tmp / 10- 1] != NULL && vegeArray[tmp % 10][tmp / 10 - 1].coolDone() && vegeArray[tmp % 10][tmp / 10 - 1].isRange())  //left
                peopleArray[i][j] - vegeArray[tmp % 10][tmp / 10 - 1];
        }
    }
}