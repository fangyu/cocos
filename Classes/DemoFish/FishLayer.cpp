//
//  FishLayer.cpp
//  DemoFish1
//
//  Created by fangyu on 12/23/14.
//
//

#include "FishLayer.h"
USING_NS_CC;

bool FishLayer::init()
{

    std::string fileName = "tortoise.c3b";
    m_Sprite = Sprite3D::create(fileName);
    m_Sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    m_Sprite->setPosition(Vec2(s.width / 2.f, s.height / 2.f));
    addChild(m_Sprite);

    m_Animation3D = Animation3D::create(fileName);
    if (m_Animation3D)
    {
        
        m_Swim = Animate3D::create(m_Animation3D, 0.f, 1.933f);
//        m_Swim->retain();
        
//        m_Hurt = Animate3D::create(m_Animation3D, 1.933f, 2.8f);
//        m_Hurt->retain();
        
        Sequence* pSequence = Sequence::create(m_Swim,NULL);
        m_Sprite->runAction(RepeatForever::create(pSequence));
    }
    
    auto glprogram = GLProgram::createWithFilenames("UVAnimation.vsh", "UVAnimation.fsh");

    auto glprogramstate =  GLProgramState::getOrCreateWithGLProgram(glprogram);
    
    m_Sprite->setGLProgramState(glprogramstate);
    
    auto textrue1 = Director::getInstance()->getTextureCache()->addImage("tortoise.png");
    
    glprogramstate->setUniformTexture("u_texture1", textrue1);
    
    
    auto textrue2 = Director::getInstance()->getTextureCache()->addImage("caustics.png");
    
    glprogramstate->setUniformTexture("u_lightTexture", textrue2);
    
    Texture2D::TexParams		tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR_MIPMAP_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_REPEAT;
    tRepeatParams.wrapT = GL_REPEAT;
    textrue2->setTexParameters(tRepeatParams);
    
    Vec4  tLightColor(1.0,1.0,1.0,1.0);
    glprogramstate->setUniformVec4("v_LightColor",tLightColor);
    
    long offset = 0;
    auto attributeCount = m_Sprite->getMesh()->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = m_Sprite->getMesh()->getMeshVertexAttribute(k);
        glprogramstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                               meshattribute.size,
                                               meshattribute.type,
                                               GL_FALSE,
                                               m_Sprite->getMesh()->getVertexSizeInBytes(),
                                               (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    
    m_LightAni.x = m_LightAni.y = 0;
    
    return true;
}

void FishLayer::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    if(m_Sprite)
    {
        
        auto glprogramstate = m_Sprite->getGLProgramState();
        if(glprogramstate)
        {
            m_LightAni.x += 0.01;
            if(m_LightAni.x > 1.0)
            {
                m_LightAni.x-= 1.0;
            }
            m_LightAni.y += 0.01;
            if(m_LightAni.y > 1.0)
            {
                m_LightAni.y-= 1.0;
            }
            glprogramstate->setUniformVec2("v_animLight",m_LightAni);
        }
    }
    Node::draw(renderer,transform,flags);
}

//击中乌龟
void    FishLayer::AttackWuGui()
{
    if (m_Animation3D)
    {
        //从1.933秒到2.8秒截取为受伤的动作
        m_Hurt = Animate3D::create(m_Animation3D, 1.933f, 2.8f);
        m_Hurt->retain();
        
        m_Sprite->stopAllActions();
        //让精灵循环播放游泳和的受伤动作
        Sequence*   pSequence = Sequence::create(m_Hurt,CallFunc::create( std::bind(&FishLayer::ContinueSwim, this) ),NULL);
        m_Sprite->runAction(pSequence);
        
    }
    
}
//继续游动
void    FishLayer::ContinueSwim()
{
    if (m_Animation3D)
    {
        //从起始到1.933秒截取为游泳动作
        m_Swim = Animate3D::create(m_Animation3D, 0.f, 1.933f);
        m_Swim->retain();
        
        m_Sprite->stopAllActions();
        //让精灵循环播放游泳和的受伤动作
        Sequence*   pSequence = Sequence::create(m_Swim,NULL);
        m_Sprite->runAction(RepeatForever::create(pSequence));
    }
}

