//
//  Map.h
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#ifndef __tower_defense__Map__
#define __tower_defense__Map__

#include <iostream>
#include "Tower.h"

class Map {
    
public:
    Tower *_map[14][18];
    Map();
    ~Map();
    void  NewTower(towerType t, int x, int y);
};

#endif /* defined(__tower_defense__Map__) */
