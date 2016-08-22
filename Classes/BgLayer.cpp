
#include "BgLayer.h"
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;


BgLayer::BgLayer() {
}

BgLayer::~BgLayer() {
}

bool BgLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Layer::init());

        //bgLayer
        cocos2d::Node* node =
                cocostudio::SceneReader::getInstance()->createNodeWithSceneFile(
                        "RPGGame.json");
        this->addChild(node);
        CCLOG("i am here");
        ret = true;
    } while (0);

    return ret;
}
