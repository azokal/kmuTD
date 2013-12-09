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
    // set initial pos of the mob
    // use CCSEQUENCE and CCMoveTo and use the velocity to set the time it takes, should be called at init and at the end of this sequence.
    // the CCSEQUENCE shoudl contain (in this order) :
    //  - the move to the end of the maze
    //  - l'appel a la perte de vie du joueur
    //  - l'appel a cette fonction (reset de pos + relancer l'action)
}

void Mob::looseLife(float damage, element elem) {
    if ((elem + 1) % 6 == _elem)
        _life -= damage * 2;
    if ((elem - 1) % 6 == _elem)
        _life -= damage / 2;
    if (elem == CHAOS)
        _life -= damage;
    if (_elem != NORMAL && elem == NORMAL)
        _life -= damage * 0.8;
}



Mob *MobFactory(mobType type) {

    switch (type) {
        case MOBL1: return (new Mob(NORMAL, 75, 1));
        case MOBL2: return (new Mob(NORMAL, 88, 1));
        case MOBL3: return (new Mob(NORMAL, 103, 1));
        case MOBL4: return (new Mob(NORMAL, 120, 1));
        case MOBL5: return (new Mob(NORMAL, 141, 2));
        case MOBL6: return (new Mob(EARTH, 164, 2));
        case MOBL7: return (new Mob(WATER, 192, 2));
        case MOBL8: return (new Mob(FIRE, 225, 2));
        case MOBL9: return (new Mob(NATURE, 263, 2));
        case MOBL10: return (new Mob(LIGHT, 308, 3));
        case MOBL11: return (new FastMob(EARTH, 361, 3));
        case MOBL12: return (new Mob(DARK, 422, 3));
        case MOBL13: return (new Mob(WATER, 494, 3));
        case MOBL14: return (new HealMob(FIRE, 577, 4));
        case MOBL15: return (new Mob(LIGHT, 676, 4));
        case MOBL16: return (new UndeadMob(DARK, 790, 5));
        case MOBL17: return (new Mob(NATURE, 925, 5));
        case MOBL18: return (new FastMob(NORMAL, 1082, 6));
        case MOBL19: return (new HealMob(LIGHT, 1266, 6));
        case MOBL20: return (new Mob(EARTH, 1481, 7));
        case MOBL21: return (new UndeadMob(FIRE, 1737, 7));
        case MOBL22: return (new Mob(NORMAL, 2036, 8));
        case MOBL23: return (new Mob(NATURE, 2387, 9));
        case MOBL24: return (new Mob(WATER, 2799, 10));
        case MOBL25: return (new FastMob(DARK, 3582, 11));
        case MOBL26: return (new Mob(FIRE, 3848, 12));
        case MOBL27: return (new Mob(LIGHT, 4512, 13));
        case MOBL28: return (new HealMob(NATURE, 5290, 14));
        case MOBL29: return (new Mob(DARK, 6203, 16));
        case MOBL30: return (new Mob(EARTH, 7273, 17));
        default: return NULL;
    }
}

void UndeadMob::looseLife(float damage, element elem) {
    if ((elem + 1) % 6 == _elem)
        _life -= damage * 2;
    if ((elem - 1) % 6 == _elem)
        _life -= damage / 2;
    if (elem == CHAOS)
        _life -= damage;
    if (_elem != NORMAL && elem == NORMAL)
        _life -= damage * 0.8;
    if (_life <= 0 && _revive == false) {
        _revive = true;
        _life = _oLife;
    }
}