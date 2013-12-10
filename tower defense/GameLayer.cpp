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
    srandom(getpid());
    _began = false;
    _isEndGame = false;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    
    Map *terrain = new Map();
    
    for (int i = 0; i < 32; i++) {
        for (int n = 0; n < 24; n++) {
            GameSprite *img = GameSprite::gameSpriteWithFile("sand.png");
            img->setPosition(ccp(16+ i * 32, -16 + _screenSize.height - n * 32));
            this->addChild(img);
        }
    }
    
    terrain->NewTower(BASIC_L1, 0, 0);
    for (int i = 0; i < 18; i++) {
        for (int n = 0; n < 14; n++) {
            if (terrain->_map[n][i] == NULL) {
                GameSprite *img = GameSprite::gameSpriteWithFile("grass_top.png");
                img->setPosition(ccp(16 + 32 * 9 + n * 32, -16 + _screenSize.height - 32 * 3 - i * 32));
                this->addChild(img);
            }
            else {
                GameSprite *img = GameSprite::gameSpriteWithFile("dirt.png");
                img->setPosition(ccp(16 + 32 * 9 + n * 32, -16 + _screenSize.height - 32 * 3 - i * 32));
                this->addChild(img);
            }
        }
        std::cout << std::endl;
    }
    
    _text = CCLabelTTF::create("Touch to Begin", "Arial", 60);
    _text->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(_text);
    
	_bullets = CCArray::createWithCapacity(50);
    _bullets->retain();
    
    this->schedule(schedule_selector(GameLayer::update));
	_lastPosTouch = CCPointZero;
    
    // faire un CCArray de monstre
    // faire un CCArray de tower avec pour size 104
    
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