//
//  Tower.cpp
//  tower defense
//
//  Created by game04 on 13. 12. 3..
//
//

#include "Tower.h"

Tower *TowerFactory(towerType type, int x, int y) {
    switch (type) {
    //    BASIC_L1: return new basicL1(int x, int y);
   //     BASIC_L1: return new basicL2(int x, int y);
        default: return NULL;
    }
}

void Tower::upgrade(towerType type) {
    // destroy tower and replace it by a new one
}

Tower::~Tower() {
    // destroy sprite all other shit
}