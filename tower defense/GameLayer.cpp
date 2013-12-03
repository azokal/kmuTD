#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameSprite.h"
#include <stdio.h>
#include <stdlib.h>

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
    srandom(getpid());
    _began = false;
    _isEndGame = false;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    
    
    _text = CCLabelTTF::create("Touch to Begin", "Arial", 60);
    _text->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(_text);
    
	_bullets = CCArray::createWithCapacity(50);
    _bullets->retain();
    
    this->schedule(schedule_selector(GameLayer::update));
	_lastPosTouch = CCPointZero;
    return true;
}

void GameLayer::nextWave() {
    // load next wave
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
}

void GameLayer::winLife() {
    _life++;
}

void GameLayer::endGame() {
    if (_life > 0) {
        _life--;
    }
    if (_life > 0) {
        return;
    }
    _isEndGame = true;
    _began = false;
}