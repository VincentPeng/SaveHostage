//
//  SettingLayer.h
//  SaveHostage
//
//  Created by Chen Guo on 4/7/14.
//
//

#ifndef __SaveHostage__SettingLayer__
#define __SaveHostage__SettingLayer__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;
class SettingLayer : public cocos2d::Layer {
public:
    SettingLayer();
    ~SettingLayer();
    virtual bool init();
    void initMenu();
    void initVoiceButton();
    void initLevelButtons();
    CREATE_FUNC(SettingLayer);
    
    void levelChanged(Object* obj);
    
private:
};

#endif /* defined(__SaveHostage__SettingLayer__) */
