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

class DemoFishScene
: public BaseTest
{
public:
    DemoFishScene();
    ~DemoFishScene();
   
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    
protected:
    std::string    _title;
    
};

#endif /* defined(__Tests__DemoFishScene__) */
