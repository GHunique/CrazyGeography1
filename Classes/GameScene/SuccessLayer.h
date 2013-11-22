//
//  SuccessLayer.h
//  CrazyGeography
//
//  Created by yong on 13-11-2.
//
//

#ifndef __CrazyGeography__SuccessLayer__
#define __CrazyGeography__SuccessLayer__

#include "CGconfig.h"


class SuccessLayer : public cocos2d::CCLayer
{
public:
    UILayer *_sUILayer;
    Layout *_rootLayout;
    
public:
    
    SuccessLayer();
    ~SuccessLayer();
    
    CREATE_FUNC(SuccessLayer);

    bool init();
protected:
    void onEnter();
    void onExit();
    
private:
    void shareButt(UIButton *butt,TouchEventType type);
    void nextButt(UIButton *butt,TouchEventType type);
public:
    
    void setSuccessData(Map_str_str &dic);
};

#endif /* defined(__CrazyGeography__SuccessLayer__) */
