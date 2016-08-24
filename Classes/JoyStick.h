//
//  JoyStick.h
//  SaveHostage
//
//  Created by Chen Guo on 2/26/14.
//
//

#ifndef __JoyStick__H_H
#define __JoyStick__H_H

#include "cocos2d.h"

#define winSize Director::getInstance()->getWinSize()

using namespace std;
USING_NS_CC;

class JoyStick;

// JoyStick Agent
class JoyStickDelegate {
public:
    virtual void onJoyStickUpdate(Node *sender, float angle, Point direction,
                                  float power) = 0;
};

class JoyStick : public Sprite {
private:
    CC_SYNTHESIZE(Sprite *, Ball, bBall);  // The ball follows touch movement
    CC_SYNTHESIZE(Sprite *, Dock, dDock);  // The stick base pad
    CC_SYNTHESIZE(int, MoveAreaRadius, mMoveAreaRadius);  // Movement radius
    CC_SYNTHESIZE(int, BallRadius, bBallRadius);          // Ball radius
    CC_SYNTHESIZE(Rect, ActiveRect, aActiveRect);
    CC_SYNTHESIZE(int, ActiveRadius, aActiveRadius);
    CC_SYNTHESIZE(Point, CurrentPoint, cCurrentPoint);
    CC_SYNTHESIZE(bool, IsFollowTouch, iIsFollowTouch);
    CC_SYNTHESIZE(bool, IsCanVisible, iIsCanVisible);
    CC_SYNTHESIZE(bool, IsAutoHide, iIsAutoHide);
    CC_SYNTHESIZE(bool, IsTouched, iIsTouched);
    CC_SYNTHESIZE(bool, HasAnimation, hHasAnimation);
    CC_SYNTHESIZE(float, Power, pPower);
    CC_SYNTHESIZE(float, Angle, aAngle);
    CC_SYNTHESIZE(Point, Direction, dDirection);
    
    CC_SYNTHESIZE(JoyStickDelegate *, _delegate, Delegate);  // Agent
    
public:
    static JoyStick *createJoyStick(const string &dockName,
                                    const string &ballName, int ballradius,
                                    int movearearadius, bool isfollowtouch,
                                    bool iscanvisible, bool isautohide,
                                    bool hasanimation);
    
    void initWithBallRadius(int ballradius, int movearearadius,
                            bool isfollowtouch, bool iscanvisible,
                            bool isautohide, bool hasanimation);
    
    void setBallTexture(const string &imageName);
    void setDockTexture(const string &imageName);
    
    void setHitAreaWithRadius(int radius);
    void setHitAreaWithRect(Rect rect);
    void startTimer(float dt);
    void stopTimer(float dt);
    void timerUpdate(float dt);
    void myTouchBegan(Point touchPoint);
    void resetTexturePosition();
    bool containsTouchLocation(Touch *touch);
    void updateTouchPoint(Point touchPoint);
    virtual bool onTouchBegan(Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(Touch *touch, cocos2d::Event *unused_event);
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__JoyStick__H_H) */