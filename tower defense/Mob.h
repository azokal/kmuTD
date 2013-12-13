//
//  Mob.h
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#ifndef __tower_defense__Mob__
#define __tower_defense__Mob__

#include <iostream>
#include "GameLayer.h"
#include "GameSprite.h"
 
extern CCArray *_mobs;

typedef enum {
    MOBL1,
    MOBL2,
    MOBL3,
    MOBL4,
    MOBL5,
    MOBL6,
    MOBL7,
    MOBL8,
    MOBL9,
    MOBL10,
    MOBL11,
    MOBL12,
    MOBL13,
    MOBL14,
    MOBL15,
    MOBL16,
    MOBL17,
    MOBL18,
    MOBL19,
    MOBL20,
    MOBL21,
    MOBL22,
    MOBL23,
    MOBL24,
    MOBL25,
    MOBL26,
    MOBL27,
    MOBL28,
    MOBL29,
    MOBL30
} mobType;



class Mob : public CCObject {
protected:
    element _elem;
    int _bounty;
    float _velocity; // speed of the mob
    GameLayer *_g;
    
public:
    int _life;
    int _oLife;
    GameSprite *_sprite;
    Mob(element type, int life, int bounty, GameLayer *g) {
        _elem = type;
        _life = life;
        _oLife = life;
        _bounty = bounty;
        _velocity = 1.0;
        this->_g = g;
        _sprite = GameSprite::gameSpriteWithFile("water.png");
        _sprite->setPosition(ccp(32 * 9 + 3 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 0.5 * 32));
        _sprite->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
                                              CCMoveTo::create(2.0f / _velocity, ccp(32 * 9 + 3 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 3 * 32)),
                                              CCMoveTo::create(1.5f / _velocity, ccp(32 * 9 + 1 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 3 * 32)),
                                              CCMoveTo::create(5.0f / _velocity, ccp(32 * 9 + 1 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 9 * 32)),
                                              CCMoveTo::create(3.0f / _velocity, ccp(32 * 9 + 5 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 9 * 32)),
                                              CCMoveTo::create(1.5f / _velocity, ccp(32 * 9 + 5 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 7 * 32)),
                                              CCMoveTo::create(3.0f / _velocity, ccp(32 * 9 + 9 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 7 * 32)),
                                              CCMoveTo::create(4.5f / _velocity, ccp(32 * 9 + 9 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 13 * 32)),
                                              CCMoveTo::create(6.0f / _velocity, ccp(32 * 9 + 1 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 13 * 32)),
                                              CCMoveTo::create(3.0f / _velocity, ccp(32 * 9 + 1 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 17 * 32)),
                                              CCMoveTo::create(8.5f / _velocity, ccp(32 * 9 + 13 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 17 * 32)),
                                              CCMoveTo::create(11.0f / _velocity, ccp(32 * 9 + 13 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 3 * 32)),
                                              CCMoveTo::create(4.5f / _velocity, ccp(32 * 9 + 7 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 3 * 32)),
                                              CCMoveTo::create(2.0f / _velocity, ccp(32 * 9 + 7 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 0.5 * 32)),
                                              CCPlace::create(ccp(32 * 9 + 3 * 32, CCDirector::sharedDirector()->getWinSize().height - 32 * 3 - 0.5 * 32)),
                                                                                         CCCallFunc::create(g,  callfunc_selector(GameLayer::looseLife)),
                                              NULL)));
    }
    ~Mob() {
        _g->_money += _bounty;
        _sprite->stopAllActions();
        _sprite->setVisible(false);
    }
    void endPath();
    bool looseLife(float damage, element elem);
};

class FastMob : public Mob {
 public:
    FastMob(element type, int life, int bounty, GameLayer *g) :
    Mob(type, life, bounty, g) {
        _velocity = 1.5;
    }
    void effect() {}
};

class HealMob : public Mob {
public:
    HealMob(element type, int life, int bounty, GameLayer *g) :
    Mob(type, life, bounty, g) {
        _elem = type;
        _life = life;
        _bounty = bounty;
    }
    
    ~HealMob() {
        CCObject *m;
        
        CCARRAY_FOREACH(_mobs, m) {
            ((Mob *)m)->_life += ((Mob *)m)->_oLife / 5;
        }
    }
};

class UndeadMob : public Mob {
    bool _revive;
public:
    UndeadMob(element type, int life, int bounty, GameLayer *g) :
    Mob(type, life, bounty, g) {
        _revive = false;
    } bool looseLife(float damage, element elem);
};

Mob *MobFactory(mobType type, GameLayer *g);

#endif /* defined(__tower_defense__Mob__) */
