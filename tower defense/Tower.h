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
#include "Mob.h"

typedef struct infoT {
    int price;
    int dmg;
    int range;
    element type;
    infoT(int d, int p, int r, element t) {
        price = p;
        dmg = d;
        range = r;
        type = t;
    }
} infoTower;

class Tower : public CCObject {
protected:
    int _dmg;
    int _range;
    float _fireRate;
    Mob *_target;
    // add target pointer
public:
    std::vector<towerType> *upgradeList;
    element _type;
    int _price;
    GameSprite *_sprite;
   static infoTower *stat(towerType);
   void shoot(CCArray *mobs); // need to implement for all basic tower that only have type and cie
    Tower(int dmg, int price, int range, float fireRate, element type, std::string sprite, int x, int y, std::vector<towerType> *upgradeList) {
        this->upgradeList = upgradeList;
        _price = price;
        _dmg = dmg;
        _range = range;
        _fireRate = fireRate;
        _type = type;
        _target = NULL;
        _sprite = GameSprite::gameSpriteWithFile(   sprite.c_str());
        _sprite->setPosition(ccp(32 * 9 + x * 32 + 16, -16 + CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - y * 32));
        _sprite->retain();
        _sprite->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCCallFuncO::create(this, callfuncO_selector(Tower::shoot), _mobs), CCDelayTime::create(_fireRate), NULL)));
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
