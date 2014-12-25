//
//  FishLayer.h
//  DemoFish1
//
//  Created by fangyu on 12/23/14.
//
//

#ifndef __DemoFish1__FishLayer__
#define __DemoFish1__FishLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "3d/CCMesh.h"
#include "Math/Vec2.h"

NS_CC_BEGIN
class FishLayer
: public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(FishLayer);
    virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
    
    //击中乌龟
    void AttackWuGui();
    
    //继续游动
    void ContinueSwim();
    
    
protected:
    cocos2d::Sprite3D*		m_Sprite;

    cocos2d::Animate3D*		m_Swim;

    cocos2d::Animate3D*		m_Hurt;
    
    cocos2d::Animation3D*	m_Animation3D;
    
    Vec2					m_LightAni;
};

NS_CC_END

#endif /* defined(__DemoFish1__FishLayer__) */
