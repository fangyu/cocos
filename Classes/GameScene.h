//
//  GameScene.h
//  Tests
//
//  Created by fangyu on 12/30/14.
//
//

#ifndef __Tests__GameScene__
#define __Tests__GameScene__

#include <stdio.h>
#include "testBasic.h"
#include "BaseTest.h"

USING_NS_CC;

class DemoSLGTest : public BaseTest
{
    
protected:
    TextureAtlas* _atlas;
    
    std::string    _title;
    
public:
    DemoSLGTest(void);
    virtual ~DemoSLGTest(void);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class DemoSLGLayer : public DemoSLGTest
{
public:
    DemoSLGLayer();
    ~DemoSLGLayer();
    
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
    
    //初始化当前层
    bool initDemoSLGLayer();
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

    
private:
    Layer* mapLayer;
    Sprite* bgSprite;
    Vec2 bgOrigin;
};

class GameScene
: public TestScene
{
public:
    virtual void runThisTest();
    
};

#define CL(__className__) [](){ return __className__::create();}
#define CLN(__className__) [](){ auto obj = new __className__(); obj->autorelease(); return obj; }

#endif /* defined(__Tests__GameScene__) */
