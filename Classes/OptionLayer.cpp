#include "OptionLayer.h"
USING_NS_CC;

#define UPBUTTON 0
#define DOWNBUTTON 1
#define LEFTBUTTON 2
#define RIGHTBUTTON 3

OptionLayer::OptionLayer()
{}

OptionLayer::~OptionLayer()
{}

bool OptionLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Layer::init());
        Point origin = Director::getInstance()->getVisibleOrigin();
        auto upButton = Sprite::create("up.png");
        auto downButton = Sprite::create("down.png");
        auto leftButton = Sprite::create("left.png");
        auto rightButton = Sprite::create("right.png");

        upButton->setTag(UPBUTTON);
        downButton->setTag(DOWNBUTTON);
        leftButton->setTag(LEFTBUTTON);
        rightButton->setTag(RIGHTBUTTON);

        upButton->setPosition(Point(origin.x + 150, origin.y + 180));
        this->addChild(upButton, 2);
        downButton->setPosition(Point(origin.x + 150, origin.y + 90));
        this->addChild(downButton, 2);
        leftButton->setPosition(Point(origin.x + 60, origin.y + 90));
        this->addChild(leftButton, 2);
        rightButton->setPosition(Point(origin.x + 240, origin.y + 90));
        this->addChild(rightButton, 2);


        auto joystickListener = EventListenerTouchOneByOne::create();
        joystickListener->setSwallowTouches(true);
        joystickListener->onTouchBegan =
                [&](Touch* touch, Event* event) {
                    CCLOG("sprite began ..");
                    auto target = static_cast<Sprite*>(event->getCurrentTarget());

                    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
                    CCLOG("touch->getLocation()  %f, %f",touch->getLocation().x ,touch->getLocation().y);
                    CCLOG("convertToNodeSpace  %f, %f",locationInNode.x ,locationInNode.y );
                    Size s = target->getContentSize();
                    Rect rect = Rect(0,0,s.width, s.height);

                    if (rect.containsPoint(locationInNode)) {
                        CCLOG("sprite began .. x=%f, y=%f", locationInNode.x, locationInNode.y);
                        CCLOG("sprite TAG %d", target->getTag());

                        _delegator->onWalk(target->getTag());
                        target->setOpacity(180);

                        return true;
                    }
                    return false;
                };

        joystickListener->onTouchMoved = [](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
//            target->setPosition(target->getPosition() + touch->getDelta());
        };

        joystickListener->onTouchEnded = [&](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            CCLOG("sprite move ended..");
            target->setOpacity(255);
            _delegator->onStop();
        };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(joystickListener, upButton);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(joystickListener->clone(), downButton);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(joystickListener->clone(), leftButton);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(joystickListener->clone(), rightButton);












        ret = true;
    } while(0);
    return ret;
}

void OptionLayer::buildEventListener() {

}
