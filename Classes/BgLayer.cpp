//
//  BgLayer.cpp
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#include "BgLayer.h"

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
        
        cocos2d::Node* node =
        cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("RPGGame.json");
        this->addChild(node);
        ret = true;
    } while (0);
    
    return ret;
}
