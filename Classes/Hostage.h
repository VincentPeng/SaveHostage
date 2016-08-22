#ifndef PkGc_cocos2dx_saveHostage_HOSTAGE_H_
#define PkGc_cocos2dx_saveHostage_HOSTAGE_H_

class GameLayer;

#include "cocos2d.h"
#include "Hero.h"
#include "GameLayer.h"

class Hostage : public cocos2d::Sprite {
public:
    Hostage();
    ~Hostage();
    bool init();
    CREATE_FUNC(Hostage);
    void setMyHero(Hero* hero);
    void doAction();
    void followHero ();
    void setNextPoint (Point nxtp);
    void setTotalClocksNeeded(int clocknum);
    int getTotalClocksNeeded();
    bool isSaved();
    void showProgressTimer();
    void hideProgressTimer();
    void setClockPassed(int clocknum);
    void setNextDirection (Direction nextDirection);
    Direction directionP2P(cocos2d::Point pold, cocos2d::Point pnew);
    void reset();
    void addSaveTimer(GameLayer* gameLayer);
private:
    Hero* myHero;
    int clock;
    Point nextPosition;
    Direction direction;
    Direction nextDirection;
    vector<Point> subpath;
    int totalClocksNeeded;
    ProgressTimer* saveProgressTimer;
};

#endif // end of PkGc_cocos2dx_saveHostage_HERO_H_
