//
//  ChapterLayer.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-12.
//
//

#ifndef __CrazyGeography__ChapterLayer__
#define __CrazyGeography__ChapterLayer__

#include "CGconfig.h"

class  ChapterLayer : public CCLayerRGBA
{
public:
    CREATE_FUNC(ChapterLayer);
    ChapterLayer();
    ~ChapterLayer();
    
    bool init();
    void onEnter();
    void onExit();
private:
    UILayer      *_cUILayer;
    Layout       *_chapter_root;
    UIScrollView *_scrollView;          //滚动层
    
    CCPoint _firstPoint;
    CCSize  _passesInterval;
    
private:
    void provincesLayout();
    void gotoDirectlyPass(CCObject *pSender,TouchEventType type);
};

#endif /* defined(__CrazyGeography__ChapterLayer__) */
