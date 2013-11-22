//
//  AheadChapter.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-14.
//
//

#ifndef __CrazyGeography__AheadChapter__
#define __CrazyGeography__AheadChapter__

#include "CGconfig.h"

class AheadChapter : public CCLayerRGBA {

public:
    
    CREATE_FUNC(AheadChapter);
    AheadChapter();
    ~AheadChapter();
    bool init();
    void onEnter();
    void onExit();
private:
    UILayer *_aUILayer;
    Layout  *_ahead_root;
    
   
private:
    void startGame  (UIButton *pSender,TouchEventType type);
    void reSetGame  (UIButton *pSender,TouchEventType type);
    void settingGame(UIButton *pSender,TouchEventType type);
    
};

#endif /* defined(__CrazyGeography__AheadChapter__) */
