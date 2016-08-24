//
//  GameLogoScene.cpp
//  SaveHostage
//
//  Created by Ke Peng 4/6/14.
//
//

#include "GameLogoScene.h"



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
//        bg->setPosition(480.0f, 270.0f);
        bg->setPosition(WIDTH_CENTER, HEIGHT_CENTER);
        this->schedule(schedule_selector(GameLogoScene::loadGameScene), 2.0f);
        addChild(bg);
        ret = true;
    } while(0);
    return ret;
}

void GameLogoScene::loadGameScene(float dt)
{
    auto s = PreGameScene::create();
    auto scene = TransitionFade::create(1.5,s,Color3B::WHITE);
    Director::getInstance()->replaceScene(scene);
    
}
