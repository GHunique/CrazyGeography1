//
//  SuccessLayer.cpp
//  CrazyGeography
//
//  Created by yong on 13-11-2.
//
//

#include "SuccessLayer.h"
#include "CGHelper.h"
#include "GameLayer.h"
#include "GlobalUserDefault.h"
#include "MacroDefine.h"

#include "EffectSoundPlayController.h"


SuccessLayer::SuccessLayer()
{
    
}

SuccessLayer::~SuccessLayer()
{
    
}

bool SuccessLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    _sUILayer = UILayer::create();
    _sUILayer->scheduleUpdate();
    addChild(_sUILayer);
    
    _rootLayout = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGameSuccessUI].c_str()));
    _rootLayout->setBackGroundColor(ccBLACK);
    _rootLayout->setOpacity(255);
    _sUILayer->addWidget(_rootLayout);
    
    UIButton *share_butt = static_cast<UIButton *>(_rootLayout->getChildByName("share_butt"));
    share_butt->setTouchEnable(true);
    share_butt->addTouchEventListener(this, toucheventselector(SuccessLayer::shareButt));
    
    UIButton *next_butt = static_cast<UIButton *>(_rootLayout->getChildByName("next_butt"));
    next_butt->setTouchEnable(true);
    next_butt->addTouchEventListener(this, toucheventselector(SuccessLayer::nextButt));
    
    return true;
}

void SuccessLayer::onEnter()
{
    CCLayer::onEnter();
    
    //
}

void SuccessLayer::onExit()
{
    
    //
    CCLayer::onExit();
    
}

void SuccessLayer::shareButt(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    
    if (type == TOUCH_EVENT_BEGAN)
    {
        PLAY_EFFECT(TAP_EFFECT);
    }else if(type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        
    }
}

void SuccessLayer::nextButt(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    
    if (type == TOUCH_EVENT_BEGAN)
    {
      PLAY_EFFECT(TAP_EFFECT);
    }else if(type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        CCScene *scene = CCScene::create();                 //添加场景
        GameLayer *gameLayer = GameLayer::create();
        scene->addChild(gameLayer);
        
        CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}

void SuccessLayer::setSuccessData(Map_str_str &dic)
{
    _dic = dic;
    this->scheduleOnce(schedule_selector(SuccessLayer::actionOfSuccessEffect),1);
    
}

void SuccessLayer::actionOfSuccessEffect()
{
    //设置奖励
    UILabel *jiangli_label = static_cast<UILabel *>(_rootLayout->getChildByName("jiangli_label"));
    
    char charData[2];
    sprintf(charData, "x  %s",_dic.at("jiangli").c_str());
    jiangli_label->setText(charData);
    
    //设置答案
    UILabel *answer_label = static_cast<UILabel *>(_rootLayout->getChildByName("answer_label"));
    //    sprintf(charData, "",)
    answer_label->setText(_dic.at("answer").c_str());
    
    //初始化星级
    
    for (int i = 2; i <= 3; i++)
    {
        std::string xingName = "xingxing_image_";
        xingName.append(CGHelper::getChar(i));
        
        UIImageView *xingImage = static_cast<UIImageView *>(_rootLayout->getChildByName(xingName.c_str()));
        xingImage->setTexture("xing-xing0.png",UI_TEX_TYPE_PLIST);
        
    }
    
    //设置星级
    int xingshu =  CGHelper::getint(_dic.at("xingshu"));
    
    cout<<xingshu<<"  星数量"<<std::endl;
    for (int i = 2; i <= xingshu; i++)
    {
        std::string xingName = "xingxing_image_";
        xingName.append(CGHelper::getChar(i));
        
        UIImageView *xingImage = static_cast<UIImageView *>(_rootLayout->getChildByName(xingName.c_str()));
        xingImage->setTexture("xing-xing1.png",UI_TEX_TYPE_PLIST);
        
    }
    
    //通关所用时间
    UILabel *used_time_label = static_cast<UILabel *>(_rootLayout->getChildByName("time_label"));
    std::string time_str = " " + _dic.at("shijian") + " 秒";
    used_time_label->setText(time_str.c_str());
    
    //显示特效
        
    const char* animation_path = (CG_ANIMATION[kCGANIMATION_BASE_PATH] + CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME]+CG_ANIMATION[kCGDocument_SUFFIX]).c_str();
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(animation_path);
    
    CCArmature *armature = CCArmature::create(CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME].c_str());
    if (xingshu >2)
    {
        armature->getAnimation()->playByIndex(0,-1,-1,0);
        
    }else if(xingshu > 1)
    {
        armature->getAnimation()->playByIndex(1,-1,-1,0);
    }else
    {
       armature->getAnimation()->playByIndex(1,-1,-1,0);
    }
    
    //播放音效
    EffectSoundPlayController *ESPC = EffectSoundPlayController::create();
    this->addChild(ESPC);
    ESPC->setEffect(DU_EFFECT, 1, 0.5, 0);
    //音效播放
    
    
    armature->setPosition(ccp(0.5 * CG_ScreenSize.width,CG_ScreenSize.height * 0.45));
//    addChild(armature,19,11221);
    
    this->scheduleOnce(schedule_selector(SuccessLayer::removeCCArmature), 2.5);

}

void SuccessLayer::removeCCArmature()
{
    this->removeChildByTag(11221, true);
}

