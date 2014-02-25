#ifndef PkGc_cocos2dx_saveHostage_HERO_H_
#define PkGc_cocos2dx_saveHostage_HERO_H_

#include "cocos2d.h"

class Hero : public cocos2d::Sprite {
public:
    Hero();
    ~Hero();
    bool init();
    CREATE_FUNC(Hero);
    void doAction();
    void setSpeed(int s);

private:
    int speed;
};

#endif // end of PkGc_cocos2dx_saveHostage_HERO_H_
