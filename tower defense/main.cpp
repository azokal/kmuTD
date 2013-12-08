#include <iostream>
#include "Map.h"
#include "Tower.h"

int main() {
    Map *lol = new Map();

    lol->NewTower(BASIC_L1, 0, 0);
for (int i = 0; i < 18; i++) {
            for (int n = 0; n < 14; n++) {
                if (lol->_map[n][i] == NULL)
                std::cout << 0 << " ";
                else
                                std::cout << 1 << " ";
            }
            std::cout << std::endl;
    }
}

