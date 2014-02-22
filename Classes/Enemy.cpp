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

void Enemy::doAction() {
//    CCLOG("Enemy::doAction");
    walk();
}
IDLE, ALERT, LOST, LOOKAROUND, INSPECT
void Enemy::walk() {
    if(epath.empty())
        return;
    Point nextPoint;
    if(curState == State::IDLE) {
        curIndex++;
        if(curIndex>= epath.size()) {
            curIndex = 0;
        }
        nextPoint = epath[curIndex];
    }
    switch(curState) {
        case State::IDLE:
            hangAround();
            break;
        case State::ALERT:
            alerting();
            break;
        case State::ALERT:
            break;
        case State::ALERT:
            break;
        case State::ALERT:
            break;
    }


    setPosition(nextPoint);
}

void Enemy::shoot() {

}
