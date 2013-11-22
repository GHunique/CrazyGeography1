//
//  AheadChapter.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-14.
//
//

#include "AheadChapter.h"
#include "ChapterLayer.h"
#include "GlobalUserDefault.h"
#include "UIControlLayer.h"
#include "DataBase64Himi.h"


AheadChapter::AheadChapter()
{
    
}

AheadChapter::~AheadChapter()
{
    
}

bool AheadChapter::init()
{
    if (!CCLayerRGBA::init()) return false;
    
    _aUILayer = UILayer::create();
    this->addChild(_aUILayer);
    
    _ahead_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kAheadChapter].c_str()));
    _aUILayer->addWidget(_ahead_root);
    
    UIButton *startButt = static_cast<UIButton *>(_ahead_root->getChildByName("start_butt"));
    startButt->setTouchEnable(true);
    startButt->addTouchEventListener(this, toucheventselector(AheadChapter::startGame));
    
    UIButton *resetButt = static_cast<UIButton *>(_ahead_root->getChildByName("reset_butt"));
    resetButt->setTouchEnable(true);
    resetButt->addTouchEventListener(this, toucheventselector(AheadChapter::reSetGame));
    
    UIButton *settingButt = static_cast<UIButton *>(_ahead_root->getChildByName("setting_butt"));
    settingButt->setTouchEnable(true);
    settingButt->addTouchEventListener(this, toucheventselector(AheadChapter::settingGame));
    
    return true;
}

void AheadChapter::onEnter()
{
    CCLayerRGBA::onEnter();
    //。。。。。
}

void AheadChapter::onExit()
{
    //....
    CCLayerRGBA::onExit();
}

#pragma mark - public

#pragma mark - private

void AheadChapter::startGame(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
        {
            CCScene *scene = CCScene::create();                         //添加场景
            ChapterLayer *chapterLayer = ChapterLayer::create();        //章节
            scene->addChild(chapterLayer);
//            CCTransitionScene *transition = CCTransitionProgressVertical::create(0.2, scene);
            CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
            CCDirector::sharedDirector()->replaceScene(transition);
        }
            break;
        case TOUCH_EVENT_CANCELED:
        {
            
        }
            break;
        default:
            break;
    }
}

void AheadChapter::reSetGame(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
        {
            
            GlobalUserDefault::instance()->sharedGame(0);
//            int iKey = 2;
//            std::string sValue = "此项目已存在保存数据的xml文件";
//            char buffer[32];
//            sprintf(buffer, "%s%d", "Himi",iKey);
//            CCLog("----------存储");
//            CCLog("存储之前数据 key：index: Himi%i, value: %s  ",iKey,sValue.c_str());
//            string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
//            CCLog("存储加密后的数据 key：index: Himi%i, value: %s  ",iKey,sKey.c_str());
//            CCUserDefault::sharedUserDefault()->setStringForKey(buffer, sKey);
//            CCUserDefault::sharedUserDefault()->flush();
            
            
        }
            break;
        case TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}

void AheadChapter::settingGame(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
        {
            CCScene *scene = CCScene::create();                         //添加场景
            UIControlLayer *gameLayer = UIControlLayer::create();        //章节
            scene->addChild(gameLayer);
            
            CCDirector::sharedDirector()->replaceScene(scene);
        }
            break;
        case TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}




