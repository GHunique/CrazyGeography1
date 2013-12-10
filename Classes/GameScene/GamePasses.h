//
//  GamePasses.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-19.
//
//

#ifndef __CrazyGeography__GamePasses__
#define __CrazyGeography__GamePasses__

#include "CGconfig.h"

class GamePasses : public CCLayerRGBA
{
public:
    CREATE_FUNC(GamePasses);
    GamePasses();
    ~GamePasses();
    
    bool init();
    void onEnter();
private:
    UILayer      *_pUILayer;
    Layout       *_pass_root;
    
    UIScrollView    *_scrollView;
    UILabelBMFont   *_passTitleLabel;
    
    CCPoint _firstPoint;
    CCSize  _passesInterval;
    
private:
    void passesLayout();                //生成,排列关卡按钮
    void gotoDirectlyGame(CCObject *pSender,TouchEventType type);           //进入指定关卡
    void backChapterLayer(UIButton *pSender,TouchEventType type);           //返回选择章节界面
    
    void delayAnimation(UIWidget *pSender,TouchEventType type);
};

#endif /* defined(__CrazyGeography__GamePasses__) */
