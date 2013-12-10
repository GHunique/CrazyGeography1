//
//  GameInfoUI.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-12-5.
//
//

#ifndef __CrazyGeography__GameInfoUI__
#define __CrazyGeography__GameInfoUI__

#include "CGconfig.h"

class GameInfoUI : public Layout
{
public:
    
    CREATE_FUNC(GameInfoUI);
    bool init();
    
    void setTextArea(const char* text);
    void setParent(UIWidget *parent);
    
private:
    
    Layout *_iLayout;
    void buttSelector(UIButton *pSender,TouchEventType type);
};

#endif /* defined(__CrazyGeography__GameInfoUI__) */
