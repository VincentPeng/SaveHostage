
//
//  PreGameScene.cpp
//  SaveHostage
//
//  Created by Ke Peng on 4/6/14.
//
//

#include "PreGameScene.h"

PreGameScene::PreGameScene() {}

PreGameScene::~PreGameScene() {}

bool PreGameScene::init() {
    bool ret = false;
    // CCLOG("GameLogoScene::init");
    do {
        Sprite* bg = Sprite::create("pregamebg.png");
        bg->setPosition(WIDTH_CENTER, HEIGHT_CENTER);
        
        addChild(bg);
        
        auto startItem = MenuItemImage::create(
                                               PIC_PLAY, PIC_PLAY, CC_CALLBACK_1(PreGameScene::startPressed, this));
        
        auto aboutItem = MenuItemImage::create(
                                               PIC_ABOUT, PIC_ABOUT, CC_CALLBACK_1(PreGameScene::aboutPressed, this));
        Menu* menu = Menu::create(startItem, aboutItem, NULL);
        menu->alignItemsHorizontallyWithPadding(150.0);
        
        menu->setPosition(500.0f, 120.0f);
        this->addChild(menu);
        
        ret = true;
    } while (0);
    return ret;
}

void PreGameScene::startPressed(Object* pSender) {
    auto scene = MyScene::create();
    Director::getInstance()->replaceScene(scene);
}

void PreGameScene::aboutPressed(Object* pSender) {
    // TODO: Add about page
}
