//
//
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#include "GameScene.h"

bool GameScene::musicLoaded = false;

GameScene::GameScene() {}

GameScene::~GameScene() {}

bool GameScene::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Scene::init());
        loadResource();
        _gameLayer = GameLayer::create();
        
        // GameLayer will contain background, so should be at bottom
        this->addChild(_gameLayer, 1);
        ret = true;
    } while (0);
    return ret;
}

// Load resouces need for the scene
void GameScene::loadResource() {
    if (!musicLoaded) loadMusic();
}

// Load music
void GameScene::loadMusic() {
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
