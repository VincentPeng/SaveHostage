//
//  GameLogoScene.cpp
//  SaveHostage
//
//  Created by Ke Peng 4/6/14.
//
//

#include "GameLogoScene.h"

GameLogoScene::GameLogoScene() {}

GameLogoScene::~GameLogoScene() {}

bool GameLogoScene::init() {
    bool ret = false;
    do {
        Sprite* bg = Sprite::create(PIC_LOGO);
        bg->setPosition(WIDTH_CENTER, HEIGHT_CENTER);
        
        // Load Start scene after x seconds
        this->schedule(schedule_selector(GameLogoScene::loadGameScene), 2.0f);
        addChild(bg);
        ret = true;
    } while (0);
    return ret;
}

void GameLogoScene::loadGameScene(float dt) {
    auto s = PreGameScene::create();
    
    // Add fade in effect before launching next scene
    auto scene = TransitionFade::create(1.5, s, Color3B::WHITE);
    Director::getInstance()->replaceScene(scene);
}
