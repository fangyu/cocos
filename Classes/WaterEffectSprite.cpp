//
//  WaterEffectSprite.cpp
//  MyCppGame
//
//  Created by fangyu on 12/24/14.
//
//

//WaterEffectSprite.cpp

#include "WaterEffectSprite.h"

WaterEffectSprite* WaterEffectSprite::create(const char *pszFileName) {
    auto pRet = new (std::nothrow) WaterEffectSprite();
    if (pRet && pRet->initWithFile(pszFileName)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool WaterEffectSprite::initWithTexture(Texture2D* texture, const Rect& rect) {
    if (Sprite::initWithTexture(texture, rect)) {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event) {
            setGLProgram(nullptr);
            initGLProgram();
        });
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        initGLProgram();
        return true;
    }
    
    return false;
}

void WaterEffectSprite::initGLProgram() {
    auto fragSource = (GLchar*)String::createWithContentsOfFile(
                                                                FileUtils::getInstance()->fullPathForFilename("Shaders/WaterEffect.fsh").c_str())->getCString();
    auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);
    
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    setGLProgramState(glProgramState);
    
    auto normalMapTextrue = TextureCache::getInstance()->addImage("Textures/water_normal.jpg");
    Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    normalMapTextrue->setTexParameters(texParams);
    getGLProgramState()->setUniformTexture("u_normalMap", normalMapTextrue);
}

