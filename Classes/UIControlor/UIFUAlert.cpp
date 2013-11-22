//
//  UIFUAlert.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-13.
//
//

#include "UIFUAlert.h"

UIFUAlert::UIFUAlert()
{
    
}

UIFUAlert::~UIFUAlert()
{
    
}

UIFUAlert* UIFUAlert::createWithFileName(const char *fileName)
{
    UIFUAlert *aler =new UIFUAlert();
    if (aler && aler->initWithFileName(fileName))
    {
        aler->autorelease();
        return aler;
    }
    
    CC_SAFE_DELETE(aler);
    return NULL;
    
}

bool UIFUAlert::initWithFileName(const char *fileName)
{
    _fileName = fileName;
    
    return this->init();
}

bool UIFUAlert::init()
{
    if (!this->CCLayerRGBA::init()) return false;
    _aUILayer = UILayer::create();
    this->addChild(_aUILayer);
    _alert_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(_fileName.c_str()));
    
    _cancleButt  = static_cast<UIButton *>(_alert_root->getChildByName(""));
    _confirmButt = static_cast<UIButton *>(_alert_root->getChildByName(""));
    
    return true;
}

void UIFUAlert::onEnter()
{
    this->CCLayerRGBA::onEnter();
    //....
}

void UIFUAlert::onExit()
{
    //.....
    this->CCLayerRGBA::onExit();
}

#pragma mark - 

#pragma mark - 
void UIFUAlert::cancelButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
            this->removeFromParent();           //从父节点移除
            break;
        case TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}

void UIFUAlert::confirmButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
            break;
        case TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}

