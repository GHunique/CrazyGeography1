//
//  UIControlLayer.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-14.
//
//

#ifndef __CrazyGeography__UIControlLayer__
#define __CrazyGeography__UIControlLayer__

#include "CGconfig.h"

class UIControlLayer : public CCLayerRGBA
{
public:
    
    CREATE_FUNC(UIControlLayer);
    UIControlLayer();
    ~UIControlLayer();
    bool init();
    void onEnter();
    void onExit();
private:
    UILayer *_conUILayer;
    Layout  *_control_root;
    
    UICheckBox *_silenceCBox;
    UISlider *_bgMusic_slider;
    UISlider *_efMusic_slider;
    
    CCDictionary *_setingInfo;    //设置配置表数据
    float _volume_bg;
    float _volume_eff;
    int  _silence;             //是否静音 1 静音;0 有声
    
    UILabel *showVolum;
    
private:
    void  quietCheckBox(UICheckBox *pSender,CheckBoxEventType type);
    float setBackGroundMusicVolum(UISlider *pSender,SliderEventType type);
    float setEffectMusicVolum(UISlider *pSender,SliderEventType type);
    void  backButt(UIButton *pSender,TouchEventType type);
    
    /**
     * @brief 保存背景音乐和音效数值到本地
     */
    void  comfirVolumSeting();
};

#endif /* defined(__CrazyGeography__UIControlLayer__) */
