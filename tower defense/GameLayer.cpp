#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameSprite.h"
#include "Map.h"
#include "Tower.h"
#include "Mob.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::~GameLayer() {
    //release CCArray
}

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    _isCompleteWave = true;
    srandom(getpid());
    _began = false;
    _isEndGame = false;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    _towerY = 0;
    _towerX = 0;
    _isTowerSelect = false;
    
  terrain = new Map();
    
    for (int i = 0; i < 32; i++) {
        for (int n = 0; n < 24; n++) {
            GameSprite *img = GameSprite::gameSpriteWithFile("sand.png");
            img->setPosition(ccp(i * 32 + 16, -16 + _screenSize.height - n * 32));
            this->addChild(img);
        }
    }
    for (int i = 0; i < 18; i++) {
        for (int n = 0; n < 14; n++) {
            if (terrain->_map[n][i] == NULL) {
                GameSprite *img = GameSprite::gameSpriteWithFile("grass_top.png");
                img->setPosition(ccp(32 * 9 + n * 32 + 16, -16 + _screenSize.height - 32 * 3 - i * 32));
                this->addChild(img);
            }
            else {
                GameSprite *img = GameSprite::gameSpriteWithFile("dirt.png");
                img->setPosition(ccp(32 * 9 + n * 32 + 16, -16 + _screenSize.height - 32 * 3 - i * 32));
                this->addChild(img);
            }
        }
    }
    _toConstruct = PURE;
    GameSprite *img = GameSprite::gameSpriteWithFile("compo.png");
    img->setPosition(ccp(32 * 9, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("dark.png");
    img->setPosition(ccp(32 * 11, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("light.png");
    img->setPosition(ccp(32 * 13, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("earth.png");
    img->setPosition(ccp(32 * 15, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("fire.png");
    img->setPosition(ccp(32 * 17, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("nature.png");
    img->setPosition(ccp(32 * 19, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("water.png");
    img->setPosition(ccp(32 * 21, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    img = GameSprite::gameSpriteWithFile("gold.png");
    img->setPosition(ccp(32 * 23, -16 + _screenSize.height - 32 * 22));
    this->addChild(img);
    
    _text = CCLabelTTF::create("Touch to Begin", "Arial", 60);
    _text->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    _text->setColor(ccc3(0,0,0));
    this->addChild(_text);
    
    _desc = CCLabelTTF::create("", "Arial", 30);
    _desc->setPosition(ccp(_screenSize.width * 0.85, _screenSize.height * 0.5));
    _desc->setColor(ccc3(0,0,0));
    this->addChild(_desc);
    
	_bullets = CCArray::createWithCapacity(50);
    _bullets->retain();
    
    this->schedule(schedule_selector(GameLayer::update));
	_lastPosTouch = CCPointZero;
    
    _mobs = CCArray::createWithCapacity(20);
    _towers = CCArray::createWithCapacity(104);
    _mobs->retain();
    _towers->retain();
    return true;
}

void GameLayer::looseLife(CCObject* sender) {
    _life--;
}

void GameLayer::createMob( CCTime delta ) {
    static int countMob;
    
    Mob *m = MobFactory((mobType)_level, this);
    _mobs->addObject(m);
    ++countMob;
    if (countMob == 15) {
        _isCompleteWave = true;
        countMob = 0;
    }
    this->addChild(m->_sprite);
}

void GameLayer::nextWave() {
    // load next wave

    this->schedule(schedule_selector( GameLayer::createMob ), 1.f, 14.f, 0.f);

    _isCompleteWave = false;
    
    _level += 1;
    if (_level != 0)
        _money += _money * 2 / 100;
}

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch* touch;
	CCPoint tap;
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch*) (*i);
        if(touch) {
			tap = touch->getLocation();
            if (tap.x > 32 * 9 && tap.x < 32 * 23 && tap.y < _screenSize.height - 32 * 3 && tap.y > _screenSize.height - 32 * 21) {
                int x = (tap.x - 32 * 9) / 32;
                int y = (-tap.y + 32 * 21) / 32;
                if (_toConstruct != PURE && this->terrain->_map[x][y] == NULL && _toConstruct != SELL) {
                    infoTower *s =  Tower::stat(_toConstruct);
                    if (s != NULL && s->price <= _money) {
                        _money -= s->price;
                        delete s;
                    } else
                        return ;
                    terrain->NewTower(_toConstruct, x, y);
                        _towers->addObject(this->terrain->_map[x][y]);
                        this->addChild(this->terrain->_map[x][y]->_sprite);
                } else if (this->terrain->_map[x][y] != NULL && this->terrain->_map[x][y] != this->terrain->_map[2][2]) {
                    printf("TOTO\n");
                    _isTowerSelect = true;
                    _towerY = y;
                    _towerX = x;
                } else if (_toConstruct == SELL) {
                    if (this->terrain->_map[x][y] != NULL) {
                        this->sellTower(x, y);
                    }
                }
            }
                if (tap.x > 32 * 9 - 16 && tap.x < 32 * 10 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    _isTowerSelect = false;
                    if (_toConstruct == BASIC_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = BASIC_L1;
                }
                if (tap.x > 32 * 11 - 16 && tap.x < 32 * 12 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                    if (_toConstruct == DARK_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = DARK_L1;
                }
                if (tap.x > 32 * 13 - 16 && tap.x < 32 * 14 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                    if (_toConstruct == LIGHT_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = LIGHT_L1;
                }
                if (tap.x > 32 * 15 - 16 && tap.x < 32 * 16 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect =false;
                    if (_toConstruct == EARTH_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = EARTH_L1;
                }
                if (tap.x > 32 * 17 - 16 && tap.x < 32 * 18 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                    if (_toConstruct == FIRE_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = FIRE_L1;
                }
                if (tap.x > 32 * 19 - 16 && tap.x < 32 * 20 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                    if (_toConstruct == NATURE_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = NATURE_L1;
                }
                if (tap.x > 32 * 21 - 16 && tap.x < 32 * 22 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                    if (_toConstruct == WATER_L1)
                        _toConstruct = PURE;
                    else
                        _toConstruct = WATER_L1;
                }
                if (tap.x > 32 * 23 - 16 && tap.x < 32 * 24 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                     _isTowerSelect = false;
                     if (_toConstruct == SELL)
                         _toConstruct = PURE;
                     else
                         _toConstruct = SELL;
                }
            }
			_lastPosTouch = tap;
		}
    if (_began == false) {
        if (_isEndGame == true) {
            _bullets->autorelease();
            
            _bullets = CCArray::createWithCapacity(50);
            _bullets->retain();
        }
        _level = 0;
        _life = 30;
        _money = 300;
        _text->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height - 60));
        
        
        _began = true;
    }
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch* touch;
    
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch*) (*i);
        if(touch) {
            
  		}
    }
}
void GameLayer::sellTower(int x, int y) {
    if (terrain->_map[x][y]->_type == NORMAL)
        _money += terrain->_map[x][y]->_price;
    else
        _money += terrain->_map[x][y]->_price * 0.8;
    delete terrain->_map[x][y];
    _towers->removeObject(terrain->_map[x][y]);
    terrain->_map[x][y] = NULL;
}

void GameLayer::upgrade(towerType type, int x, int y) {
    infoTower *s =  Tower::stat(_toConstruct);

    delete terrain->_map[x][y];
    if (s != NULL) {
        _money -= s->price;
        delete s;
    }
    terrain->NewTower(_toConstruct, x, y);
    _towers->addObject(this->terrain->_map[x][y]);
    this->addChild(this->terrain->_map[x][y]->_sprite);
}

void GameLayer::update (float dt) {
    if (_began == false) {
        return;
    }
    
    char tmp[1024];
    sprintf(tmp, "Gold: %d Life: %d Waves: %d/30", _money, _life, _level);
    _text->setString(tmp);
    
    if (_mobs->count() == 0 && _isCompleteWave == true)
        nextWave();
    
    if (_toConstruct != PURE && _toConstruct != SELL) {
        infoTower *i = Tower::stat(_toConstruct);
        std::string s = "";
        switch (i->type) {
            case LIGHT:
                s = "Light";
                break;
            case DARK:
                s = "Dark";
                break;
            case WATER:
                s = "Water";
                break;
            case FIRE:
                s = "Fire";
                break;
            case NATURE:
                s = "Nature";
                break;
            case EARTH:
                s = "Earth";
                break;
            case NORMAL:
                s = "Normal";
                break;
            case CHAOS:
                s = "Chaos";
                break;

        }
        sprintf(tmp, "Tower Info\nDamage: %d\nRange: %d\nType: %s\nPrice: %d", i->dmg, i->range, s.c_str(), i->price);
        _desc->setString(tmp);
    }
    else {
        sprintf(tmp, "");
        _desc->setString(tmp);
    }

    if (_isTowerSelect) {
        if (terrain->_map[_towerX][_towerY]->upgradeList->size() != 0) {
        towerType t = terrain->_map[_towerX][_towerY]->upgradeList->at(0);
        infoTower *i = Tower::stat(t);
        std::string s = "";
    switch (i->type) {
        case LIGHT:
            s = "Light";
            break;
        case DARK:
            s = "Dark";
            break;
        case WATER:
            s = "Water";
            break;
        case FIRE:
            s = "Fire";
            break;
        case NATURE:
            s = "Nature";
            break;
        case EARTH:
            s = "Earth";
            break;
        case NORMAL:
            s = "Normal";
            break;
        case CHAOS:
            s = "Chaos";
            break;
            
    }
    sprintf(tmp, "Tower upgrade info\nDamage: %d\nRange: %d\nType: %s\nPrice: %d", i->dmg, i->range, s.c_str(), i->price);
    _desc->setString(tmp);
        }
}
    if (_level > 30 || _life <= 0) // end of game
        endGame();

}

void GameLayer::winLife() {
    _life++;
}

void GameLayer::endGame() {
    _isEndGame = true;
    _began = false;
    // re-init level, life, money
    // clean all board
     _text->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    char tmp[1024];
    if (_life > 0) {
        sprintf(tmp, "You win!");
        _text->setString(tmp);
    } else {
        sprintf(tmp, "You lost at wave %d!", _level);
        _text->setString(tmp);
    }
    for (int x = 0; x < 14; x++) {
        for (int y = 0; y < 18; y++) {
            if (terrain->_map[x][y] != NULL && terrain->_map[x][y] != terrain->_map[2][2]) {
                sellTower(x, y);
            }
        }
    }
    CCObject *r;
    CCARRAY_FOREACH(_mobs, r) {
        delete r;
    }
    _mobs->removeAllObjects();
}