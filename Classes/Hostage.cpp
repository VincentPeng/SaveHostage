#include "Hostage.h"
#include "ImageHelper.h"
#include "AppDef.h"

Hostage::Hostage() {}

Hostage::~Hostage() {}

bool Hostage::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Sprite::initWithFile("hostageset.png"));
        this->setMyHero(NULL);
        clock = 0;
        totalClocksNeeded = 50;
        Sprite* timerSprite = Sprite::create("progress.png");
        saveProgressTimer = ProgressTimer::create(timerSprite);
        saveProgressTimer->setType(ProgressTimer::Type::RADIAL);
        saveProgressTimer->setReverseProgress(true);
        saveProgressTimer->setPercentage(100);
        hideProgressTimer();
        ret = true;
    } while(0);
    return ret;
}

void Hostage::reset()
{
    clock = 0;
    saveProgressTimer->setPercentage(100);
    hideProgressTimer();
    setMyHero(NULL);
    direction = DOWN;
    nextDirection = direction;
    setTexture("hostageset.png");
    setTextureRect(ImageHelper::sharedImageHelper()->getWalkAnimationsRects()[DOWN][1]);
}

void Hostage::setMyHero(Hero* hero)
{
    myHero = hero;
}

void Hostage::setNextPoint(Point nextp)
{
    nextPosition = nextp;
}

void Hostage::setNextDirection(Direction nDirection)
{
    nextDirection = nDirection;
}

void Hostage::setTotalClocksNeeded(int clocknum)
{
    totalClocksNeeded = clocknum;
}

int Hostage::getTotalClocksNeeded()
{
    return totalClocksNeeded;
}

void Hostage::showProgressTimer()
{
//    saveProgressTimer->setPercentage(100.0f);
    saveProgressTimer->setVisible(true);
}

void Hostage::hideProgressTimer()
{
    saveProgressTimer->setPercentage(100.0f);
    saveProgressTimer->setVisible(false);
}

void Hostage::setClockPassed(int clocknum)
{
    float remainedProgress = (float)(totalClocksNeeded - clocknum) / (float)totalClocksNeeded;
    saveProgressTimer->setPercentage(remainedProgress * 100);
    if (remainedProgress == 0.0) {
        saveProgressTimer->setVisible(false);
    }
}

void Hostage::doAction() {
//    CCLOG("Hostage::doAction");
    if (myHero) {
        followHero();
    }
}

bool Hostage::isSaved()
{
    return myHero == NULL ? false:true;
}

Direction Hostage::directionP2P(cocos2d::Point pold, cocos2d::Point pnew)
{
    float dx = pnew.x - pold.x, dy = pnew.y - pold.y;
    if (dx == 0 && dy > 0) return UP;
    else if (dx == 0 && dy < 0) return DOWN;
    else if (dx > 0 && dy == 0) return RIGHT;
    else if (dx < 0 && dy == 0) return LEFT;
    else if (dx < 0 && dy < 0) return DL;
    else if (dx < 0 && dy > 0) return UL;
    else if (dx > 0 && dy > 0) return UR;
    else if (dx > 0 && dy < 0) return DR;
    
    return STOP;
}

void Hostage::followHero()
{
//    CCLOG("following the hero");
    if (clock % HOSTAGESPEED == 0) {
//        nextPosition = myHero->getPastPosition();
        if(nextPosition == this->getPosition())
            return;
        clock = 0;
        subpath.clear();
        cocos2d::Point currentPos = this->getPosition();
        direction = directionP2P(currentPos, nextPosition);
        for (int i = 1; i <= HOSTAGESPEED; i++) {
            Point pathPoint = ((nextPosition - currentPos) / HOSTAGESPEED) * i + currentPos;
            subpath.push_back(pathPoint);
        }
/*        MoveTo* moveto = MoveTo::create(0.2f, nextPosition);
        this->runAction(moveto);
        this->setPosition(nextPosition);*/
    }
    Point nextPoint = subpath[clock];
    setPosition (nextPoint);
    clock++;
    setTextureRect(ImageHelper::sharedImageHelper()->getWalkAnimationsRects()[direction][clock % 4]);
}

void Hostage::addSaveTimer(GameLayer* gameLayer) {
    gameLayer->addChild(saveProgressTimer,5);
    saveProgressTimer->setPosition(this->getPosition());
}
