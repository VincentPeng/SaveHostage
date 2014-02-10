#include "GameLayer.h"

GameLayer::GameLayer() {

}

GameLayer::~GameLayer() {

}

bool GameLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Layer::init());

        return true;
    } while (0);
    return ret;
}
