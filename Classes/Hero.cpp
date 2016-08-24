//
//
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#include "Hero.h"

Hero::Hero() {}

Hero::~Hero() {}

bool Hero::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Sprite::initWithFile("heroset.png"));
        
        saving_clock = 0;
        health = 100;
        current_hostage = NULL;
        speedChange = false;
        speed = HEROSPEED_M;
        setDirection(DOWN);
        nextDirection = direction;
        
        ret = true;
    } while (0);
    return ret;
}

void Hero::reset() {
    clock = 0;
    saving_clock = 0;
    health = 100;
    current_hostage = NULL;
    speedChange = false;
    direction = DOWN;
    nextDirection = direction;
    savedHostages.clear();
    pastPoints.clear();
    pastDirections.clear();
    subpath.clear();
    setTexture("heroset.png");
    setTextureRect(
                   ImageHelper::sharedImageHelper()->getWalkAnimationsRects()[DOWN][1]);
}

void Hero::setHealth(int health) { this->health = health; }

int Hero::getHealth() { return health; }

void Hero::setSpeed(int s) {
    if (s <= 0) this->speed = 7;
    this->speed = s;
}

void Hero::setDirection(Direction d) { this->direction = d; }

void Hero::setNextDirection(Direction nDirection) {
    this->nextDirection = nDirection;
}

void Hero::setCurrentNode(cocos2d::Point pos) { this->currentNode = pos; }

void Hero::setNextNode(cocos2d::Point nxtPos) { this->nextNode = nxtPos; }

void Hero::setNextPosition(cocos2d::Point nxtPos) {
    this->nextPosition = nxtPos;
}

void Hero::setCurrentHostage(Hostage *host) { this->current_hostage = host; }

void Hero::setTargetSavingClocks(int target) { target_saving_clocks = target; }

void Hero::attackedBy(int power) {
    health -= power;
    /*    healthProgressTimer->setPercentage(health);
     if (health < 0) {
     setTexture("mariodown.jpg");
     healthProgressTimer->setVisible(false);
     }*/
}

bool Hero::isDead() {
    if (health < 0) {
        return true;
    }
    return false;
}

void Hero::incrementSavingClock() {
    saving_clock++;
    if (saving_clock == target_saving_clocks) {
        pastPosition = current_hostage->getPosition();
        current_hostage->setMyHero(this);
        current_hostage->setNextPoint(pastPoints[4 - savedHostages.size()]);
        savedHostages.push_back(current_hostage);
    }
}

void Hero::zeroSavingClock() { saving_clock = 0; }

int Hero::getSavingClock() { return saving_clock; }

cocos2d::Point Hero::getCurrentNode() { return currentNode; }

Hostage *Hero::getCurrentHostage() { return current_hostage; }

Point Hero::getPastPosition() { return pastPosition; }

//  when clock % speed == 0
//  consititude a sub path

void Hero::updateHostagesPosition() {
    pastPosition = this->getPosition();
    pastPoints.push_back(pastPosition);
    pastDirections.push_back(direction);
    if (pastPoints.size() > 5) {
        pastPoints.pop_front();
    }
    for (int i = 0; i < savedHostages.size(); i++) {
        savedHostages[i]->setNextPoint(pastPoints[4 - i]);
        savedHostages[i]->setNextDirection(pastDirections[4 - i]);
    }
}

void Hero::doAction() {
    //    CCLOG("Hero::doAction");
    if (clock % this->speed == 0) {
        if (currentNode == nextNode) {
            return;
        }
        updateHostagesPosition();
        currentNode = nextNode;
        direction = nextDirection;
        clock = 0;
        subpath.clear();
        if (speedChange == true) {
            if (this->speed == HEROSPEED_M) {
                this->speed = HEROSPEED_H;
            } else if (this->speed == HEROSPEED_H) {
                this->speed = HEROSPEED_M;
            }
            speedChange = false;
        }
        cocos2d::Point currentPos = this->getPosition();
        for (int i = 1; i <= this->speed; i++) {
            Point pathPoint =
            ((nextPosition - currentPos) / this->speed) * i + currentPos;
            subpath.push_back(pathPoint);
        }
        /*        MoveTo* moveto = MoveTo::create(0.2f, nextPosition);
         this->runAction(moveto);
         this->setPosition(nextPosition);*/
    }
    Point nextPoint = subpath[clock];
    setPosition(nextPoint);
    setTextureRect(ImageHelper::sharedImageHelper()
                   ->getWalkAnimationsRects()[direction][clock % 4]);
    clock++;
}

Buff Hero::getCurBuff() { return curBuff; }

void Hero::setCurBuff(Buff buff) {
    this->curBuff = buff;
    this->removeChildByTag(100);
    Sprite *b;
    switch (buff) {
        case Buff::SPEED:
            b = Sprite::create("buff_speed.png");
            //        this->highSpeed();
            speedChange = true;
            this->bufftime = BUFFTIME;
            this->addChild(b, 1, 100);
            b->setPosition(Point(1 * BLKWIDTH, 2.5 * BLKWIDTH));
            speedChange = true;
            break;
        case Buff::INVISIBLE:
            b = Sprite::create("buff_invisible.png");
            this->bufftime = BUFFTIME;
            this->addChild(b, 1, 100);
            b->setPosition(Point(1 * BLKWIDTH, 2.5 * BLKWIDTH));
            break;
        case Buff::UNBREAK:
            b = Sprite::create("buff_unbreak.png");
            this->bufftime = BUFFTIME;
            this->addChild(b, 1, 100);
            b->setPosition(Point(1 * BLKWIDTH, 2.5 * BLKWIDTH));
            break;
        case Buff::NONE:
            this->normalSpeed();
            this->bufftime = 0;
            break;
        default:
            break;
    }
}

void Hero::normalSpeed() {
    if (this->speed != HEROSPEED_M) {
        speedChange = true;
    }
    //    setSpeed(HEROSPEED_M);
}

void Hero::highSpeed() { setSpeed(HEROSPEED_H); }

bool Hero::ifUnbreak() { return curBuff == Buff::UNBREAK; }

bool Hero::ifInvisible() { return curBuff == Buff::INVISIBLE; }

void Hero::buffCountdown() { this->bufftime--; }

int Hero::getBufftime() { return bufftime; }

void Hero::setBufftime(int bufftime) { this->bufftime = bufftime; }
