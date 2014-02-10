#ifndef PkGc_cocos2d_saveHostage_GAMELAYER_H_
#define PkGc_cocos2d_saveHostage_GAMELAYER_H_

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
};

#endif // end of PkGc_cocos2d_saveHostage_GAMELAYER_H_
