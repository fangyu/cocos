//
//  DemoFishScene.h
//  Tests
//
//  Created by fangyu on 12/25/14.
//
//

#ifndef __Tests__DemoFishScene__
#define __Tests__DemoFishScene__

#include <stdio.h>
#include "../testBasic.h"
#include "../BaseTest.h"

class DemoFishTest : public BaseTest
{
    
protected:
    TextureAtlas* _atlas;
    
    std::string    _title;
    
public:
    DemoFishTest(void);
    virtual ~DemoFishTest(void);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class DemoFish1 : public DemoFishTest
{
public:
    DemoFish1();
    ~DemoFish1();
    
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
    
    //初始化当前层
    bool initDemoFish1();

    
protected:
    //鱼精灵
    cocos2d::Sprite3D*_sprite;
    //向前游的动作
    cocos2d::Animate3D*_swim;
    //受伤的动作
    cocos2d::Animate3D*_hurt;
    
};

class DemoFishScene
: public TestScene
{
public:
    virtual void runThisTest();
    
};

#endif /* defined(__Tests__DemoFishScene__) */
