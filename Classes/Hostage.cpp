#include "Hostage.h"

Hostage::Hostage() {}

Hostage::~Hostage() {}

bool Hostage::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Sprite::initWithFile("hostage.png"));
        ret = true;
    } while(0);
    return ret;
}

void Hostage::doAction() {
//    CCLOG("Hostage::doAction");
}
