#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SceneController.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    auto scene1 = HelloWorld::createScene();
    director->runWithScene(scene1);
    return true;
    
    
    auto scene = Scene::create();
    auto layer = new SceneController();
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
//    layer->addConsoleAutoTest();
#endif
    layer->autorelease();
//    layer->addConsoleAutoTest();
    scene->addChild(layer);
    director->runWithScene(scene);
    
    // Enable Remote Console
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    auto console = director->getConsole();
    console->listenOnTCP(5678);
    Configuration *conf = Configuration::getInstance();
    bool isAutoRun = conf->getValue("cocos2d.x.testcpp.autorun", Value(false)).asBool();
    if(isAutoRun)
    {
//        layer->startAutoRun();
    }
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setCurrentTest(BaseTest* curTest)
{
    _curTest = curTest;
}

BaseTest* AppDelegate::getCurrentTest()
{
    return _curTest;
}


