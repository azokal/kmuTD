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
    BASIC_L2
} towerType;

typedef struct {
    int price;
    int dmg;
    int range;
    element type;
} infoTower;

class Tower {
    int _price;
    int _dmg;
    int _range;
    float _fireRate;
    element _type;
    // add target pointer
    std::vector<towerType> upgradeList;
    GameSprite *_sprite;
public:
    static infoTower stat();
    virtual void shoot() = 0;
    void upgrade(towerType);
    ~Tower();
};

#endif /* defined(__tower_defense__Tower__) */
