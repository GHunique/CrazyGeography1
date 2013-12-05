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
    
    this->addChild(_iLayout);

    return true;
    
}

void GameInfoUI::setTextArea(const char *text)
{
    UIScrollView *scroll = static_cast<UIScrollView *>(_iLayout->getChildByName("scroll_view"));
    UITextArea *textArea = static_cast<UITextArea *>(scroll->getChildByName(""));
    
    textArea->setText(text);
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
            this->removeFromParentAndCleanup(true);
        }
            break;
        case TOUCH_EVENT_CANCELED:
            
            break;
        default:
            break;
    }
}

