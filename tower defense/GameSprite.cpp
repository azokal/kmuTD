//
//  GameSprite.cpp
//  coco2d-x-2.0.4-project
//
//  Created by game04 on 13. 9. 17..
//
//

#include "GameSprite.h"

GameSprite::GameSprite(void){ _vector = ccp(0,0);
}
GameSprite::~GameSprite(void){
}
GameSprite* GameSprite::gameSpriteWithFile(const char * pszFileName) {
    GameSprite * sprite = new GameSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
        CC_SAFE_DELETE(sprite);
        return NULL;
}
void GameSprite::setPosition(const CCPoint& pos) { CCSprite::setPosition(pos);
        if (!_nextPosition.equals(pos)) {
            _nextPosition = pos;
        }
    }