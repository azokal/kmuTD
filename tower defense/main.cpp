#include <iostream>
#include "Map.h"
#include "Tower.h"
#include "Mob.h"

void endGame() {
    if (1/* put life of game layer > 0 */) {
        // do loose action, then go back on main menu on next click
    } else {
        // do win action
    }
}

int main() {
    // fonction init de cocos
    Map *terrain = new Map();

    terrain->NewTower(BASIC_L1, 0, 0);
    for (int i = 0; i < 18; i++) {
            for (int n = 0; n < 14; n++) {
                if (terrain->_map[n][i] == NULL)
                std::cout << 0 << " ";
                else
                                std::cout << 1 << " ";
            }
            std::cout << std::endl;
    }

    // faire un CCArray de monstre
    // faire un CCArray de tower avec pour size 104
    
    // boucle de jeu (update dans cocos2D) a adapter pou que ca tinne dans le update, basically all while will be if
    int level = 0;
    
    // when in update 
    while (level < 30 /* && life > 0*/) { // modify to a if in cocos and call endGame() and replace with gamelayer variable
        for (int i = 0; i < 15; i++) //  nombre arbitraire a adapter, creation de niveau
            MobFactory((mobType)level); //  stocker le retour dans le CCArray, mettre un delai entre chaque creation de mob., should be moved to next wave
        // add mob array empty condition empty to continue something like :
        // while (mobArray.lenght != 0)
          {
          // boucle de jeu
          }  
        level++; // call nextWave in gameLayer
        std::cout << "level " << level << " finished" << std::endl;
    }
    endGame();
}
