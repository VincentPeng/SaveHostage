#ifndef PkGc_cocos2d_saveHostage_ENEMY_H_
#define PkGc_cocos2d_saveHostage_ENEMY_H_

class Hero;
class Hostage;
class GameLayer;

#include "cocos2d.h"
#include "EnumUtil.h"
#include "Hero.h"
#include <PathGenerator.h>
#include "AppDef.h"
#include "TileNode.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "ImageHelper.h"

#include <vector>
using namespace std;
USING_NS_CC;

class Enemy: public cocos2d::Sprite {
public:
    Enemy();
    ~Enemy();
    bool init();
    CREATE_FUNC(Enemy);
    void setParentLayer(GameLayer* layer);
    
    void reset();
    void doAction();
    
    void walk();
    void shoot();
    void setPath(vector<Point> path);
    void initialIdleMove();
    void takeAction();
    void hangAround();
    void alerting();
    void toMissingPoint();
    bool ifStoped();
    void setState(State state);
    State getState();
    void setSign(Sprite* sign);
    void setLoopRoute(vector<vector<Point>> route);
    void idleMoveFrom(int index);
    
    int getAtkRange();
    void setAtkRange(int atkRange);
    int getDamage();
    void setDamage(int damage);
    int getSpeed();
    void setSpeed(int speed);
    
    void useNormalSpeed();
    void useHighSpeed();
    
    int getVisionRange();
    void setVisionRange(int visionRange);
    
    bool canSee(Hero* hero);
    bool canAttack(Hero* hero);
    
    int getNormalSpeed();
    void setNormalSpeed(int normalSpeed);
    
    int distance(Point, Point);
    
    Hero* getTarget();
    void setTarget(Hero* target);
    
    Point getInspectTarget();
    void setInspectTarget(Point inspectTarget);
    void setGameLevel();
    Direction directionP2P(Point pold, Point pnew);
    bool ifVisibleAngle(Point target);
    
    Direction getCurDirection();
    void setCurDirection(Direction curDirection);
    
    static int lookaround_clock;
    
private:
    vector<Point> epath;
    int routeIndex = 0;
    int curIndex = 0;
    vector<Point> subpath;
    State curState = State::IDLE;
    int speed;
    int normalSpeed;
    int damage;
    int atkRange;
    int visionRange;
    int clock = 0;
    Sprite* sign;
    vector<vector<Point>> loopRoute;
    Hero* target;
    Point inspectTarget;
    Direction curDirection;
    GameLayer* parentLayer;
};

#endif // end of PkGc_cocos2d_saveHostage_ENEMY_H_
