#include "MyScene.h"


MyScene::MyScene()
{

}

MyScene::~MyScene()
{}

bool MyScene::init() {
    bool ret = false;
    CCLOG("MyScene::init");
    do {
        CC_BREAK_IF(!Scene::init());


        _gameLayer = GameLayer::create();
        _optionLayer = OptionLayer::create();

        _optionLayer->setDelegator(_gameLayer);

        CCLOG("MyScene::init 1");
        this->addChild(_gameLayer, 1);
        CCLOG("MyScene::init 2");
        this->addChild(_optionLayer, 2);
        ret = true;
    } while(0);
    return ret;
}
