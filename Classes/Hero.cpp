#include "Hero.h"

Hero::Hero()
{}

Hero::~Hero()
{}

bool Hero::init() {
    CCLOG("gao0");
    bool ret=false;
    do {
        CCLOG("gao");
        CC_BREAK_IF(!Sprite::create("hero.png"));
        ret = true;
    } while(0);
    return ret;
}
