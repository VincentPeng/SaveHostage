#ifndef PkGc_cocos2dx_saveHostage_BGLAYER_H_
#define PkGc_cocos2dx_saveHostage_BGLAYER_H_

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

class BgLayer : public cocos2d::Layer {
public:
    BgLayer();
    ~BgLayer();
    virtual bool init();
    CREATE_FUNC(BgLayer);
};

#endif  // end of PkGc_cocos2dx_saveHostage_BGLAYER_H_
