//
//  GameScene.cpp
//  Tests
//
//  Created by fangyu on 12/30/14.
//
//

#include "GameScene.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"

using namespace ui;

Layer* nextSLGDemo();
Layer* backSLGDemo();
Layer* restartSLGDemo();

static int sceneIdx = -1;

#define MAX_LAYER    1

Layer* createSLGDemoLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new DemoSLGLayer();
    }
    
    return nullptr;
}

Layer* restartSLGDemo()
{
    auto layer = createSLGDemoLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* backSLGDemo()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = createSLGDemoLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* nextSLGDemo()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = createSLGDemoLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

DemoSLGTest::DemoSLGTest()
{
}

DemoSLGTest::~DemoSLGTest()
{
}

std::string DemoSLGTest::title() const
{
    return "Demo SLG Scene Test";
}

std::string DemoSLGTest::subtitle() const
{
    return "No title";
}

void DemoSLGTest::restartCallback(Ref* sender)
{
    auto s = new GameScene();
    s->addChild(restartSLGDemo());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DemoSLGTest::nextCallback(Ref* sender)
{
    auto s = new GameScene();
    s->addChild(nextSLGDemo());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DemoSLGTest::backCallback(Ref* sender)
{
    auto s = new GameScene();
    s->addChild( backSLGDemo() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// DemoSLGLayer
//
//------------------------------------------------------------------

DemoSLGLayer::DemoSLGLayer()
{
    initDemoSLGLayer();
}

DemoSLGLayer::~DemoSLGLayer()
{
    
}

std::string DemoSLGLayer::subtitle() const
{
    return "DemoFish1 ";
}

void DemoSLGLayer::onEnter()
{
    DemoSLGTest::onEnter();
}

void DemoSLGLayer::removeThis()
{
    _parent->removeChild(this, true);
    
    nextCallback(this);
}

bool DemoSLGLayer::initDemoSLGLayer()
{
    mapLayer = Layer::create();
    this->addChild(mapLayer,-1);
    
    bgSprite = Sprite::create("ipadhd/HelloWorld.png");
    bgSprite->setAnchorPoint(Vec2::ZERO);
    bgSprite->setPosition(Vec2::ZERO),
    bgOrigin = Vec2(Vec2::ZERO);
    mapLayer->addChild(bgSprite);
    
    // 1 创建一个事件监听器
    auto listener = EventListenerTouchAllAtOnce::create();
    // 2 绑定触摸事件
    listener->onTouchesBegan = CC_CALLBACK_2(DemoSLGLayer::onTouchesBegan, this);// 触摸开始时触发
    listener->onTouchesMoved = CC_CALLBACK_2(DemoSLGLayer::onTouchesMoved, this);// 触摸移动时触发
    // 3 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);

    
//    auto treeSprite = Sprite::create("1.png");
//    treeSprite->setAnchorPoint(Vec2::ZERO);
//    treeSprite->setPosition(Vec2::ZERO),
//    treeSprite->setScale(2);
//    bgSprite->addChild(treeSprite, 2);
//    
//    auto map = TMXTiledMap::create("mymap4.tmx");
//    map->setAnchorPoint(Vec2::ZERO);
//    map->setPosition(Vec2::ZERO),
//    bgSprite->addChild(map, 1);
    
    return true;
}

void DemoSLGLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    
}

void DemoSLGLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto winSize = Director::getInstance()->getWinSize();
    if(touches.size() > 1)        // 多点进行缩放
    {
        // 得到当前两触摸点
        auto point1 = touches[0]->getLocation();
        auto point2 = touches[1]->getLocation();
        // 计算两点之间得距离
        auto currDistance = point1.distance(point2);
        // 计算两触摸点上一时刻之间得距离
        auto prevDistance = touches[0]->getPreviousLocation().distance(touches[1]->getPreviousLocation());
        // 两触摸点与原点的差向量，pointVec1和pointVec2是相对于bgSprite的位置
        auto pointVec1 = point1  - bgOrigin;
        auto pointVec2 = point2  - bgOrigin;
        // 两触摸点的相对中点
        auto relMidx = (pointVec1.x + pointVec2.x) / 2 ;
        auto relMidy = (pointVec1.y + pointVec2.y) / 2 ;
        // 计算bgSprite的锚点
        auto anchorX = relMidx / bgSprite->getBoundingBox().size.width;
        auto anchorY = relMidy / bgSprite->getBoundingBox().size.height;
        // 相对屏幕的中点
        auto absMidx = (point2.x + point1.x) / 2 ;
        auto absMidy = (point2.y + point1.y) / 2 ;
        
        // 缩放时，为了避免出现空白的区域，需要做以下的边界处理。
        // 当bgSprite快要进入到屏幕时，修改bgSprite的位置（既absMidx和absMidy）。
        if(  bgOrigin.x > 0)
        {
            absMidx -= bgOrigin.x;
        }
        if( bgOrigin.x < -bgSprite->getBoundingBox().size.width + winSize.width )
        {
            absMidx +=  -bgSprite->getBoundingBox().size.width + winSize.width - bgOrigin.x;
        }
        if( bgOrigin.y > 0 )
        {
            absMidy -= bgOrigin.y;
        }
        if( bgOrigin.y < -bgSprite->getBoundingBox().size.height + winSize.height )
        {
            absMidy +=  -bgSprite->getBoundingBox().size.height + winSize.height - bgOrigin.y;
        }
        // 重设bgSprite锚点和位置
        bgSprite->setAnchorPoint(Vec2(anchorX, anchorY));
        bgSprite->setPosition(Vec2(absMidx, absMidy));
        // 根据两触摸点前后的距离计算缩放倍率
        auto scale = bgSprite->getScale() * ( currDistance / prevDistance);
        // 控制缩放倍率在1～4倍之间，最小倍率不能太小，不让背景将不能填充满整个屏幕。
        scale = MIN(4,MAX(1, scale));
        bgSprite->setScale(scale);
        // 更新原点位置
        bgOrigin = Vec2(absMidx, absMidy) - Vec2(bgSprite->getBoundingBox().size.width * anchorX, bgSprite->getBoundingBox().size.height * anchorY) ;
    }
    else if(touches.size() == 1)        // 单点进行移动
    {
        // 单点时，touches中只有一个Touch对象，所以通过touches[0]就可以得到触摸对象
        auto touch = touches[0];
        // 计算滑动过程中的滑动增量
        auto diff = touch->getDelta();
        // 得到当前bgSprite的位置
        auto currentPos = bgSprite->getPosition();
        // 得到滑动后bgSprite应该所在的位置
        auto pos = currentPos + diff;
        // 得到此刻bgSprite的尺寸
        auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
        
        //边界控制，约束pos的位置
        pos.x = MIN(pos.x, bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.x = MAX(pos.x, -bgSpriteCurrSize.width + winSize.width + bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.y = MIN(pos.y, bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);
        pos.y = MAX(pos.y, -bgSpriteCurrSize.height + winSize.height + bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);
        // 重设bgSprite位置
        bgSprite->setPosition(pos);
        
        // 更新原点位置
        if( pos.x >= bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x
           || pos.x <= -bgSpriteCurrSize.width + winSize.width + bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x)
        {
            diff.x = 0;
        }
        if( pos.y >= bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y
           || pos.y <= -bgSpriteCurrSize.height + winSize.height + bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y)
        {
            diff.y = 0;
        }
        bgOrigin += diff;
    }
}

void GameScene::runThisTest()
{
    auto layer = nextSLGDemo();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

