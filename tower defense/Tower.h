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

typedef struct {
    int price;
    int dmg;
    int range;
    element type;
} infoTower;

class Tower : public CCObject {
protected:
    int _price;
    int _dmg;
    int _range;
    float _fireRate;
    element _type;
    // add target pointer
    std::vector<towerType> upgradeList;
public:
    GameSprite *_sprite;
   static infoTower *stat(towerType);
   void shoot(CCArray *mobs); // need to implement for all basic tower that only have type and cie
    void upgrade(towerType);
    Tower(int price, int dmg, int range, float fireRate, element type, std::string sprite, int x, int y, std::vector<towerType> *upgradeList) {
        _price = price;
        _dmg = dmg;
        _range = range;
        _fireRate = fireRate;
        _type = type;
        _sprite = GameSprite::gameSpriteWithFile(sprite.c_str());
        _sprite->setPosition(ccp(32 * 9 + x * 32 + 16, -16 + CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - y * 32));
        _sprite->retain();
    }
    ~Tower();
};

class Filer :public Tower {
  public:
    Filer() :
    Tower(0,0,0,10, NORMAL, "dirt.png", 0, 0,  new std::vector<towerType>) {
    }
    void shoot() {
    }
};

Tower *TowerFactory(towerType type, int x, int y);

#endif /* defined(__tower_defense__Tower__) */
