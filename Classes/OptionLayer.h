#ifndef PkGc_cocos2dx_saveHostage_OPTIONLAYER_H_
#define PkGc_cocos2dx_saveHostage_OPTIONLAYER_H_

#include "cocos2d.h"


class OptionDelegate {
public:
    virtual void onWalk(int direction)=0;
    virtual void onStop()=0;
};

class OptionLayer : public cocos2d::Layer {
public:
    OptionLayer();
    ~OptionLayer();
    virtual bool init();
    CREATE_FUNC(OptionLayer);

    void buildEventListener();

    CC_SYNTHESIZE(OptionDelegate*, _delegator, Delegator);
};

#endif // end of PkGc_cocos2dx_saveHostage_OPTIONLAYER_H_
