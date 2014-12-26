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

#define MAX_LAYER    2


Layer* createDemoFishLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new DemoFish1();
        case 1: return new DemoFish2();
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
// DemoFish2
//
//------------------------------------------------------------------

DemoFish2::DemoFish2()
{
    initDemoFish2();
}

DemoFish2::~DemoFish2()
{
    
}

std::string DemoFish2::subtitle() const
{
    return "DemoFish1 ";
}

void DemoFish2::onEnter()
{
    DemoFishTest::onEnter();
}

void DemoFish2::removeThis()
{
    _parent->removeChild(this, true);
    
    nextCallback(this);
}

bool DemoFish2::initDemoFish2()
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
        
        //从1.933秒到2.8秒截取为受伤的动作
//        _hurt = Animate3D::create(animation, 1.933f, 2.8f);
        
        //让精灵循环播放游泳和的受伤动作
        Sequence*pSequence = Sequence::create(_swim,_hurt,NULL);
        _sprite->runAction(RepeatForever::create(pSequence));
    }
    
    // 取得文件管理器
    auto fileUtiles = FileUtils::getInstance();
    
    // 加载相应的Shader文件
    // 加载UVAnimation.vsh并取得文件内容字符串
    auto vertexFilePath = fileUtiles->fullPathForFilename("UVAnimation.vsh");
    auto vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    
    // 加载UVAnimation.fsh并取得文件内容字符串
    auto fragmentFilePath = fileUtiles->fullPathForFilename("UVAnimation.fsh");
    auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);
    
    // 将vsh与fsh装配成一个完整的Shader文件。
    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    // 由Shader文件创建这个Shader
    auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    // 给精灵设置所用的Shader
    _sprite->setGLProgramState(glprogramstate);
    
    //创建海龟所用的贴图。
    auto textrue1 = Director::getInstance()->getTextureCache()->addImage("tortoise.png");
    //将贴图设置给Shader中的变量值u_texture1
    glprogramstate->setUniformTexture("u_texture1", textrue1);
    
    //创建波光贴图。
    auto textrue2 = Director::getInstance()->getTextureCache()->addImage("caustics.png");
    
    //将贴图设置给Shader中的变量值u_lightTexture
    glprogramstate->setUniformTexture("u_lightTexture", textrue2);
    
    //注意，对于波光贴图，我们希望它在进行UV动画时能产生四方连续效果，必须设置它的纹理UV寻址方式为GL_REPEAT。
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR_MIPMAP_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_REPEAT;
    tRepeatParams.wrapT = GL_REPEAT;
    textrue2->setTexParameters(tRepeatParams);
    
    //在这里，我们设置一个波光的颜色，这里设置为白色。
    Vec4  tLightColor(1.0,1.0,1.0,1.0);
    glprogramstate->setUniformVec4("v_LightColor",tLightColor);
    
    //下面这一段，是为了将我们自定义的Shader与我们的模型顶点组织方式进行匹配。模型的顶点数据一般包括位置，法线，色彩，纹理，以及骨骼绑定信息。而Shader需要将内部相应的顶点属性通道与模型相应的顶点属性数据进行绑定才能正确显示出顶点。
    long offset = 0;
    auto attributeCount = _sprite->getMesh()->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = _sprite->getMesh()->getMeshVertexAttribute(k);
        glprogramstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                               meshattribute.size,
                                               meshattribute.type,
                                               GL_FALSE,
                                               _sprite->getMesh()->getVertexSizeInBytes(),
                                               (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    
    //uv滚动初始值设为0
    _lightani.x = _lightani.y = 0;
    
    return true;
}

void DemoFish2::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    if(_sprite)
    {
        
        auto glprogramstate = _sprite->getGLProgramState();
        if(glprogramstate)
        {
            _lightani.x += 0.01;
            if(_lightani.x > 1.0)
            {
                _lightani.x-= 1.0;
            }
            _lightani.y += 0.01;
            if(_lightani.y > 1.0)
            {
                _lightani.y-= 1.0;
            }
            glprogramstate->setUniformVec2("v_animLight",_lightani);
        }
    }
    Node::draw(renderer,transform,flags);
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

