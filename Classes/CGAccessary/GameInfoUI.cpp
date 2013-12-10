//
//  GameInfoUI.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-12-5.
//
//

#include "GameInfoUI.h"

bool GameInfoUI::init()
{
    if (!Layout::init()) return false;
    
    _iLayout = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGameInfoUI].c_str()));
    
    UIButton *back = static_cast<UIButton *>(_iLayout->getChildByName("close_butt"));
    back->addTouchEventListener(this, toucheventselector(GameInfoUI::buttSelector));
    back->setZOrder(10);
    back->setPosition(ccpAdd(back->getPosition(), ccp(5,-5)));
    this->addChild(_iLayout);

    return true;
}

void GameInfoUI::setTextArea(const char *text)
{
    UIScrollView *scroll = static_cast<UIScrollView *>(_iLayout->getChildByName("scroll_view"));
    UITextArea *textArea = static_cast<UITextArea *>(scroll->getChildByName("info_textArea"));
    
    textArea->setText(text);
    
}

void GameInfoUI::setParent(cocos2d::extension::UIWidget *parent)
{
    parent->addChild(this);
    
    //冻结父类的触摸事件
    parent->setTouchEnable(false,true);
    
    //解冻本层及其子类
    _iLayout->setTouchEnable(true,true);

}

void GameInfoUI::buttSelector(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            
            break;
        case TOUCH_EVENT_MOVED:
            
            break;
        case TOUCH_EVENT_ENDED:
        {
            //解冻父类的触摸事件
            Layout *parent = static_cast<Layout *>(this->getParent());
            parent->setTouchEnable(true,true);
            this->removeFromParentAndCleanup(true);
        }
            break;
        case TOUCH_EVENT_CANCELED:
            
            break;
        default:
            break;
    }
}

