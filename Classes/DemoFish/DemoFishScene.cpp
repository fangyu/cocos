//
//  DemoFishScene.cpp
//  Tests
//
//  Created by fangyu on 12/25/14.
//
//

#include "DemoFishScene.h"

Layer* nextDemoFish();
Layer* backDemoFish();
Layer* restartDemoFish();

static int sceneIdx = -1;

#define MAX_LAYER    1


Layer* createDemoFishLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new DemoFish1();
    
    }
    
    return nullptr;
}

Layer* nextDemoFish()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = createDemoFishLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* backDemoFish()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = createDemoFishLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* restartDemoFish()
{
    auto layer = createDemoFishLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

DemoFishTest::DemoFishTest()
{
    
}

DemoFishTest::~DemoFishTest()
{
    
}

std::string DemoFishTest::title() const
{
    return "DemoFish Test";
}

std::string DemoFishTest::subtitle() const
{
    return "No title";
}

void DemoFishTest::restartCallback(Ref* sender)
{
    auto s = new DemoFishScene();
    s->addChild(restartDemoFish());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DemoFishTest::nextCallback(Ref* sender)
{
    auto s = new DemoFishScene();
    s->addChild( nextDemoFish() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DemoFishTest::backCallback(Ref* sender)
{
    auto s = new DemoFishScene();
    s->addChild( backDemoFish() );
    Director::getInstance()->replaceScene(s);
    s->release();
}


//------------------------------------------------------------------
//
// DemoFish1
//
//------------------------------------------------------------------

DemoFish1::DemoFish1()
{
    initDemoFish1();
}

DemoFish1::~DemoFish1()
{
    
}

std::string DemoFish1::subtitle() const
{
    return "DemoFish1 ";
}

void DemoFish1::onEnter()
{
    DemoFishTest::onEnter();
}

void DemoFish1::removeThis()
{
    _parent->removeChild(this, true);
    
    nextCallback(this);
}

bool DemoFish1::initDemoFish1()
{
    //加载模型文件
    std::string fileName = "3D/tortoise.c3b";
    _sprite = Sprite3D::create(fileName);
    _sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    _sprite->setPosition(Vec2(s.width * 4.f / 5.f, s.height / 2.f));
    addChild(_sprite);
    
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        //从起始到1.933秒截取为游泳动作
        _swim = Animate3D::create(animation, 0.f, 1.933f);
        _swim->retain();
        
        //从1.933秒到2.8秒截取为受伤的动作
        _hurt = Animate3D::create(animation, 1.933f, 2.8f);
        _hurt->retain();
        
        //让精灵循环播放游泳和的受伤动作
        Sequence*pSequence = Sequence::create(_swim,_hurt,NULL);
        _sprite->runAction(RepeatForever::create(pSequence));
    }
    
    return true;
}


//------------------------------------------------------------------
//
// ActionManagerTestScene
//
//------------------------------------------------------------------

void DemoFishScene::runThisTest()
{
    auto layer = nextDemoFish();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

