
//
//  PreGameScene.cpp
//  SaveHostage
//
//  Created by 閮�鏅�on 4/6/14.
//
//

#include "PreGameScene.h"


PreGameScene::PreGameScene()
{
    
}

PreGameScene::~PreGameScene()
{
    
}

bool PreGameScene::init()
{
    bool ret = false;
    CCLOG("GameLogoScene::init");
    do {
        Sprite* bg = Sprite::create("pregamebg.png");
        bg->setPosition(WIDTH_CENTER, HEIGHT_CENTER);
        
//        this->schedule(schedule_selector(PreGameScene::loadGameScene), 2.0f);
        addChild(bg);
        
        auto startItem = MenuItemImage::create(
                                               "buttonPlay.png",
                                               "buttonPlay.png",
                                               CC_CALLBACK_1(PreGameScene::startPressed,this));
        
        auto aboutusItem = MenuItemImage::create(
                                               "buttonAbout.png",
                                               "buttonAbout.png",
                                               CC_CALLBACK_1(PreGameScene::aboutusPressed,this));
        Menu* menu = Menu::create(startItem,aboutusItem, NULL);
        menu->alignItemsHorizontallyWithPadding(150.0);
        
        menu->setPosition(500.0f, 120.0f);
        this->addChild(menu);
        
        ret = true;
    } while(0);
    return ret;
}

void PreGameScene::startPressed(Object* pSender)
{
    auto scene = MyScene::create();
    Director::getInstance()->replaceScene(scene);
}

void PreGameScene::aboutusPressed(Object* pSender)
{
    
}
