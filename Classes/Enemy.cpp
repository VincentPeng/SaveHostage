#include "enemy.h"
#include <PathGenerator.h>
#include "AppDef.h"
#include "TileNode.h"
#include "EnumUtil.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "ImageHelper.h"
#define BLOCK 30

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

int Enemy::lookaround_clock = 3;

bool Enemy::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Sprite::initWithFile("enemyset.png"));
        ret = true;
    } while (0);
    return ret;
}

void Enemy::reset() {
    this->setGameLevel();
    curState = State::IDLE;
    clock = 0;
    sign = Sprite::create("state_idle.png");
    this->setSign(sign);
    setTexture("enemyset.png");
    curDirection = Direction::DOWN;
    setTextureRect(
            ImageHelper::sharedImageHelper()->getWalkAnimationsRects()[curDirection][1]);
}

int Enemy::getAtkRange() {
    return atkRange;
}

void Enemy::setAtkRange(int atkRange) {
    this->atkRange = atkRange;
}

int Enemy::getDamage() {
    return damage;
}

void Enemy::setDamage(int damage) {
    this->damage = damage;
}

int Enemy::getSpeed() {
    return speed;
}

void Enemy::setSpeed(int speed) {
    this->speed = speed;
}

int Enemy::getVisionRange() {
    return visionRange;
}

void Enemy::setVisionRange(int visionRange) {
    this->visionRange = visionRange;
}

void Enemy::setPath(vector<Point> newpath) {
    this->epath = newpath;
}

void Enemy::setLoopRoute(vector<vector<Point>> route) {
    this->loopRoute = route;
}

void Enemy::doAction() {
    clock++;
    if (clock % speed != 0)
        return;
    clock = 0;
    if (curState == State::ATTACK) {
        shoot();
    }
    walk();
}

Direction Enemy::directionP2P(cocos2d::Point pold, cocos2d::Point pnew) {
    float dx = pnew.x - pold.x, dy = pnew.y - pold.y;
    if (dx == 0 && dy > 0)
        return UP;
    else if (dx == 0 && dy < 0)
        return DOWN;
    else if (dx > 0 && dy == 0)
        return RIGHT;
    else if (dx < 0 && dy == 0)
        return LEFT;
    else if (dx < 0 && dy < 0)
        return DL;
    else if (dx < 0 && dy > 0)
        return UL;
    else if (dx > 0 && dy > 0)
        return UR;
    else if (dx > 0 && dy < 0)
        return DR;

    return STOP;
}

// walk based on epath variable
void Enemy::walk() {
    // IDLE will loop the path
    if (curState == State::IDLE) {
        if (curIndex >= epath.size()) {
            curIndex = 0;
            routeIndex++;
            routeIndex %= loopRoute.size();
            epath = loopRoute[routeIndex];
        }
    } else if (epath.empty() || curIndex >= epath.size())
        return;

    /*set direction*/

    if (curIndex + 1 < epath.size()) {
        curDirection = directionP2P(epath[curIndex], epath[curIndex + 1]);
        if (curDirection != STOP) {
            setTextureRect(
                    ImageHelper::sharedImageHelper()->getWalkAnimationsRects()[curDirection][curIndex
                            % 4]);
        }
    }

    FiniteTimeAction* actionMove = MoveTo::create((float) 1 / FPS * getSpeed(),
            epath[curIndex++]);
    runAction(Sequence::create(actionMove, NULL));

}

State Enemy::getState() {
    return curState;
}

void Enemy::setState(State state) {
    curState = state;
}

void Enemy::takeAction() {
    curIndex = 0;
    if (epath.size() > 1) {
        curDirection = directionP2P(epath[curIndex], epath[curIndex + 1]);
    } else if (curState == State::ALERT || curState == State::ATTACK) {
        curDirection = directionP2P(getPosition(), target->getPosition());
    }
}

void Enemy::hangAround() {

}

void Enemy::alerting() {

}

void Enemy::shoot() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(EFCT_SHOOT);
    this->target->attackedBy(getDamage());
}

void Enemy::toMissingPoint() {

}

void Enemy::setSign(Sprite* sign) {
    this->removeAllChildren();
    this->addChild(sign);
    sign->setPosition(Point(1 * BLKWIDTH, 2.5 * BLKWIDTH));
}

bool Enemy::ifStoped() {

    return curIndex >= epath.size();
}

void Enemy::initialIdleMove() {
    int size = loopRoute.size();
    routeIndex = 0;
    curIndex = 0;
    setPath(loopRoute[routeIndex]);
}

void Enemy::idleMoveFrom(int index) {
    routeIndex = index;
    curIndex = 0;
    setPath(loopRoute[routeIndex]);
}

bool Enemy::canSee(Hero* ob) {
    if (!ob->ifInvisible()
            && distance(this->getPosition(), ob->getPosition()) <= visionRange
            && ifVisibleAngle(ob->getPosition())) {
        return true;
    }
    return false;
}

bool Enemy::canAttack(Hero* ob) {
    if (!ob->ifUnbreak() && !ob->ifInvisible()
            && distance(this->getPosition(), ob->getPosition()) <= atkRange) {
        return true;
    }
    return false;
}

int Enemy::getNormalSpeed() {
    return normalSpeed;
}

void Enemy::setNormalSpeed(int normalSpeed) {
    this->normalSpeed = normalSpeed;
}

void Enemy::useNormalSpeed() {
    this->speed = normalSpeed;
}

void Enemy::useHighSpeed() {
    this->speed = normalSpeed * 0.5;
}

int Enemy::distance(Point a, Point b) {
    int x = (int) (a.x - b.x);
    int y = (int) (a.y - b.y);

    return (int) sqrt(x * x + y * y);
}

Hero* Enemy::getTarget() {
    return target;
}

void Enemy::setTarget(Hero* target) {
    this->target = target;
}

Point Enemy::getInspectTarget() {
    return inspectTarget;
}

void Enemy::setInspectTarget(Point inspectTarget) {
    this->inspectTarget = inspectTarget;
}

void Enemy::setGameLevel() {
    switch (GameLayer::game_level) {
    case GameLevel::HEAVEN:
        this->setNormalSpeed(ENEMYSPEED_L);
        this->useNormalSpeed();
        this->setDamage(DAMAGE_L);
        this->setAtkRange(ATKRANGE_L);
        break;
    case GameLevel::MORTAL:
        this->setNormalSpeed(ENEMYSPEED_M);
        this->useNormalSpeed();
        this->setDamage(DAMAGE_M);
        this->setAtkRange(ATKRANGE_M);
        break;
    case GameLevel::HELL:
        this->setNormalSpeed(ENEMYSPEED_H);
        this->useNormalSpeed();
        this->setDamage(DAMAGE_H);
        this->setAtkRange(ATKRANGE_H);
        break;
    default:
        this->setNormalSpeed(ENEMYSPEED_M);
        this->useNormalSpeed();
        this->setDamage(DAMAGE_M);
        this->setAtkRange(ATKRANGE_M);
        break;
    }
    this->setVisionRange(VISIONRANGE);
}

bool Enemy::ifVisibleAngle(Point target) {
    Point myVector;
    switch (curDirection) {
    case UP:
        myVector = Point(0, -1);
        break;
    case DOWN:
        myVector = Point(0, 1);
        break;
    case LEFT:
        myVector = Point(-1, 0);
        break;
    case RIGHT:
        myVector = Point(1, 0);
        break;
    case UL:
        myVector = Point(-1, -1);
        break;
    case UR:
        myVector = Point(1, -1);
        break;
    case DL:
        myVector = Point(-1, 1);
        break;
    case DR:
        myVector = Point(1, 1);
        break;
    default:
        myVector = Point(0, 1);
        break;
    }
    float x1 = myVector.x;
    float y1 = myVector.y;
    // transfer into tiled coordinate
    Point myp = parentLayer->tileCoordinate(this->getPosition());
    Point targetp = parentLayer->tileCoordinate(target);
    float x2 = (targetp.x - myp.x);
    float y2 = (targetp.y - myp.y);
    return ((x1 * x2 + y1 * y2)
            / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2))) >= 0;
}

Direction Enemy::getCurDirection() {
    return curDirection;
}

void Enemy::setCurDirection(Direction curDirection) {
    this->curDirection = curDirection;
}

void Enemy::setParentLayer(GameLayer* layer) {
    parentLayer = layer;
}

