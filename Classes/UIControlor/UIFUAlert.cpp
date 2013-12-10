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
    _aUILayer->addWidget(_alert_root);
    
    _cancleButt  = static_cast<UIButton *>(_alert_root->getChildByName("cancel_butt"));
    _cancleButt->setTouchEnable(true);
    _confirmButt = static_cast<UIButton *>(_alert_root->getChildByName("sure_butt"));
    _confirmButt->setTouchEnable(true);
    _cancleButt->addTouchEventListener(this, toucheventselector(UIFUAlert::cancelButt));
    _textArea    = static_cast<UITextArea *>(_alert_root->getChildByName("tips_textArea"));
    
    return true;
}

void UIFUAlert::onEnter()
{
    this->CCLayerRGBA::onEnter();
    //....
    ActionObject *earth_action = ActionManager::shareManager()->getActionByName("GameAlertUI.ExportJson", "Animation0");
    
    if (earth_action != NULL)
    {
        earth_action->setLoop(false);
        earth_action->play();
    }
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
        {
            PLAY_EFFECT(TAP_EFFECT);
        }
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
        {ActionObject *earth_action = ActionManager::shareManager()->getActionByName("GameAlertUI.ExportJson", "Animation0");
            
            if (earth_action != NULL)
            {
                earth_action->setLoop(false);
                earth_action->play();
            }
//            this->removeFromParentAndCleanup(true);           //从父节点移除
        }
            
            break;
        case TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}

void UIFUAlert::confirmButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
        {
            PLAY_EFFECT(TAP_EFFECT);
        }
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

void UIFUAlert::boundCancelEvent(cocos2d::CCObject *target, SEL_TouchEvent selector)
{
    _cancleButt->addTouchEventListener(target, selector);
}

void UIFUAlert::boundConfirmEvent(cocos2d::CCObject *target, SEL_TouchEvent selector)
{
    _confirmButt->addTouchEventListener(target, selector);
}

void UIFUAlert::setTipsTextArea(const char *tips)
{
    _textArea->setText(tips);
}

