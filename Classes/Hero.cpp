#include "Hero.h"

Hero::Hero()
{}

Hero::~Hero()
{}

bool Hero::init() {
    bool ret=false;
    do {
        CCLOG("Hero::init 1");
        CC_BREAK_IF(!Sprite::initWithFile("hero.png"));
        CCLOG("Hero::init 2");
        ret = true;
    } while(0);
    return ret;
}

void Hero::doAction() {
//    CCLOG("Hero::doAction");
}
