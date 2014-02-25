#ifndef PkGc_cocos2d_saveHostage_GAMELAYER_H_
#define PkGc_cocos2d_saveHostage_GAMELAYER_H_

#include "cocos2d.h"
#include "OptionLayer.h"
#include "Hero.h"
#include "Enemy.h"
#include "Hostage.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer, public OptionDelegate
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    void update (float dt);
    bool canGo(float x, float y);
    Point tileCoordinate(float x, float y);

    void onWalk(int direction);
    void onStop();

    void checkNewEvent();
    int distance(Point, Point);

private:
    Hero* _hero;
    Enemy* _enemy;
    Hostage* _hostage1;
    Hostage* _hostage2;
    int tempstate=0;
    int tempdirect=0;
    TMXTiledMap* _map;
    TMXLayer* _bgLayer;
    TMXLayer* _metaLayer;
};

#endif // end of PkGc_cocos2d_saveHostage_GAMELAYER_H_
