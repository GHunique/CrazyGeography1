//
//  ChapterLayer.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-12.
//
//

#include "ChapterLayer.h"
#include "GamePasses.h"
#include "GlobalUserDefault.h"
#include "CGAccessaryButton.h"
#include "AheadChapter.h"

ChapterLayer::ChapterLayer()
{
    _firstPoint = ccp(70,600);
    _passesInterval = CCSizeMake(120, 130);
}

ChapterLayer::~ChapterLayer()
{
    
}

bool ChapterLayer::init()
{
    if (!CCLayerRGBA::init()) return false;
    
    _cUILayer = UILayer::create();
    _cUILayer->scheduleUpdate();
    this->addChild(_cUILayer);
    
    _chapter_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGameChapterLayerUI].c_str()));
    _cUILayer->addWidget(_chapter_root);
    
    _scrollView = static_cast<UIScrollView *>(_chapter_root->getChildByName("ScrollView"));
    _scrollView->setZOrder(10);
    _scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    
    UIButton *back_butt_1 = static_cast<UIButton *>(_chapter_root->getChildByName("back_butt_1"));
    back_butt_1->setTouchEnable(true);
    back_butt_1->addTouchEventListener(this, toucheventselector(ChapterLayer::gotoAheadLayer));
    UIButton *back_butt_2 = static_cast<UIButton *>(_chapter_root->getChildByName("back_butt_2"));
    back_butt_2->setTouchEnable(true);
    back_butt_2->addTouchEventListener(this, toucheventselector(ChapterLayer::gotoAheadLayer));
    
    UIButton *back_butt_3 = static_cast<UIButton *>(_chapter_root->getChildByName("back_butt_3"));
    back_butt_3->setTouchEnable(true);
    back_butt_3->addTouchEventListener(this, toucheventselector(ChapterLayer::gotoAheadLayer));
    
    this->provincesLayout();
    
    return true;
}

void ChapterLayer::onEnter()
{
    this->CCLayerRGBA::onEnter();
    //.....
}

void ChapterLayer::onExit()
{
    //....
    this->CCLayerRGBA::onExit();
}

#pragma mark - private Methods

void ChapterLayer::provincesLayout()
{
    CCDictionary * mapDic = GlobalUserDefault::instance()->getChapterInfo();
    int passed_chapter = GlobalUserDefault::instance()->getPassedChapter();
    
    CCDictElement *element;
    int chapter_id = 0;               //当前章节号
    int row = 0,col = 0;
    int passNum_perRow = 4;
    int totalPasses_perPage = 16;
    int passesAmount = 0;           //章节总数量
    
    CCSize viewSize = _scrollView->getSize();
    CCSize innerSize = _scrollView->getInnerContainerSize();
    
    CCDICT_FOREACH(mapDic, element)
    {
        CCDictionary *passInfoDic = (CCDictionary *)element->getObject();
        
        int pass_id = ((CCString*)((passInfoDic->objectForKey("id"))))->intValue();
        CCLog("所大红我们不着调也是好的 %d passid %d",mapDic->count(),pass_id);
        if (pass_id == 0)
        {
            continue;
        }
        
        chapter_id = pass_id - 1;
        row = chapter_id/passNum_perRow;
        col = chapter_id%passNum_perRow;
        
        CCPoint buttPoint = ccpAdd(_firstPoint, ccp(_passesInterval.width * col,-_passesInterval.height * row));
        
        if (chapter_id >= totalPasses_perPage)
            buttPoint = ccp(buttPoint.x + viewSize.width,buttPoint.y + _passesInterval.height * totalPasses_perPage/passNum_perRow);
        
        ProvinceButton *probutt = ProvinceButton::create();
        int starNum = ((CCString*)((passInfoDic->objectForKey("star"))))->intValue();
        probutt->setStarNumber(starNum);
        probutt->setShortName(((CCString*)((passInfoDic->objectForKey("shortName"))))->getCString());
        probutt->setPosition(buttPoint);
        probutt->setChapterId(pass_id);             //将要进入的章节
        
        if (pass_id <= passed_chapter)
        {
            probutt->setCGButtonTouchEnable(true);
            probutt->addCGButtonTouchEventListener(this, toucheventselector(ChapterLayer::gotoDirectlyPass));
        }else
        {
//            probutt->setOpacity(180);
            probutt->lock(true);
        }
        
//        probutt->setTouchEnable(true);
//        probutt->addTouchEventListener(this, toucheventselector(ChapterLayer::gotoDirectlyPass));
        _scrollView->addChild(probutt);
        passesAmount++;
    }
    
    int scroll_page ;
    if (passesAmount%totalPasses_perPage == 0) {
        scroll_page = passesAmount/totalPasses_perPage;
    }else
    {
        scroll_page = passesAmount/totalPasses_perPage + 1;
    }
    
    CCSize newSize = CCSizeMake(viewSize.width * scroll_page, viewSize.height);
    _scrollView->setInnerContainerSize(newSize);
}

void ChapterLayer::gotoDirectlyPass(CCObject *pSender, TouchEventType type)
{
    switch (type) {
        case TOUCH_EVENT_BEGAN:
            
            break;
        case TOUCH_EVENT_MOVED:
            
            break;
        case TOUCH_EVENT_ENDED:
        {
            UIButton *butt = static_cast<UIButton *>(pSender);
            ProvinceButton *proButt = static_cast<ProvinceButton *>(butt->getParent());
            GlobalUserDefault::instance()->setCurrentChapter(proButt->getChapterId()); //设置进入章节
            CCLog("章节id %d",proButt->getChapterId());
            
            CCScene *scene = CCScene::create();                 //添加场景
            GamePasses *gamePass = GamePasses::create();
            scene->addChild(gamePass);
            CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
            CCDirector::sharedDirector()->replaceScene(transition);
        }
            break;
        case TOUCH_EVENT_CANCELED:
            
            break;
        default:
            break;
    }
}

void ChapterLayer::gotoAheadLayer(cocos2d::extension::UIButton *pSender, TouchEventType tyep)
{
    switch (tyep) {
        case cocos2d::extension::TOUCH_EVENT_ENDED:
        {
            CCScene *scene = CCScene::create();                 //添加场景
            AheadChapter *gameLayer = AheadChapter::create();
            scene->addChild(gameLayer);
            
            CCTransitionScene *transition = CCTransitionProgressVertical::create(0.2, scene);
            CCDirector::sharedDirector()->replaceScene(transition);
        }
            break;
            
        default:
            break;
    }
}







