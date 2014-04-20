//
//  GameEndLayer.h
//  SaveHostage
//
//  Created by 郭 晨 on 4/8/14.
//
//

#ifndef __SaveHostage__GameEndLayer__
#define __SaveHostage__GameEndLayer__

class GameLayer;

#include "cocos2d.h"

USING_NS_CC;
class GameEndLayer : public cocos2d::Layer{
public:
    GameEndLayer();
    ~GameEndLayer();
    virtual bool init();
/*    void initMenu();
    void initVoiceButton();
    void initLevelButtons();*/
    CREATE_FUNC(GameEndLayer);
    
    void setGameEndLayerType (int type);
    void restartButtonPressed(Object* pSender);
    void settingButtonPressed(Object* pSender);
    void initMenu();
    void setParentGameLayer(GameLayer* parent);

private:
    int layerType;
    Sprite* bgSprite;
    GameLayer* parentLayer;
};


#endif /* defined(__SaveHostage__GameEndLayer__) */
