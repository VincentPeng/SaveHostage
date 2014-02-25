#ifndef PkGc_cocos2d_saveHostage_ENEMY_H_
#define PkGc_cocos2d_saveHostage_ENEMY_H_

#include "cocos2d.h"
#include "StateMachine.h"
#include "EnumUtil.h"

#include <vector>
using namespace std;
USING_NS_CC;

class Enemy : public cocos2d::Sprite {
public:
    Enemy();
    ~Enemy();
    bool init();
    CREATE_FUNC(Enemy);
    void doAction();

    void walk();
    void shoot();

    void setSpeed(int speed);

    void hangAround();
    void alerting();


private:
    StateMachine* mc;
    vector<Point> epath;
    int curIndex=0;
    State curState = State::IDLE;
    int speed;
    int clock=1;

};

#endif // end of PkGc_cocos2d_saveHostage_ENEMY_H_
