//
//  GameSprite.h
//  coco2d-x-2.0.4-project
//
//  Created by game04 on 13. 9. 17..
//
//

#ifndef __coco2d_x_2_0_4_project__GameSprite__
#define __coco2d_x_2_0_4_project__GameSprite__

#include "cocos2d.h"

using namespace cocos2d;
class GameSprite : public CCSprite {
public:
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
    GameSprite(void); ~GameSprite(void);
    static GameSprite* gameSpriteWithFile(const char * pszFileName);
    virtual void setPosition(const CCPoint& pos);
};

#endif /* defined(__coco2d_x_2_0_4_project__GameSprite__) */
