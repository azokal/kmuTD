//
//  Mob.cpp
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#include "Mob.h"

CCArray *_mobs;

void Mob::endPath() {
    
}

bool Mob::looseLife(float damage, element elem) {
    if ((elem + 1) % 6 == _elem)
        _life -= damage * 2;
    else if ((elem - 1) % 6 == _elem)
        _life -= damage / 2;
    else if (_elem != NORMAL && elem == NORMAL)
        _life -= damage * 0.8;
    else
        _life -= damage;
    if (_sprite)
        _sprite->runAction(CCTintBy::create(0.5f, 0, 255, 255));
    if (_life <= 0)
        return true;
    return false;
}



Mob *MobFactory(mobType type, GameLayer *g) {

    switch (type) {
        case MOBL1: return (new Mob(NORMAL, 75, 1, g, "level1.png"));
        case MOBL2: return (new Mob(NORMAL, 88, 1, g, "level2.png"));
        case MOBL3: return (new Mob(NORMAL, 103, 1, g, "level3.png"));
        case MOBL4: return (new Mob(NORMAL, 120, 1, g, "level4.png"));
        case MOBL5: return (new Mob(NORMAL, 141, 2, g, "level5.png"));
        case MOBL6: return (new Mob(EARTH, 164, 2, g, "level6.png"));
        case MOBL7: return (new Mob(WATER, 192, 2, g, "level7.png"));
        case MOBL8: return (new Mob(FIRE, 225, 2, g, "level8.png"));
        case MOBL9: return (new Mob(NATURE, 263, 2, g, "level9.png"));
        case MOBL10: return (new Mob(LIGHT, 308, 3, g, "level10.png"));
        case MOBL11: return (new FastMob(EARTH, 361, 3, g, "level11.png"));
        case MOBL12: return (new Mob(DARK, 422, 3, g, "level12.png"));
        case MOBL13: return (new Mob(WATER, 494, 3, g, "level13.png"));
        case MOBL14: return (new HealMob(FIRE, 577, 4, g, "level14.png"));
        case MOBL15: return (new Mob(LIGHT, 676, 4, g, "level15.png"));
        case MOBL16: return (new UndeadMob(DARK, 790, 5, g, "level16.png"));
        case MOBL17: return (new Mob(NATURE, 925, 5, g, "level17.png"));
        case MOBL18: return (new FastMob(NORMAL, 1082, 6, g, "level18.png"));
        case MOBL19: return (new HealMob(LIGHT, 1266, 6, g, "level19.png"));
        case MOBL20: return (new Mob(EARTH, 1481, 7, g, "level20.png"));
        case MOBL21: return (new UndeadMob(FIRE, 1737, 7, g, "level21.png"));
        case MOBL22: return (new Mob(NORMAL, 2036, 8, g, "level22.png"));
        case MOBL23: return (new Mob(NATURE, 2387, 9, g, "level23.png"));
        case MOBL24: return (new Mob(WATER, 2799, 10, g, "level24.png"));
        case MOBL25: return (new FastMob(DARK, 3582, 11, g, "level25.png"));
        case MOBL26: return (new Mob(FIRE, 3848, 12, g, "level26.png"));
        case MOBL27: return (new Mob(LIGHT, 4512, 13, g, "level27.png"));
        case MOBL28: return (new HealMob(NATURE, 5290, 14, g, "level28.png"));
        case MOBL29: return (new Mob(DARK, 6203, 16, g, "level29.png"));
        case MOBL30: return (new Mob(EARTH, 7273, 17, g, "level30.png"));
        default: return NULL;
    }
}

bool UndeadMob::looseLife(float damage, element elem) {
    if ((elem + 1) % 6 == _elem)
        _life -= damage * 2;
    else if ((elem - 1) % 6 == _elem)
        _life -= damage / 2;
    else if (_elem != NORMAL && elem == NORMAL)
        _life -= damage * 0.8;
    else
        _life -= damage;
    if (_life <= 0 && _revive == false) {
        _revive = true;
        _life = _oLife;
    }
    _sprite->runAction(CCTintBy::create(1, 255, 0, 0));
    if (_life < 0) {
        return true;
    }
    return false;
}