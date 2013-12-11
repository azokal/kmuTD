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
    _toConstruct = CHAOS;
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
    this->addChild(_text);
    
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

void GameLayer::createMob( CCTime delta ) {
    static int countMob;
    printf("canard\n");
    Mob *m = MobFactory((mobType)_level);
    _mobs->addObject(MobFactory((mobType)_level));
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
                printf("x = %d y = %d\n", x, y);
                //MODIF !!!! TIM BLABLABLA JJIMDAK
            }
            else {
                if (tap.x > 32 * 9 - 16 && tap.x < 32 * 10 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == NORMAL)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = NORMAL;
                }
                if (tap.x > 32 * 11 - 16 && tap.x < 32 * 12 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == DARK)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = DARK;
                }
                if (tap.x > 32 * 13 - 16 && tap.x < 32 * 14 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == LIGHT)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = LIGHT;
                }
                if (tap.x > 32 * 15 - 16 && tap.x < 32 * 16 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == EARTH)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = EARTH;
                }
                if (tap.x > 32 * 17 - 16 && tap.x < 32 * 18 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == FIRE)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = FIRE;
                }
                if (tap.x > 32 * 19 - 16 && tap.x < 32 * 20 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == NATURE)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = NATURE;
                }
                if (tap.x > 32 * 21 - 16 && tap.x < 32 * 22 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    if (_toConstruct == WATER)
                        _toConstruct = CHAOS;
                    else
                        _toConstruct = WATER;
                }
                if (tap.x > 32 * 23 - 16 && tap.x < 32 * 24 - 16 && tap.y < _screenSize.height - 32 * 22 && tap.y > _screenSize.height - 32 * 23) {
                    /* if (_toConstruct == NORMAL)
                     _toConstruct = CHAOS;
                     else
                     _toConstruct = NORMAL;*/
                }
            }
			_lastPosTouch = tap;
		}
	}
    if (_began == false) {
        if (_isEndGame == true) {
            _bullets->autorelease();
            
            _bullets = CCArray::createWithCapacity(50);
            _bullets->retain();
        }
        _level = 0;
        _life = 50;
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

void GameLayer::update (float dt) {
    if (_began == false) {
        return;
    }

    if (_level > 30 || _life <= 0) // end of game
        endGame();
        
        // les movement et tir a appeller ici
        
        if (_mobs->count() == 0 && _isCompleteWave == true)
            nextWave();
}

void GameLayer::winLife() {
    _life++;
}

void GameLayer::endGame() {
    _isEndGame = true;
    _began = false;
    // re-init level, life, money
    // clean all board
    if (_life > 0) {
        // win message
    } else {
        // loose message
    }
}