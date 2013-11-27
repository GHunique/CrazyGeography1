//
//  UIFUAlert.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-13.
//
//

#ifndef __CrazyGeography__UIFUAlert__
#define __CrazyGeography__UIFUAlert__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UIFUAlert : public CCLayerRGBA {
    
public:
    
    
    UIFUAlert();
    ~UIFUAlert();
    static UIFUAlert* createWithFileName(const char *fileName);
    bool initWithFileName(const char *fileName);
    bool init();
    void onEnter();
    void onExit();
    
    void boundConfirmEvent(cocos2d::CCObject *target,SEL_TouchEvent selector);//绑定确定按钮事件
    
private:
    UILayer *_aUILayer;
    Layout  *_alert_root;
    std::string _fileName;
    
    UIButton *_cancleButt;
    UIButton *_confirmButt;
    
private:
    void cancelButt(UIButton *pSender,TouchEventType type);
    void confirmButt(UIButton *pSender,TouchEventType type);
    
    //屏蔽优先级低的界面触摸事件
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    
};
#endif /* defined(__CrazyGeography__UIFUAlert__) */
