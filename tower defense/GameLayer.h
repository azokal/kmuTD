#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include <map>
#include "cocos2d.h"
#include "GameSprite.h"

class Map;

using namespace cocos2d;

typedef enum {
    LIGHT,
    DARK,
    WATER,
    FIRE,
    NATURE,
    EARTH,
    NORMAL,
    CHAOS
} element;

typedef enum {
    BASIC_L1,
    BASIC_L2,
    BASIC_L3,
    FIRE_L1,
    FIRE_L2,
    FIRE_L3,
    FIRE_L4,
    FIRE_L5,
    NATURE_L1,
    NATURE_L2,
    NATURE_L3,
    NATURE_L4,
    NATURE_L5,
    EARTH_L1,
    EARTH_L2,
    EARTH_L3,
    EARTH_L4,
    EARTH_L5,
    WATER_L1,
    WATER_L2,
    WATER_L3,
    WATER_L4,
    WATER_L5,
    LIGHT_L1,
    LIGHT_L2,
    LIGHT_L3,
    LIGHT_L4,
    LIGHT_L5,
    DARK_L1,
    DARK_L2,
    DARK_L3,
    DARK_L4,
    DARK_L5,
    PURE,
    SELL
} towerType;

class GameLayer : public cocos2d::CCLayer
{
    bool _began;
    int _life;
    int _level;
    CCArray *_towers;
    CCSize _screenSize;
	CCPoint _lastPosTouch;
    bool _isEndGame;
    bool _isCompleteWave;
    CCLabelTTF *_text;
    CCAction *_action;
    towerType _toConstruct;
    
    void endGame();
    void winLife();
public:
    int _money;
    Map *terrain;
    CCArray *_bullets;
    ~GameLayer();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    void upgrade(towerType type, int x, int y);
    void update(float dt);
    void sellTower(int x, int y);
    void nextWave();
    void createMob( CCTime delta );
    void looseLife(CCObject* sender);
};

#endif // __GAMELAYER_H__
