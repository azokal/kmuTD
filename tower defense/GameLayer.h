#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;
class GameLayer : public cocos2d::CCLayer
{
    bool _began;
    int _life;
    int _level;
    CCArray *_towers;
    int     _money;
    CCSize _screenSize;
	CCPoint _lastPosTouch;
    bool _isEndGame;
    CCLabelTTF *_text;
    CCAction *_action;
    
    void endGame();
    void winLife();
public:
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
    void update (float dt);
    void nextWave();
};

#endif // __GAMELAYER_H__
