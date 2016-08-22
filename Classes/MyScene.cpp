#include "MyScene.h"
#include "EnumUtil.h"

int MyScene::musicLoaded = false;

MyScene::MyScene() {

}

MyScene::~MyScene() {
}

bool MyScene::init() {
    bool ret = false;
    CCLOG("MyScene::init");
    do {
        CC_BREAK_IF(!Scene::init());
        loadingResource();

        _gameLayer = GameLayer::create();
        CCLOG("MyScene::init 1");
        this->addChild(_gameLayer, 1);
        CCLOG("MyScene::init 2");
        ret = true;
    } while (0);
    return ret;
}

void MyScene::loadingResource() {
    if (!musicLoaded)
        loadingMusic();

}

void MyScene::loadingMusic() {
    musicLoaded = true;
    auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
    Audio->preloadEffect(MUSIC_GAMEOVER);
    Audio->preloadEffect(MUSIC_VICTORY);
    Audio->preloadEffect(EFCT_UNLOCK1);
    Audio->preloadEffect(EFCT_UNLOCK2);
    Audio->preloadEffect(EFCT_BTPRESS1);
    Audio->preloadEffect(EFCT_SHOOT);
    Audio->preloadEffect(EFCT_SPEED);
    Audio->preloadEffect(EFCT_UNBREAK);
    Audio->preloadEffect(EFCT_HEAL);
    Audio->preloadEffect(EFCT_INVISIBLE);
    Audio->playBackgroundMusic(MUSIC_BACKGROUND, true);
}
