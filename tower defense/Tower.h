//
//  Tower.h
//  tower defense
//
//  Created by game04 on 13. 12. 3..
//
//

#ifndef __tower_defense__Tower__
#define __tower_defense__Tower__

#include <iostream>
#include <vector>
#include "GameLayer.h"



typedef enum {
    BASIC_L1,
    BASIC_L2,
    BASIC_L3,
    FIRE_L1,
    FIRE_L2,
    FIRE_L3,
    FIRE_L4,
    FIRE_L5,
    NATURE_L1,
    NATURE_L2,
    NATURE_L3,
    NATURE_L4,
    NATURE_L5,
    EARTH_L1,
    EARTH_L2,
    EARTH_L3,
    EARTH_L4,
    EARTH_L5,
    WATER_L1,
    WATER_L2,
    WATER_L3,
    WATER_L4,
    WATER_L5,
    LIGHT_L1,
    LIGHT_L2,
    LIGHT_L3,
    LIGHT_L4,
    LIGHT_L5,
    DARK_L1,
    DARK_L2,
    DARK_L3,
    DARK_L4,
    DARK_L5
} towerType;

typedef struct {
    int price;
    int dmg;
    int range;
    element type;
} infoTower;

class Tower {
protected:
    int _price;
    int _dmg;
    int _range;
    float _fireRate;
    element _type;
    // add target pointer
    std::vector<towerType> upgradeList;
  //  GameSprite *_sprite;
public:
   static infoTower *stat(towerType);
   void shoot(); // need to implement for all basic tower that only have type and cie
    void upgrade(towerType);
    Tower(int price, int dmg, int range, float fireRate, element type) {
        _price = price;
        _dmg = dmg;
        _range = range;
        _fireRate = fireRate;
        _type = type;
    }
    ~Tower();
};

class Filer :public Tower {
  public:
    Filer() :
    Tower(0,0,0,10, NORMAL) {
    }
    void shoot() {
    }
};

Tower *TowerFactory(towerType type);

#endif /* defined(__tower_defense__Tower__) */
