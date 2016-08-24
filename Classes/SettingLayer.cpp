//
//  SettingLayer.cpp
//  SaveHostage
//
//  Created by Ke Peng on 4/7/14.
//
//

#include "SettingLayer.h"

SettingLayer::SettingLayer()
{
    
}


SettingLayer::~SettingLayer()
{
    
}


void SettingLayer::initMenu()
{
    
}


void SettingLayer::initVoiceButton()
{
    
}

void SettingLayer::levelChanged(cocos2d::Object *obj)
{
    
}

void SettingLayer::initLevelButtons()
{
    MenuItemImage* playImg = MenuItemImage::create(PIC_RESTART, PIC_RESTART);
    MenuItemImage* pauseImg = MenuItemImage::create(PIC_SETTINGS, PIC_SETTINGS);
    MenuItemToggle* tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::levelChanged,this), pauseImg, playImg,nullptr);
    //    tog->setSelectedIndex(GameLayer::game_level);
}

bool SettingLayer::init()
{
    bool ret = false;
    // CCLOG("Setting layer init");
    do {
        Sprite* bg = Sprite::create("gamelogobg.jpg");
        bg->setPosition(480.0f, 270.0f);
        addChild(bg);
        initMenu();
        initVoiceButton();
        initLevelButtons();
        ret = true;
    } while(0);
    return ret;
}
