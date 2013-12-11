//
//  Map.cpp
//  tower defense
//
//  Created by game03 on 13. 12. 5..
//
//

#include "Map.h"
#include "Tower.h"

Map::Map() {
    Filer *road = new Filer();
    
    for (int i = 0; i < 14; i++) {
            for (int n = 0; n < 18; n++) {
                _map[i][n] = NULL;
            }
    }
    _map[2][0] = road;
    _map[3][0] = road;
   _map[2][1] = road;
   _map[3][1] = road;
   _map[2][2] = road;
   _map[3][2] = road;
    _map[2][3] = road;
   _map[3][3] = road;
    _map[0][2] = road;
    _map[1][2] = road;
    _map[0][3] = road;
    _map[1][3] = road;
    for (int i = 3; i < 10; i++) {
        _map[0][i] = road;
        _map[1][i] = road;
    }
    for (int i = 2; i < 6; i++) { 
        _map[i][8] = road;
        _map[i][9] = road;
    }
    
    _map[4][7] = road;
    _map[5][7] = road;
    _map[4][6] = road;
    _map[5][6] = road;
   for (int i = 6; i < 10; i++) {
        _map[i][7] = road;
        _map[i][6] = road;
    }
    for (int i = 8; i < 12; i++) {
        _map[8][i] = road;
        _map[9][i] = road;
    }
    for (int i = 9; i >= 0; i--) {
        _map[i][12] = road;
        _map[i][13] = road;
    }
    for (int i = 14; i < 16; i++) {
        _map[0][i] = road;
        _map[1][i] = road;
    }
     for (int i = 0; i < 12; i++) {
        _map[i][16] = road;
        _map[i][17] = road;
    }
     for (int i = 17; i >= 2; i--) {
        _map[12][i] = road;
        _map[13][i] = road;
    }
    for (int i = 13; i >= 6; i--) {
        _map[i][2] = road;
        _map[i][3] = road;
    }
    _map[6][1] = road;
    _map[6][0] = road;
    _map[7][1] = road;
    _map[7][0] = road;
}

void  Map::NewTower(towerType type, int x, int y) {
   _map[x][y] = TowerFactory(type, x, y);
}