#ifndef PkGc_cocos2d_saveHostage_MYSCENE_H_
#define PkGc_cocos2d_saveHostage_MYSCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "BgLayer.h"

class MyScene : public cocos2d::Scene
{
public:
    MyScene();
    ~MyScene();
    virtual bool init();
    CREATE_FUNC(MyScene);

    CC_SYNTHESIZE(BgLayer*, _bgLayer, BgLayer);
    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);
};


#endif  // end of PkGc_cocos2d_saveHostage_MYSCENE_H_
