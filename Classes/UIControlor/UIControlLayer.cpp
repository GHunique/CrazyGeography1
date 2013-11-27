//
//  UIControlLayer.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-14.
//
//

#include "UIControlLayer.h"
#include "SimpleAudioEngine.h"
#include "XMLOperation.h"
#include "CGHelper.h"
#include "AheadChapter.h"
#include "GlobalUserDefault.h"

using namespace CocosDenshion;

#define SETTING_ID     "settingName" //uniqueID


#define VOLUME_NAME   "音量"          //uniqueID's value
#define SILENCE_NAME  "静音"


UIControlLayer::UIControlLayer()
{
    GlobalUserDefault::instance()->show91ToolBar(true);
}

UIControlLayer::~UIControlLayer()
{
    CC_SAFE_RELEASE_NULL(_setingInfo);
    
    CCLog("设置释放 内存了....设置释放 内存了....设置释放 内存了....设置释放 内存了....设置释放 内存了....");
}

bool UIControlLayer::init()
{
    if (!CCLayerRGBA::init()) return false;
    
    _conUILayer = UILayer::create();
    this->addChild(_conUILayer);
    
    _control_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kControlerUI_volume].c_str()));
    _conUILayer->addWidget(_control_root);
    
//    _setingInfo = XMLOperation::xmlDicSwitchToCCDic1(CG_GAME_DATA[kGD_SETTING_MXL].c_str(),SETTING_ID);
    std::string filePath = GlobalUserDefault::instance()->makeCacheFileData(CG_GAME_DATA[kGD_SETTING_MXL]);
    _setingInfo = XMLOperation::xmlDicSwitchToCCDic1(filePath.c_str(),SETTING_ID,true);
    CC_SAFE_RETAIN(_setingInfo);
    CCDictionary *volume_dic = static_cast<CCDictionary *>(_setingInfo->objectForKey(VOLUME_NAME));
    CCDictionary *silence_dic = static_cast<CCDictionary *>(_setingInfo->objectForKey(SILENCE_NAME));
    
    _silenceCBox = static_cast<UICheckBox *>(_control_root->getChildByName("silence_checkBox"));
    _silenceCBox->setTouchEnable(true);
    _silenceCBox->addEventListener(this, checkboxselectedeventselector(UIControlLayer::quietCheckBox));
    
    _bgMusic_slider = static_cast<UISlider *>(_control_root->getChildByName("backMusic_slider"));
    _bgMusic_slider->setTouchEnable(true);
    _bgMusic_slider->addEventListener(this, sliderpercentchangedselector(UIControlLayer::setBackGroundMusicVolum));
    
    _efMusic_slider = static_cast<UISlider *>(_control_root->getChildByName("effectMusic_slider"));
    _efMusic_slider->setTouchEnable(true);
    _efMusic_slider->addEventListener(this, sliderpercentchangedselector(UIControlLayer::setEffectMusicVolum));
    
    UIButton *back_butt = static_cast<UIButton *>(_control_root->getChildByName("back_butt"));
    back_butt->setTouchEnable(true);
    back_butt->addTouchEventListener(this, toucheventselector(UIControlLayer::backButt));
    
    _volume_bg  = static_cast<CCString *>(volume_dic->objectForKey("volume_bg"))->floatValue();
    _volume_eff = static_cast<CCString *>(volume_dic->objectForKey("volume_eff"))->floatValue();
    _silence  = static_cast<CCString *>(silence_dic->objectForKey("silence"))->intValue();
    
    showVolum = UILabel::create();
    showVolum->setPosition(ccp(300,400));
    _conUILayer->addWidget(showVolum);
    
    return true;
}

void UIControlLayer::onEnter()
{
    CCLayerRGBA::onEnter();
    //....
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(_volume_eff);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_volume_bg);
    
    //设置各个参数
    _bgMusic_slider->setPercent(_volume_bg*100);
    _efMusic_slider->setPercent(_volume_eff*100);
    if (_silence) _silenceCBox->setSelectedState(true);
    else _silenceCBox->setSelectedState(false);
    
    CCString *volume_str = (CCString::createWithFormat("satrt 背景音乐:%f -- 音效音量:%f",_volume_bg,_volume_eff));
    showVolum->setText(volume_str->getCString());
}

void UIControlLayer::onExit()
{
    
    comfirVolumSeting();
    //。。。。。。
    CCLayerRGBA::onExit();
}

#pragma mark - public

#pragma mark - private
void UIControlLayer::quietCheckBox(cocos2d::extension::UICheckBox *pSender, CheckBoxEventType type)
{
    switch (type)
    {
        case cocos2d::extension::CHECKBOX_STATE_EVENT_SELECTED:
        {
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
            _silence = 1;
            showVolum->setText("静音了的喔。。。。");
        }
            break;
        case cocos2d::extension::CHECKBOX_STATE_EVENT_UNSELECTED:
        {
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(_volume_eff);
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_volume_bg);
            _silence = 0;
            showVolum->setText("开启声音了的！！！");
        }
            break;
        default:
            break;
    }
}

float UIControlLayer::setBackGroundMusicVolum(cocos2d::extension::UISlider *pSender,SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            float volum_value = pSender->getPercent();
            _volume_bg = volum_value/100.0f;
//            CCDictionary *volume_dic = static_cast<CCDictionary *>(_setingInfo->objectForKey(VOLUME_NAME));
//            _volume_bg  = static_cast<CCString *>(volume_dic->objectForKey("volume_bg"))->floatValue();
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_volume_bg);
            CCLog("我的游戏音乐音量:%f",_volume_bg);
            CCString *volume_str = (CCString::createWithFormat("bg 背景音乐:%f -- 音效音量:%f",_volume_bg,_volume_eff));
            showVolum->setText(volume_str->getCString());
            
        }
            break;
            
        default:
            break;
    }
    
    return _volume_bg;
}

float UIControlLayer::setEffectMusicVolum(cocos2d::extension::UISlider *pSender,SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            float volum_value = pSender->getPercent();
            _volume_eff = volum_value/100.0f;
//            CCDictionary *volume_dic = static_cast<CCDictionary *>(_setingInfo->objectForKey(VOLUME_NAME));
//            _volume_eff = static_cast<CCString *>(volume_dic->objectForKey("volume_eff"))->floatValue();
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(_volume_eff);
            CCLog("我的游戏 特效 音量:%f",_volume_eff);
            CCString *volume_str = (CCString::createWithFormat("eff 背景音乐:%f -- 音效音量:%f",_volume_bg,_volume_eff));
            showVolum->setText(volume_str->getCString());
        }
            break;
            
        default:
            break;
    }
    
    return _volume_eff;
}

void UIControlLayer::backButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
        
    }else if(type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        CCScene *scene = CCScene::create();
        AheadChapter *layer = AheadChapter::create();
        scene->addChild(layer);
        
        CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}

void UIControlLayer::comfirVolumSeting()
{
    //volume_bg="0.34" volume_eff
    std::string volum_bg_str  = CGHelper::getstring(_volume_bg);
    std::string volum_eff_str = CGHelper::getstring(_volume_eff);
    
    std::string settingPath = GlobalUserDefault::instance()->makeCacheFileData(CG_GAME_DATA[kGD_SETTING_MXL]);
    XMLOperation::fixAttribute1(settingPath.c_str(),VOLUME_NAME,"volume_bg", volum_bg_str.c_str(),SETTING_ID,true); //最后的参数 true 表示传入的是绝对路径
    XMLOperation::fixAttribute1(settingPath.c_str(), VOLUME_NAME, "volume_eff", volum_eff_str.c_str(),SETTING_ID,true);
    
    //设置静音状态
    std::string silence_str = CGHelper::getstring(_silence);
    XMLOperation::fixAttribute1(settingPath.c_str(), SILENCE_NAME, "silence", silence_str.c_str(),SETTING_ID,true);
}


