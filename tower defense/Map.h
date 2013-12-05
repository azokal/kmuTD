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
    Tower ***_map;
    
public:
    Map();
    ~Map();
};

#endif /* defined(__tower_defense__Map__) */
