//
//  Tower.cpp
//  tower defense
//
//  Created by game04 on 13. 12. 3..
//
//

#include "Tower.h"
#include "Map.h"

void Tower::upgrade(towerType type) {
    // destroy tower and replace it by a new one
}

 Tower::~Tower() {
     // destroy sprite all other shit
 }

/*infoTower *Tower::stat(towerType type) {
   
    infoTower *ret = new infoTower;

//return infoTower {10, 10, 10, NORMAL} ;
switch (type) {
        case BASIC_L1:
            
            ret->dmg = 10;
            ret->price = 7;
            ret->type = NORMAL;
            ret->range = 600;
            break;
        default:
            ret->dmg = 0;
            ret->price = 0;
            ret->type = NORMAL;
            ret->range = 0;
            break;
    }
    return (ret);
    
}*/

Tower *TowerFactory(towerType type) {

    std::cout << "><><><><" << std::endl;
    switch (type) {
        case BASIC_L1: return (new TBasic1());
   //    case BASIC_L1: return new basicL2();
        default: return NULL;
    }
}