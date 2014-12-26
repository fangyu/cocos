//
//  SceneController.cpp
//  Tests
//
//  Created by fangyu on 12/25/14.
//
//

#include "SceneController.h"
// C++ includes
#include <map>
#include <functional>
#include <string>
#include <chrono>
#include <thread>
// test inclues
#include "AppDelegate.h"
#include "BaseTest.h"
#include "testResource.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <io.h>
#include <WS2tcpip.h>
#endif
#include "cocostudio/CocoStudio.h"
#include "testBasic.h"

#include "DemoFishScene.h"

typedef struct _Controller{
    const char *test_name;
    std::function<TestScene*()> callback;
} Controller;

Controller g_aTestNames[] = {
    
    //
    // TESTS MUST BE ORDERED ALPHABETICALLY
    //     violators will be prosecuted
    //
    { "DemoFishScene", [](){return new DemoFishScene(); } },
};


static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
//static Controller *currentController = nullptr;
#define LINE_SPACE          40

static Vec2 s_tCurPos = Vec2::ZERO;

SceneController::SceneController()
: _beginPos(Vec2::ZERO)
{
    // add close menu
    auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, CC_CALLBACK_1(SceneController::closeCallback, this) );
    auto menu = Menu::create(closeItem, nullptr);
    
    menu->setPosition( Vec2::ZERO );
    closeItem->setPosition(Vec2( VisibleRect::right().x - 30, VisibleRect::top().y - 30));
    
    // add menu items for tests
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    _itemMenu = Menu::create();
    for (int i = 0; i < g_testCount; ++i)
    {
        auto label = Label::createWithTTF(ttfConfig, g_aTestNames[i].test_name);
        auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(SceneController::menuCallback, this));
        
        _itemMenu->addChild(menuItem, i + 10000);
        menuItem->setPosition( Vec2( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
    }
    
    _itemMenu->setContentSize(Size(VisibleRect::getVisibleRect().size.width, (g_testCount + 1) * (LINE_SPACE)));
    _itemMenu->setPosition(s_tCurPos);
    addChild(_itemMenu);
    
    addChild(menu, 1);
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(SceneController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SceneController::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(SceneController::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

SceneController::~SceneController()
{
    
}

void SceneController::menuCallback(Ref * sender)
{
    Director::getInstance()->purgeCachedData();
    
    // get the userdata, it's the index of the menu item clicked
    auto menuItem = static_cast<MenuItem *>(sender);
    int idx = menuItem->getLocalZOrder() - 10000;
    
    // create the test scene and run it
    auto scene = g_aTestNames[idx].callback();
    
    if (scene)
    {
        scene->runThisTest();
        scene->release();
    }

}

void SceneController::closeCallback(Ref * sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool SceneController::onTouchBegan(Touch* touch, Event  *event)
{
    log("onTouchBegan");
    _beginPos = touch->getLocation();
    return true;
}

void SceneController::onTouchMoved(Touch* touch, Event  *event)
{
    auto touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vec2(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

void SceneController::onMouseScroll(Event *event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    float nMoveY = mouseEvent->getScrollY() * 6;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vec2(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    s_tCurPos   = nextPos;

}
