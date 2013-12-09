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

infoTower *Tower::stat(towerType type) {
   
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
    
}

void shoot() {
    
}

Tower *TowerFactory(towerType type) {

    switch (type) {
        // three basic tower
        case FIRE_L1: return new Tower(24, 50, 500,  0.31, FIRE);
        case FIRE_L2: return new Tower(120, 175, 500, 0.31, FIRE);
        case FIRE_L3: return new Tower(600, 625, 500, 0.31, FIRE);
        case FIRE_L4: return new Tower(3000, 2125, 500, 0.31, FIRE);
        case FIRE_L5: return new Tower(45000, 11225, 500, 0.31, FIRE);
        case NATURE_L1: return new Tower(80, 50, 700,  0.66, NATURE);
        case NATURE_L2: return new Tower(400, 175, 700,  0.66, NATURE);
        case NATURE_L3: return new Tower(2000, 625, 700,  0.66, NATURE);
        case NATURE_L4: return new Tower(10000, 2125, 700,  0.66, NATURE);
        case NATURE_L5: return new Tower(150000, 11225, 700,  0.66, NATURE);
        case EARTH_L1: return new Tower(100, 50, 600,  1, EARTH);
        case EARTH_L2: return new Tower(480, 175, 600,  1, EARTH);
        case EARTH_L3: return new Tower(2400, 625, 600,  1, EARTH);
        case EARTH_L4: return new Tower(12000, 2125, 600,  1, EARTH);
        case EARTH_L5: return new Tower(180000, 11225, 600,  1, EARTH);
        case WATER_L1: return new Tower(30, 50, 700,  0.31, WATER);
        case WATER_L2: return new Tower(180, 175, 7010,  0.31, WATER);
        case WATER_L3: return new Tower(900, 625, 700,  0.31, WATER);
        case WATER_L4: return new Tower(4500, 2125, 700,  0.31, WATER);
        case WATER_L5: return new Tower(70000, 11225, 700,  0.31, WATER);
        case LIGHT_L1: return new Tower(57, 50, 1500,  0.66, LIGHT);
        case LIGHT_L2: return new Tower(285, 175, 1500,  0.66, LIGHT);
        case LIGHT_L3: return new Tower(1425, 625, 1500,  0.66, LIGHT);
        case LIGHT_L4: return new Tower(7125, 2125, 1500,  0.66, LIGHT);
        case LIGHT_L5: return new Tower(106875, 11225, 1500,  0.66, LIGHT);
        case DARK_L1: return new Tower(157, 50, 1125,  1.5, NATURE);
        case DARK_L2: return new Tower(785, 175, 1125,  1.5, NATURE);
        case DARK_L3: return new Tower(3925, 625, 1125,  1.5, NATURE);
        case DARK_L4: return new Tower(19625, 2125, 1125,  1.5, NATURE);
        case DARK_L5: return new Tower(294375, 11225, 1125,  1.5, NATURE);
        default: return NULL;
    }
}