//
//  Mob.cpp
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#include "Mob.h"

void Mob::move() {
    //TODO:: MOVE !
}

void looseLife::looseLife(float damage, element elem) {
    if ((elem + 1) % 6 == _elem)
        _life -= damage * 2;
    if ((elem - 1) % 6 == _elem)
        _life -= damage / 2;
    if (elem == CHAOS)
        _life -= damage;
    if (_elem != NORMAL && elem == NORMAL)
        _life -= damage * 0.8;
}