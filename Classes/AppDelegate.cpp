#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MyScene.h"

USING_NS_CC;
using namespace cocostudio;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();
    director->setOpenGLView(eglView);
    // my phone 1920*1080

    auto designResolution = Size(960, 540);
    EGLView::getInstance()->setDesignResolutionSize(designResolution.width, designResolution.height, ResolutionPolicy::NO_BORDER);


	
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();



    auto scene = MyScene::create();
    CCLOG("i am here 8");
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
