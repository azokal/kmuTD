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

typedef enum {
    BASIC
}towerType;

class Tower {
    int _dmg;
    int _range;
    float _fireRate;
    // add target pointer
    std::vector<towerType> upgradeList;
    
    void shoot();
    void upgrade();
};

#endif /* defined(__tower_defense__Tower__) */
