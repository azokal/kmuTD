//
//  Tower.cpp
//  tower defense
//
//  Created by game04 on 13. 12. 3..
//
//

#include "Tower.h"
#include "Map.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

 Tower::~Tower() {
     _sprite->setVisible(false);
     _sprite->stopAllActions();
     _sprite->release();
 }

infoTower *Tower::stat(towerType type) {
   
switch (type) {
    case FIRE_L1: return new infoTower(24, 50, 57, FIRE);
    case FIRE_L2: return new infoTower(120, 175, 57, FIRE);
    case FIRE_L3: return new infoTower(600, 625, 57, FIRE);
    case FIRE_L4: return new infoTower(3000, 2125, 57, FIRE);
    case FIRE_L5: return new infoTower(45000, 11225, 57, FIRE);
    case NATURE_L1: return new infoTower(80, 50, 80, NATURE);
    case NATURE_L2: return new infoTower(400, 175, 80, NATURE);
    case NATURE_L3: return new infoTower(2000, 625, 80, NATURE);
    case NATURE_L4: return new infoTower(10000, 2125, 80, NATURE);
    case NATURE_L5: return new infoTower(150000, 11225, 80, NATURE);
    case EARTH_L1: return new infoTower(100, 50, 70, EARTH);
    case EARTH_L2: return new infoTower(480, 175, 70, EARTH);
    case EARTH_L3: return new infoTower(2400, 625, 70, EARTH);
    case EARTH_L4: return new infoTower(12000, 2125, 70, EARTH);
    case EARTH_L5: return new infoTower(180000, 11225, 70, EARTH);
    case WATER_L1: return new infoTower(30, 50, 80, WATER);
    case WATER_L2: return new infoTower(180, 175, 80, WATER);
    case WATER_L3: return new infoTower(900, 625, 80, WATER);
    case WATER_L4: return new infoTower(4500, 2125, 80, WATER);
    case WATER_L5: return new infoTower(70000, 11225, 80, WATER);
    case LIGHT_L1: return new infoTower(57, 50, 170, LIGHT);
    case LIGHT_L2: return new infoTower(285, 175, 170, LIGHT);
    case LIGHT_L3: return new infoTower(1425, 625, 170, LIGHT);
    case LIGHT_L4: return new infoTower(7125, 2125, 170, LIGHT);
    case LIGHT_L5: return new infoTower(106875, 11225, 170, LIGHT);
    case DARK_L1: return new infoTower(157, 50, 128, DARK);
    case DARK_L2: return new infoTower(785, 175, 128, DARK);
    case DARK_L3: return new infoTower(3925, 625, 128, DARK);
    case   DARK_L4: return new infoTower(19625, 2125, 128, DARK);
    case DARK_L5: return new infoTower(294375, 11225, 128, DARK);
    default: return NULL;
    }
}

void Tower::shoot(CCArray *mobs) {
    pthread_mutex_lock(&m);
    CCObject *r;
    float closest = 0;
    if (_target == NULL) {
        CCARRAY_FOREACH(mobs, r) {
            float centerDistance = ccpDistance(((Mob*)r)->_sprite->getPosition(), _sprite->getPosition());
            if ((closest == 0 || closest > centerDistance) && centerDistance <= 18.0 + _range) {
                closest = centerDistance;
                _target = ((Mob*)r);
            }
        }
    } else {
        if (_mobs->containsObject(_target)) {
            float centerDistance = ccpDistance(_target->_sprite->getPosition(), _sprite->getPosition());
            if (centerDistance > 18.0 + _range)
                _target = NULL;
        }
    }
    if (_target != NULL) {
        if (_mobs->containsObject(_target)) {
            bool t = _target->looseLife(_dmg, _type);
            if (t == true) {
                if (_mobs->containsObject(_target)) {
                    _mobs->removeObject(_target);
                    delete _target;
                }
                _target = NULL;
            }
        } else {
            _target = NULL;
        }
    }
    pthread_mutex_unlock(&m);
}

Tower *TowerFactory(towerType type, int x, int y) {

    switch (type) {
        // three basic tower
        case FIRE_L1: return new Tower(24, 50, 57,  0.31, FIRE, "fire.png", x, y, new std::vector<towerType>(1, FIRE_L2));
        case FIRE_L2: return new Tower(120, 225, 57, 0.31, FIRE, "afire.png", x, y, new std::vector<towerType>(1, FIRE_L3));
        case FIRE_L3: return new Tower(600, 850, 57, 0.31, FIRE, "ffire.png", x, y, new std::vector<towerType>(1, FIRE_L4));
        case FIRE_L4: return new Tower(3000, 2975, 57, 0.31, FIRE, "rfire.png", x, y, new std::vector<towerType>(1, FIRE_L5));
        case FIRE_L5: return new Tower(45000, 14200, 57, 0.31, FIRE, "pfire.png", x, y, new std::vector<towerType>);
        case NATURE_L1: return new Tower(80, 50, 80,  0.66, NATURE, "nature.png", x, y, new std::vector<towerType>(1, NATURE_L2));
        case NATURE_L2: return new Tower(400, 225, 80,  0.66, NATURE, "anature.png", x, y, new std::vector<towerType>(1, NATURE_L3));
        case NATURE_L3: return new Tower(2000, 850, 80,  0.66, NATURE, "rnature.png", x, y, new std::vector<towerType>(1, NATURE_L4));
        case NATURE_L4: return new Tower(10000, 3000, 80,  0.66, NATURE, "fnature.png", x, y, new std::vector<towerType>(1, NATURE_L5));
        case NATURE_L5: return new Tower(150000, 14200, 80,  0.66, NATURE, "pnature.png", x, y, new std::vector<towerType>);
        case EARTH_L1: return new Tower(100, 50, 70,  1, EARTH, "earth.png", x, y, new std::vector<towerType>(1, EARTH_L2));
        case EARTH_L2: return new Tower(480, 225, 70,  1, EARTH, "aearth.png", x, y, new std::vector<towerType>(1, EARTH_L3));
        case EARTH_L3: return new Tower(2400, 850, 70,  1, EARTH, "rearth.png", x, y, new std::vector<towerType>(1, EARTH_L4));
        case EARTH_L4: return new Tower(12000, 2975, 70,  1, EARTH, "fearth.png", x, y, new std::vector<towerType>(1, EARTH_L5));
        case EARTH_L5: return new Tower(180000, 14200, 70,  1, EARTH, "pearth.png", x, y, new std::vector<towerType>);
        case WATER_L1: return new Tower(30, 50, 80,  0.31, WATER, "water.png", x, y, new std::vector<towerType>(1, WATER_L2));
        case WATER_L2: return new Tower(180, 225, 80,  0.31, WATER, "awater.png", x, y, new std::vector<towerType>(1, WATER_L3));
        case WATER_L3: return new Tower(900, 850, 80,  0.31, WATER, "rwater.png", x, y, new std::vector<towerType>(1, WATER_L4));
        case WATER_L4: return new Tower(4500, 2975, 80,  0.31, WATER, "fwater.png", x, y, new std::vector<towerType>(1, WATER_L5));
        case WATER_L5: return new Tower(70000, 14200, 80,  0.31, WATER, "pwater.png", x, y, new std::vector<towerType>);
        case LIGHT_L1: return new Tower(57, 50, 170,  0.66, LIGHT, "light.png", x, y, new std::vector<towerType>(1, LIGHT_L2));
        case LIGHT_L2: return new Tower(285, 225, 170,  0.66, LIGHT, "alight.png", x, y, new std::vector<towerType>(1, LIGHT_L3));
        case LIGHT_L3: return new Tower(1425, 850, 170,  0.66, LIGHT, "rlight.png", x, y, new std::vector<towerType>(1, LIGHT_L4));
        case LIGHT_L4: return new Tower(7125, 2975, 170,  0.66, LIGHT, "flight.png", x, y, new std::vector<towerType>(1, LIGHT_L5));
        case LIGHT_L5: return new Tower(106875, 14200, 170,  0.66, LIGHT, "plight.png", x, y, new std::vector<towerType>);
        case DARK_L1: return new Tower(157, 50, 128,  1.5, DARK, "dark.png", x, y, new std::vector<towerType>(1, DARK_L2));
        case DARK_L2: return new Tower(785, 225, 128,  1.5, DARK, "adark.png", x, y, new std::vector<towerType>(1, DARK_L3));
        case DARK_L3: return new Tower(3925, 850, 128,  1.5, DARK, "rdark.png", x, y,  new std::vector<towerType>(1, DARK_L4));
        case DARK_L4: return new Tower(19625, 2975, 128,  1.5, DARK, "fdark.png", x, y,  new std::vector<towerType>(1, DARK_L5));
        case DARK_L5: return new Tower(294375, 14200, 128,  1.5, DARK, "pdark.png", x, y,  new std::vector<towerType>);
        default: return NULL;
    }
}