//
//  GameLogoScene.h
//  SaveHostage
//
//  Created by 郭 晨 on 4/6/14.
//
//

#ifndef __SaveHostage__GameLogoScene__
#define __SaveHostage__GameLogoScene__

#include "cocos2d.h"

USING_NS_CC;

class GameLogoScene : public cocos2d::Scene
{
private:
    
    
public:
    
    GameLogoScene();
    ~GameLogoScene();
    virtual bool init();
    CREATE_FUNC(GameLogoScene);
    void loadGameScene(float dt);
};


#endif /* defined(__SaveHostage__GameLogoScene__) */
