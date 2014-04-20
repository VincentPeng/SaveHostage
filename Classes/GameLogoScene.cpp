//
//  GameLogoScene.cpp
//  SaveHostage
//
//  Created by 閮�鏅�on 4/6/14.
//
//

#include "GameLogoScene.h"
#include "MyScene.h"
#include "PreGameScene.h"

GameLogoScene::GameLogoScene()
{
    CCLOG("allocing game logo scene");
}

GameLogoScene::~GameLogoScene()
{
    
}

bool GameLogoScene::init() {
    bool ret = false;
    CCLOG("GameLogoScene::init");
    do {
        Sprite* bg = Sprite::create("gamelogobg.png");
        bg->setPosition(480.0f, 270.0f);
        this->schedule(schedule_selector(GameLogoScene::loadGameScene), 2.0f);
        addChild(bg);
        ret = true;
    } while(0);
    return ret;
}

void GameLogoScene::loadGameScene(float dt)
{
    auto scene = PreGameScene::create();
    Director::getInstance()->replaceScene(scene);
//    Director::getInstance()->pushScene(scene);
    
}
