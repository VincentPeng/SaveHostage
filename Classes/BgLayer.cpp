#include "BgLayer.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;

BgLayer::BgLayer()
{
    CCLOG("i am here 3");}

BgLayer::~BgLayer()
{}

bool BgLayer::init() {
    bool ret=false;
    CCLOG("i am here 2");
    do {
        CC_BREAK_IF(!Layer::init());

        //bgLayer
        cocos2d::Node* node = SceneReader::getInstance()->createNodeWithSceneFile("RPGGame.json");
        this->addChild(node);
        CCLOG("i am here");
        ret = true;
    } while(0);

    return ret;
}
