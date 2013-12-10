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
//#include "GameSprite.h"

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
    int _life;
    int _bounty;
    float _velocity; // time needed to do 100 unit move
   // GameSprite *_sprite;

public:
    Mob(element type, int life, int bounty) {
        _elem = type;
        _life = life;
        _bounty = bounty;
        _velocity = 1.0;
    }
    ~Mob() {}
    void move();
    void looseLife(float damage, element elem);
};

class FastMob : public Mob {
 public:
    FastMob(element type, int life, int bounty) :
    Mob(type, life, bounty) {
        _velocity = 1.5;
    }
    void effect() {}
};

class HealMob : public Mob {
public:
    HealMob(element type, int life, int bounty) :
    Mob(type, life, bounty) {
        _elem = type;
        _life = life;
        _bounty = bounty;
    }
    
    ~HealMob() {
         // heall all other alive mob, we will need to have a way of access to this list, probably putting it on global variable
    }
};

class UndeadMob : public Mob {
    bool _revive;
    int _oLife;
public:
    UndeadMob(element type, int life, int bounty) :
    Mob(type, life, bounty) {
        _oLife = life;
        _revive = false;
    }
    void looseLife(float damage, element elem);
};

Mob *MobFactory(mobType type);

#endif /* defined(__tower_defense__Mob__) */
