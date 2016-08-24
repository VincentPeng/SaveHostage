#ifndef PkGc_cocos2dx_saveHostage_HERO_H_
#define PkGc_cocos2dx_saveHostage_HERO_H_

class Hostage;

#include "cocos2d.h"
#include "EnumUtil.h"
#include "TileNode.h"
//#include "Hostage.h"
#include <vector>
#include <queue>
#include <deque>
#include "Hostage.h"
#include "ImageHelper.h"

using namespace std;
USING_NS_CC;

class Hero : public cocos2d::Sprite {
public:
    Hero();
    ~Hero();
    bool init();
    CREATE_FUNC(Hero);
    void doAction();
    void setHealth(int health);
    int getHealth();
    void setSpeed(int s);
    void normalSpeed();
    void highSpeed();
    bool ifUnbreak();
    bool ifInvisible();
    void setDirection(Direction d);
    void setCurrentNode(Point pos);
    void setNextNode(Point nxtNode);
    void setNextPosition(Point nxtPosition);
    void setNextDirection(Direction nDirection);
    void setCurrentHostage(Hostage* host);
    void incrementSavingClock();
    void zeroSavingClock();
    int getSavingClock();
    void setTargetSavingClocks(int target);
    
    Point getCurrentNode();
    Hostage* getCurrentHostage();
    Point getPastPosition();
    
    void updateHostagesPosition();
    void attackedBy(int power);
    bool isDead();
    void reset();
    
    Buff getCurBuff();
    void setCurBuff(Buff buff);
    void buffCountdown();
    int getBufftime();
    void setBufftime(int bufftime);
    
    
private:
    int speed;
    int health;
    Point currentNode;
    Point nextNode;
    Point nextPosition;
    Point pastPosition;
    Direction direction;
    Direction nextDirection;
    int clock = 0;
    vector<Point> subpath;
    deque<Point> pastPoints;
    deque<Direction> pastDirections;
    Hostage* current_hostage;
    vector<Hostage*> savedHostages;
    int saving_clock;
    int target_saving_clocks;
    ProgressTimer* healthProgressTimer;
    int bufftime;
    Buff curBuff;
    bool speedChange;
};

#endif // end of PkGc_cocos2dx_saveHostage_HERO_H_
