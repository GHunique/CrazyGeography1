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
//------
#include "CGShop.h"

#include "MacroDefine.h"


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
//            const char* animation_path = (CG_ANIMATION[kCGANIMATION_BASE_PATH] + CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME]+CG_ANIMATION[kCGDocument_SUFFIX]).c_str();
//            CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(animation_path);
//            
//            CCArmature *armature = CCArmature::create(CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME].c_str());
//                            armature->getAnimation()->playByIndex(0,-1,-1,0);
//            
//            armature->setPosition(ccp(0.5 * CG_ScreenSize.width,CG_ScreenSize.height * 0.45));
//            addChild(armature,19);
//            return;
//            GlobalUserDefault::instance()->buyCommodities("", "", 68, 1);

//            GlobalUserDefault::instance()->enterAccountManage();
            
//            GlobalUserDefault::instance()->unLockAchievement(1, 50, "我去这么好的游戏");
//            GlobalUserDefault::instance()->enterVirtualShop();
            CCScene *scene = CCScene::create();                 //添加场景
            CGShop *gameLayer = CGShop::create();               //章节
            scene->addChild(gameLayer);
            CCTransitionScene *transition = CCTransitionProgressInOut::create(0.2, scene);
            //        CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
            CCDirector::sharedDirector()->replaceScene(transition);
            
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
        {
                    }
            break;
        case TOUCH_EVENT_MOVED:
            break;
        case TOUCH_EVENT_ENDED:
        {
//            const char* animation_path = (CG_ANIMATION[kCGANIMATION_BASE_PATH] + CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME]+CG_ANIMATION[kCGDocument_SUFFIX]).c_str();
//            CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(animation_path);
//            
//            CCArmature *armature = CCArmature::create(CG_ANIMATION[kCGGoldJUMP_ANIMATION_NAME].c_str());
//            armature->getAnimation()->playByIndex(1,-1,-1,0);
//            
//            armature->setPosition(ccp(0.5 * CG_ScreenSize.width,CG_ScreenSize.height * 0.45));
//            addChild(armature,19);
//            return;
            
//            GlobalUserDefault::instance()->submitScoreTo91(1, 1, "用户获得了哈");
//            GlobalUserDefault::instance()->openScoreBoard(0);
//            GlobalUserDefault::instance()->openAchievement();
//            return;
            GlobalUserDefault::instance()->show91ToolBar(false);

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

void AheadChapter::onEnterTransitionDidFinish()
{
    //播放动作
    ActionObject *action = ActionManager::shareManager()->getActionByName("AheadChapterUI.ExportJson", "title_panel_animation");
    
    if (action != NULL)
        action->play();
    
    
    this->scheduleOnce(schedule_selector(AheadChapter::delayAnimation), 3.2);
}

void AheadChapter::delayAnimation()
{
    ActionObject  *action = ActionManager::shareManager()->getActionByName("AheadChapterUI.ExportJson", "map_animation");
    
    if (action != NULL)
    {
        action->play();
    }
}



