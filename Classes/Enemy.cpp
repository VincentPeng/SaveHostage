#include "enemy.h"
#define BLOCK 30

Enemy::Enemy() {}

Enemy::~Enemy() {}

bool Enemy::init() {
    bool ret = false;
    do {
        CCLOG("Enemy::init 1");
        CC_BREAK_IF(!Sprite::initWithFile("enemy.png"));
        CCLOG("Enemy::init 2");
        setSpeed(7);
        epath.push_back(Point(BLOCK*5-BLOCK/2,BLOCK*14-BLOCK/2));
        epath.push_back(Point(BLOCK*6-BLOCK/2,BLOCK*15-BLOCK/2));
        epath.push_back(Point(BLOCK*7-BLOCK/2,BLOCK*16-BLOCK/2));
        epath.push_back(Point(BLOCK*8-BLOCK/2,BLOCK*15-BLOCK/2));
        epath.push_back(Point(BLOCK*9-BLOCK/2,BLOCK*14-BLOCK/2));
        epath.push_back(Point(BLOCK*10-BLOCK/2,BLOCK*13-BLOCK/2));

        epath.push_back(Point(BLOCK*9-BLOCK/2,BLOCK*13-BLOCK/2));
        epath.push_back(Point(BLOCK*8-BLOCK/2,BLOCK*13-BLOCK/2));
        epath.push_back(Point(BLOCK*7-BLOCK/2,BLOCK*13-BLOCK/2));
        epath.push_back(Point(BLOCK*6-BLOCK/2,BLOCK*13-BLOCK/2));
        epath.push_back(Point(BLOCK*5-BLOCK/2,BLOCK*13-BLOCK/2));

        ret = true;
    } while(0);
    return ret;
}

void Enemy::setSpeed(int s) {
    if (s <= 0)
        this->speed = 7;
    this->speed = s;
}

void Enemy::doAction() {
    // CCLOG("Enemy::doAction");
    clock++;
    if(clock % speed == 0) {
        //walk();
        clock=1;
    }
}

void Enemy::walk() {
    if(epath.empty())
        return;
    switch(curState) {
        case State::IDLE:
            hangAround();
            break;
        case State::ALERT:
            alerting();
            break;
        case State::LOST:
            break;
        case State::LOOKAROUND:
            break;
        case State::INSPECT:
            break;
    }



}

void Enemy::hangAround() {
    Point nextPoint;
    curIndex++;
    if (curIndex >= epath.size()) {
        curIndex = 0;
    }
    nextPoint = epath[curIndex];
    setPosition (nextPoint);
}

void Enemy::alerting() {

}

void Enemy::shoot() {

}
