//
//  WaterEffectSprite.h
//  MyCppGame
//
//  Created by fangyu on 12/24/14.
//
//

#ifndef __MyCppGame__WaterEffectSprite__
#define __MyCppGame__WaterEffectSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class WaterEffectSprite
: public Sprite
{
public:
    static WaterEffectSprite* create(const char* pszFileName);
    
public:
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    void initGLProgram();
    
};
#endif /* defined(__MyCppGame__WaterEffectSprite__) */
