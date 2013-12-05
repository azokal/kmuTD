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

class Mob {
    element _elem;
    int _life;
    float _velocity;
    GameSprite *_sprite;

public:
    ~Mob() {}
    void move();
    virtual void effect() = 0;
    void looseLife(float damage, element elem);
};

#endif /* defined(__tower_defense__Mob__) */
