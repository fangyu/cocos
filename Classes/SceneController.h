//
//  SceneController.h
//  Tests
//
//  Created by fangyu on 12/25/14.
//
//

#ifndef __Tests__SceneController__
#define __Tests__SceneController__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class SceneController : public Layer
{
public:
    SceneController();
    ~SceneController();
    
    void menuCallback(Ref * sender);
    void closeCallback(Ref * sender);
    
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    
    void onMouseScroll(Event *event);
    
private:
    Vec2 _beginPos;
    Menu* _itemMenu;
    bool _exitThread;
    
};
#endif /* defined(__Tests__SceneController__) */
