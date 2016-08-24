//
//
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#include "GameEndLayer.h"

GameEndLayer::GameEndLayer() {}

GameEndLayer::~GameEndLayer() {}

void GameEndLayer::setParentGameLayer(GameLayer* parent) {
    parentLayer = parent;
}

void GameEndLayer::resumeButtonPressed(cocos2d::Object* pSender) {
    LOGV("resumeButtonPressed");
    Director::getInstance()->resume();
    removeFromParentAndCleanup(true);
}

void GameEndLayer::restartButtonPressed(cocos2d::Object* pSender) {
    LOGV("restartButtonPressed");
    parentLayer->restartGame();
    Director::getInstance()->resume();
    removeFromParentAndCleanup(true);
}

void GameEndLayer::settingButtonPressed(cocos2d::Object* pSender) {
    // LOGV("settingButtonPressed");
}

void GameEndLayer::initMenu() {
    LOGV("GameEndLayer initMenu");
    
    MenuItemImage* resumeItem = MenuItemImage::create(
                                                      PIC_RESUME, PIC_RESUME_PRESSED,
                                                      CC_CALLBACK_1(GameEndLayer::resumeButtonPressed, this));
    MenuItemImage* restartItem = MenuItemImage::create(
                                                       PIC_RESTART, PIC_RESTART,
                                                       CC_CALLBACK_1(GameEndLayer::restartButtonPressed, this));
    MenuItemImage* settingItem = MenuItemImage::create(
                                                       PIC_SETTINGS, PIC_SETTINGS,
                                                       CC_CALLBACK_1(GameEndLayer::restartButtonPressed, this));
    
    Menu* menu = Menu::create(resumeItem, restartItem, settingItem, NULL);
    menu->alignItemsVerticallyWithPadding(5.0f);
    
    this->addChild(menu, 5);
}

bool GameEndLayer::init() {
    bool ret = false;
    LOGV("Game End layer init");
    do {
        bgSprite = Sprite::create(PIC_GAMEOVER);
        bgSprite->setPosition(480.0f, 270.0f);
        addChild(bgSprite, 5);
        initMenu();
        ret = true;
    } while (0);
    return ret;
}

GameEndLayer* GameEndLayer::getLayerWithTexture(RenderTexture* rt) {
    GameEndLayer* layer = GameEndLayer::create();
    Sprite* sprite = rt->getSprite();
    Size sz = Director::getInstance()->getWinSize();
    sprite->setPosition(sz.width / 2, sz.height / 2);
    layer->addChild(sprite, 4);
    return layer;
}

void GameEndLayer::setGameEndLayerType(int type) {
    if (type == 0) {
        bgSprite->setTexture(PIC_GAMEOVER);
    } else {
        bgSprite->setTexture(PIC_GAMEWIN);
    }
}

Scene* GameEndLayer::getScene(RenderTexture* rt) {
    Sprite* sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
    Size winsize = Director::getInstance()->getWinSize();
    sprite->setPosition(winsize.width / 2, winsize.height / 2);
    sprite->setFlipY(true);
    
    Scene* retScene = Scene::create();
    
    GameEndLayer* endLayer = GameEndLayer::create();
    retScene->addChild(endLayer, 2);
    
    return retScene;
}
