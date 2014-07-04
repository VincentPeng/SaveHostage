//
//  PreGameScene.h
//  SaveHostage
//
//  Created by 郭 晨 on 4/6/14.
//
//

#ifndef __SaveHostage__PreGameScene__
#define __SaveHostage__PreGameScene__

#include "cocos2d.h"

USING_NS_CC;

class PreGameScene : public Scene
{
private:
    
    
public:
    
    PreGameScene();
    ~PreGameScene();
    virtual bool init();
    CREATE_FUNC(PreGameScene);
    void loadGameScene(float dt);
    
    void startPressed(Object* pSender);
    void aboutusPressed(Object* pSender);
};

#endif /* defined(__SaveHostage__PreGameScene__) */
