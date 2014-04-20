//
//  GameEndLayer.cpp
//  SaveHostage
//
//  Created by 閮�鏅�on 4/8/14.
//
//
#include "GameLayer.h"
#include "GameEndLayer.h"

GameEndLayer::GameEndLayer()
{
    
}

GameEndLayer::~GameEndLayer()
{
    
}

void GameEndLayer::setParentGameLayer(GameLayer *parent)
{
    parentLayer = parent;
}

void GameEndLayer::restartButtonPressed(cocos2d::Object *pSender)
{
    parentLayer -> restartGame();
    removeFromParentAndCleanup(true);
}

void GameEndLayer::settingButtonPressed(cocos2d::Object *pSender)
{
//    parentLayer -> removeChild(this);
}

void GameEndLayer::initMenu(){
    MenuItemImage* restartItem = MenuItemImage::create(PIC_RESTART, PIC_RESTART, CC_CALLBACK_1(GameEndLayer::restartButtonPressed, this));
    MenuItemImage* settingItem = MenuItemImage::create(PIC_SETTINGS, PIC_SETTINGS, CC_CALLBACK_1(GameEndLayer::restartButtonPressed, this));
    
    Menu* menu = Menu::create(restartItem,settingItem, NULL);
    menu->alignItemsHorizontallyWithPadding(80.0f);
    menu->setPosition(Point(480.0f, 200.0f));
    this->addChild(menu,5);
}



bool GameEndLayer::init()
{
    bool ret = false;
    CCLOG("Game End layer init");
    do {
//        setPosition(0.0f,0.0f);
//        setContentSize(Size(Point(640.0f, 360.0f)));
        bgSprite = Sprite::create(PIC_GAMEOVER);
        bgSprite->setPosition(480.0f, 270.0f);
        addChild(bgSprite,5);
        initMenu();
        ret = true;
    } while(0);
    return ret;
}

void GameEndLayer::setGameEndLayerType(int type)
{
    if (type == 0) {
        bgSprite->setTexture(PIC_GAMEOVER);
    } else{
        bgSprite->setTexture(PIC_GAMEWIN);
    }
}
