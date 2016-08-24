//
//  ImageHelper.cpp
//  SaveHostage
//
//  Created by Chen Guo on 4/9/14.
//
//

#include "ImageHelper.h"

using namespace std;


ImageHelper::ImageHelper()
{
    initAnimationRectsMap();
}

void ImageHelper::initAnimationRectsMap()
{
    vector<Rect> upFrameRects;
    for (int i = 0; i < 4; i ++) {
        upFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 3, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[UP] = upFrameRects;
    vector<Rect> downFrameRects;
    for (int i = 0; i < 4; i ++) {
        downFrameRects.push_back(Rect(i * TILESIZE, 0.0, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[DOWN] = downFrameRects;
    vector<Rect> leftFrameRects;
    for (int i = 0; i < 4; i ++) {
        leftFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 1, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[LEFT] = leftFrameRects;
    vector<Rect> rightFrameRects;
    for (int i = 0; i < 4; i ++) {
        rightFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 2, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[RIGHT] = rightFrameRects;
    vector<Rect> downleftFrameRects;
    for (int i = 0; i < 4; i ++) {
        downleftFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 4, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[DL] = downleftFrameRects;
    vector<Rect> downrightFrameRects;
    for (int i = 0; i < 4; i ++) {
        downrightFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 5, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[DR] = downrightFrameRects;
    vector<Rect> upleftFrameRects;
    for (int i = 0; i < 4; i ++) {
        upleftFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 6, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[UL] = upleftFrameRects;
    vector<Rect> uprightFrameRects;
    for (int i = 0; i < 4; i ++) {
        uprightFrameRects.push_back(Rect(i * TILESIZE, TILESIZE * 7, TILESIZE, TILESIZE));
    }
    walkAnimationsRects[UR] = uprightFrameRects;
}

ImageHelper* ImageHelper::sharedImageHelper()
{
    static ImageHelper* sharedHelper = NULL;
    if (sharedHelper == NULL) {
        sharedHelper = new ImageHelper();
    }
    return sharedHelper;
}

map<Direction, vector<Rect>> ImageHelper::getWalkAnimationsRects()
{
    return walkAnimationsRects;
}


