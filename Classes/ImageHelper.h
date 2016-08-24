//
//  ImageHelper.h
//  SaveHostage
//
//  Created by Chen Guo on 4/9/14.
//
//

#ifndef __SaveHostage__ImageHelper__
#define __SaveHostage__ImageHelper__

#include "cocos2d.h"
#include <vector>
#include <map>
#include "EnumUtil.h"

using namespace std;
USING_NS_CC;

class ImageHelper {
private:
    map<Direction, vector<Rect>> walkAnimationsRects;
    
public:
    ImageHelper();
    ~ImageHelper();
    void initAnimationRectsMap();
    
    map<Direction, vector<Rect>> getWalkAnimationsRects();
    
    static ImageHelper* sharedImageHelper();
};

#endif /* defined(__SaveHostage__ImageHelper__) */
