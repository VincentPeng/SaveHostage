#include "JoyStick.h"

JoyStick * JoyStick::createJoyStick(const string&dockName,const string&ballName,int ballradius,int movearearadius,bool isfollowtouch,bool iscanvisible,bool isautohide,bool hasanimation)
{
    JoyStick* joystick = new JoyStick();
    if (joystick)
    {
        joystick->autorelease();
        joystick->initWithBallRadius(ballradius, movearearadius, isfollowtouch, iscanvisible, isautohide,  hasanimation);
        joystick->setDockTexture(dockName);
        joystick->setBallTexture(ballName);
        return joystick;
    }
    
    CC_SAFE_DELETE(joystick);
    return NULL;
}
//JokStick鐨勫垵濮嬪寲
void JoyStick::initWithBallRadius(int ballradius,int movearearadius,bool isfollowtouch,bool iscanvisible,bool isautohide,bool hasanimation)
{
    
    if (!Sprite::init())
    {
        return;
    }
    BallRadius=ballradius;
    MoveAreaRadius=movearearadius;
    IsFollowTouch=isfollowtouch;
    IsCanVisible=iscanvisible;
    IsAutoHide=isautohide;
    HasAnimation=hasanimation;
    
    Power=0;
    Angle=0;
    
    this->setHitAreaWithRect(Rect(0, 0, winSize.width, winSize.height));
    
    Ball =Sprite::create();
    Dock =Sprite::create();
    
    this->addChild(Ball,2);
    this->addChild(Dock,1);
    
    if(!IsCanVisible)
    {
        this->setVisible(false);
    }
    else
    {
        if (IsAutoHide)
        {
            this->setVisible(false);
        }
    }
}
void JoyStick::setBallTexture(const string&imageName)
{
    Ball->removeAllChildrenWithCleanup(true);
	
	Sprite *balltexture=Sprite::create(imageName);
	
	Ball->addChild(balltexture,4,1);
    
}
void JoyStick::setDockTexture(const string&imageName)
{
    
    Dock->removeAllChildrenWithCleanup(true);
	Sprite *docktexture=Sprite::create(imageName);
	
	Dock->addChild(docktexture,3,2);
    
}
void JoyStick::setHitAreaWithRadius(int radius)
{
	ActiveRect=Rect(0, 0, 0, 0);
	ActiveRadius=radius;
}
void JoyStick::setHitAreaWithRect(Rect rect)
{
    ActiveRect=rect;
	ActiveRadius=0;
}
void JoyStick::startTimer(float dt)
{
    this->schedule(schedule_selector(JoyStick::timerUpdate));
    
}
void JoyStick::stopTimer(float dt)
{
    this->unschedule(schedule_selector(JoyStick::timerUpdate));
}
void JoyStick::timerUpdate(float dt)
{
    _delegate->onJoyStickUpdate(this, Angle, Direction, Power);
}
void JoyStick::myTouchBegan(Point touchPoint)
{
    CurrentPoint = touchPoint;
	IsTouched=true;
	
	if(IsAutoHide && IsCanVisible){
		this->setVisible(true);
	}
	
	if(IsFollowTouch)
    {
		this->setPosition(touchPoint);
	}
	
	Ball->stopAllActions();
	this->updateTouchPoint(touchPoint);
    this->startTimer(0);
}
void JoyStick::resetTexturePosition()
{
    Power=0;
	Angle=0;
	CurrentPoint=Point(0,0);
    
	if (!IsAutoHide && IsCanVisible && HasAnimation)
    {
		MoveTo *action =MoveTo::create(0.5, Point(0,0));
		Ball->runAction(EaseElasticOut::create(action));
	}
    else
    {
		Ball->setPosition(Point(0,0));
	}
}
bool JoyStick::containsTouchLocation(Touch *touch)
{
    Point touchPoint = touch->getLocation();
	if (ActiveRadius>0)
	{
		if (touchPoint.getDistance(this->getParent()->convertToWorldSpace(this->getPosition()))< ActiveRadius) {
			return true;
		}
	}
	if(ActiveRect.size.width>0 && ActiveRect.size.height>0){
		if (touchPoint.x>ActiveRect.origin.x && touchPoint.x<ActiveRect.origin.x+ActiveRect.size.width && touchPoint.y>ActiveRect.origin.y && touchPoint.y<ActiveRect.origin.y+ActiveRect.size.height) {
			return true;
		}
	}
    return false;
}
void JoyStick::updateTouchPoint(Point touchPoint)
{
    Point selfposition=this->getParent()->convertToWorldSpace(this->getPosition());
	if (touchPoint.getDistance(Point(selfposition.x,selfposition.y)) > (MoveAreaRadius-BallRadius))
	{
        Vec2 newv = Vec2(touchPoint.x-selfposition.x, touchPoint.y-selfposition.y).getNormalized();
        CurrentPoint =Point::ZERO+newv*(float)(MoveAreaRadius-BallRadius);
	}
    else
    {
		CurrentPoint = Point(touchPoint.x-selfposition.x,touchPoint.y-selfposition.y);
	}
	Ball->setPosition(CurrentPoint);
	
	Angle=atan2(Ball->getPositionY(), Ball->getPositionX())/(3.14159/180);
	Power=Ball->getPosition().getDistance(Point::ZERO)/(MoveAreaRadius-BallRadius);
	Direction=Point(cos(Angle * (3.14159/180)),sin(Angle * (3.14159/180)));
	
}
bool JoyStick::onTouchBegan(Touch * touch,Event * event)
{
    
    if (!this->containsTouchLocation(touch))
    {
        return false;
    }
    Point touchPoint =touch->getLocation();
    this->myTouchBegan(touchPoint);
    
    return true;
    
}
void JoyStick::onTouchMoved(Touch * touch,Event * event)
{
    Point touchPoint =touch->getLocation();
    if (IsTouched)
    {
        this->updateTouchPoint(touchPoint);
    }
    
    
}
void JoyStick::onTouchEnded(Touch * touch,Event * event)
{
    if (IsTouched)
    {
		if(IsAutoHide && IsCanVisible)
        {
			this->setVisible(false);
		}
		IsTouched=false;
		this->stopTimer(0);
		this->resetTexturePosition();
	}
    
    
}
void JoyStick::onEnter()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Sprite::onEnter();
    
}
void JoyStick::onExit()
{
    _eventDispatcher->removeAllEventListeners();
    Sprite::onExit();
}
