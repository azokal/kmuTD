//
//  Mob.cpp
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#include "Mob.h"

void Mob::endPath() {
    
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



Mob *MobFactory(mobType type, GameLayer *g) {

    switch (type) {
        case MOBL1: return (new Mob(NORMAL, 75, 1, g));
        case MOBL2: return (new Mob(NORMAL, 88, 1, g));
        case MOBL3: return (new Mob(NORMAL, 103, 1, g));
        case MOBL4: return (new Mob(NORMAL, 120, 1, g));
        case MOBL5: return (new Mob(NORMAL, 141, 2, g));
        case MOBL6: return (new Mob(EARTH, 164, 2, g));
        case MOBL7: return (new Mob(WATER, 192, 2, g));
        case MOBL8: return (new Mob(FIRE, 225, 2, g));
        case MOBL9: return (new Mob(NATURE, 263, 2, g));
        case MOBL10: return (new Mob(LIGHT, 308, 3, g));
        case MOBL11: return (new FastMob(EARTH, 361, 3, g));
        case MOBL12: return (new Mob(DARK, 422, 3, g));
        case MOBL13: return (new Mob(WATER, 494, 3, g));
        case MOBL14: return (new HealMob(FIRE, 577, 4, g));
        case MOBL15: return (new Mob(LIGHT, 676, 4, g));
        case MOBL16: return (new UndeadMob(DARK, 790, 5, g));
        case MOBL17: return (new Mob(NATURE, 925, 5, g));
        case MOBL18: return (new FastMob(NORMAL, 1082, 6, g));
        case MOBL19: return (new HealMob(LIGHT, 1266, 6, g));
        case MOBL20: return (new Mob(EARTH, 1481, 7, g));
        case MOBL21: return (new UndeadMob(FIRE, 1737, 7, g));
        case MOBL22: return (new Mob(NORMAL, 2036, 8, g));
        case MOBL23: return (new Mob(NATURE, 2387, 9, g));
        case MOBL24: return (new Mob(WATER, 2799, 10, g));
        case MOBL25: return (new FastMob(DARK, 3582, 11, g));
        case MOBL26: return (new Mob(FIRE, 3848, 12, g));
        case MOBL27: return (new Mob(LIGHT, 4512, 13, g));
        case MOBL28: return (new HealMob(NATURE, 5290, 14, g));
        case MOBL29: return (new Mob(DARK, 6203, 16, g));
        case MOBL30: return (new Mob(EARTH, 7273, 17, g));
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