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
   virtual void shoot() = 0;
    void upgrade(towerType);
    Tower() {
            std::cout << "canard ?" << std::endl;
    }
    ~Tower();
};

class Filer :public Tower {
    void shoot() {
    }
};

class TBasic1 : public Tower {
public:
    TBasic1() {
        std::cout << "canard ?2" << std::endl;
        _price = 7;
        _dmg = 16;
        _range = 300;
        _fireRate = 0.1;
        _type = NORMAL;
    }
    void shoot() {
      // to fill
    }
};

Tower *TowerFactory(towerType type);

#endif /* defined(__tower_defense__Tower__) */
