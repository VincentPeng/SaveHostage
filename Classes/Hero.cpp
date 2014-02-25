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
        setSpeed(4);
        ret = true;
    } while(0);
    return ret;
}

void Hero::setSpeed(int s) {
    if(s<=0)
        this->speed = 7;
    this->speed = s;
}

void Hero::doAction() {
//    CCLOG("Hero::doAction");

}
