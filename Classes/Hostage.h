#ifndef PkGc_cocos2dx_saveHostage_HOSTAGE_H_
#define PkGc_cocos2dx_saveHostage_HOSTAGE_H_

#include "cocos2d.h"

class Hostage : public cocos2d::Sprite {
public:
    Hostage();
    ~Hostage();
    bool init();
    CREATE_FUNC(Hostage);
    void doAction();

};

#endif // end of PkGc_cocos2dx_saveHostage_HERO_H_
