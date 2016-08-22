#ifndef PkGc_cocos2d_saveHostage_MYSCENE_H_
#define PkGc_cocos2d_saveHostage_MYSCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

class MyScene : public cocos2d::Scene
{
public:
    MyScene();
    ~MyScene();
    virtual bool init();
    void loadingResource();
    void loadingMusic();
    CREATE_FUNC(MyScene);

    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    static int musicLoaded;
};


#endif  // end of PkGc_cocos2d_saveHostage_MYSCENE_H_
