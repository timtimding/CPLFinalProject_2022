#include "Character.h"
#include "Data.h"
#include "Grid.h"

#define GET_VARIABLE_NAME(Variable) (#Variable)

#include <iostream>
using namespace std;

int main(){

    Data da;
    Data db(da);
    Data dc(100,100,100,2,2,2);
    Data dd;
    cout<<GET_VARIABLE_NAME(da)<<" "<<da<<endl;
    cout<<GET_VARIABLE_NAME(db)<<" "<<db<<endl;
    cout<<GET_VARIABLE_NAME(dc)<<" "<<dc<<endl;
    cout<<GET_VARIABLE_NAME(dd)<<" "<<dd<<endl;

    dd = dc;
    cout<<GET_VARIABLE_NAME(da)<<" "<<da<<endl;
    cout<<GET_VARIABLE_NAME(db)<<" "<<db<<endl;
    cout<<GET_VARIABLE_NAME(dc)<<" "<<dc<<endl;
    cout<<GET_VARIABLE_NAME(dd)<<" "<<dd<<endl;

    Character ca;
    Character cb(ca);
    Character cc(dd,VAMPIRE);
    Character cd;
    cout<<GET_VARIABLE_NAME(ca)<<" "<<ca<<endl;
    cout<<GET_VARIABLE_NAME(cb)<<" "<<cb<<endl;
    cout<<GET_VARIABLE_NAME(cc)<<" "<<cc<<endl;
    cout<<GET_VARIABLE_NAME(cd)<<" "<<cd<<endl;

    cd = cc;
    cout<<GET_VARIABLE_NAME(ca)<<" "<<ca<<endl;
    cout<<GET_VARIABLE_NAME(cb)<<" "<<cb<<endl;
    cout<<GET_VARIABLE_NAME(cc)<<" "<<cc<<endl;
    cout<<GET_VARIABLE_NAME(cd)<<" "<<cd<<endl;

    Grid ga;
    Grid gb(ga);
    Grid gc(false, 2, 3, 1, 1, &cc, &cd);
    Grid gd;
    cout<<GET_VARIABLE_NAME(ga)<<" "<<ga<<endl;
    cout<<GET_VARIABLE_NAME(gb)<<" "<<gb<<endl;
    cout<<GET_VARIABLE_NAME(gc)<<" "<<gc<<endl;
    cout<<GET_VARIABLE_NAME(gd)<<" "<<gd<<endl;


    ///maintain fight on a grid
    gc.gridFight();
    cout<<GET_VARIABLE_NAME(gc)<<" "<<gc<<endl;

    /*
    gd = gc;
    cout<<GET_VARIABLE_NAME(ga)<<" "<<ga<<endl;
    cout<<GET_VARIABLE_NAME(gb)<<" "<<gb<<endl;
    cout<<GET_VARIABLE_NAME(gc)<<" "<<gc<<endl;
    cout<<GET_VARIABLE_NAME(gd)<<" "<<gd<<endl;
    */

    ///game start

    ///Grid myGrids[5][7];

    ///load information from .txt file, including *:nothing,
    ///C:coriander 1,
    ///G:garlic 2,
    ///P:piment 3,
    ///S:spinach 4,
    ///B:beans 5

    ///maintain move and position of character, move



    return 0;
}



