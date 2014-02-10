#include "MyScene.h"


MyScene::MyScene()
{

}

MyScene::~MyScene()
{}

bool MyScene::init() {
    bool ret = false;
    CCLOG("i am here 5");
    do {
        CC_BREAK_IF(!Scene::init());

        CCLOG("i am here 6");
        _bgLayer = (BgLayer*)BgLayer::create();
        _gameLayer = (GameLayer*)GameLayer::create();
        _optionLayer = (OptionLayer*)OptionLayer::create();

        this->addChild(_bgLayer, 0);
        this->addChild(_gameLayer, 1);
        this->addChild(_optionLayer, 2);
        ret = true;
    } while(0);
    return ret;
}
