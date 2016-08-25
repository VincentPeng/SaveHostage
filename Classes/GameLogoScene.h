//
//  GameLogoScene.h
//  SaveHostage
//
//  Created by Chen Guo on 4/6/14.
//
//

#ifndef __SaveHostage__GameLogoScene__
#define __SaveHostage__GameLogoScene__

#include "cocos2d.h"
#include "GameScene.h"
#include "PreGameScene.h"
#include "EnumUtil.h"

USING_NS_CC;

class GameLogoScene : public cocos2d::Scene {
private:
public:
    GameLogoScene();
    ~GameLogoScene();
    virtual bool init();
    CREATE_FUNC(GameLogoScene);
    void loadGameScene(float dt);
};

#endif /* defined(__SaveHostage__GameLogoScene__) */
