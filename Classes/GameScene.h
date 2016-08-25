#ifndef PkGc_cocos2d_saveHostage_MYSCENE_H_
#define PkGc_cocos2d_saveHostage_MYSCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "EnumUtil.h"

class GameScene : public cocos2d::Scene {
public:
    GameScene();
    ~GameScene();
    virtual bool init();
    void loadMusic();
    CREATE_FUNC(GameScene);
    
    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    static bool musicLoaded;
};

#endif  // end of PkGc_cocos2d_saveHostage_MYSCENE_H_
