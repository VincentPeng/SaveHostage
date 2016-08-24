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

#define winSize  Director::getInstance()->getWinSize()

using namespace std;
USING_NS_CC;

class JoyStick;

//JoyStick的代理类
class JoyStickDelegate
{
public:
    
    virtual void onJoyStickUpdate(Node*sender,float angle,Point direction,float power) =0;
    
};

class JoyStick:public Sprite
{
private:
    
    CC_SYNTHESIZE(Sprite *, Ball, bBall); //更随手势转动的球
    CC_SYNTHESIZE(Sprite *, Dock, dDock); //底座
    CC_SYNTHESIZE(int, MoveAreaRadius, mMoveAreaRadius); //移动半径
    CC_SYNTHESIZE(int, BallRadius, bBallRadius); //球半径
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
    
    CC_SYNTHESIZE(JoyStickDelegate*, _delegate, Delegate);//代理
    
public:
    //   自定义实例函数
    static JoyStick * createJoyStick(const string&dockName,const string&ballName,int ballradius,int movearearadius,bool isfollowtouch,bool iscanvisible,bool isautohide,bool hasanimation);
    /**********
     函数参数说明：
     1.参数dockName :底座背景图名称
     2.参数ballName :旋转球名称
     3.参数ballradius :旋转球的半径
     4.参数movearearadius :旋转球活动半径
     5.参数isfollowtouch :是否跟随触摸
     6.参数iscanvisible  :是否可见
     7.参数isautohide ：是否自动隐藏（即用户没有操作英雄时，隐藏操作键）
     8.参数hasanimation ：是否带动画
     
     **********/
    
    void initWithBallRadius(int ballradius,int movearearadius,bool isfollowtouch,bool iscanvisible,bool isautohide,bool hasanimation) ;
    
    void setBallTexture(const string&imageName);
    void setDockTexture(const string&imageName);
    
    void setHitAreaWithRadius(int radius);
    void setHitAreaWithRect(Rect rect);
    void startTimer(float dt);
    void stopTimer(float dt);
    void timerUpdate(float dt);
    void myTouchBegan(Point touchPoint);
    void resetTexturePosition();
    bool containsTouchLocation(Touch *touch) ;
    void updateTouchPoint(Point touchPoint);
    virtual bool onTouchBegan(Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(Touch *touch, cocos2d::Event *unused_event);
    virtual void onEnter();
    virtual void onExit();
    
    
};

#endif /* defined(__JoyStick__H_H) */