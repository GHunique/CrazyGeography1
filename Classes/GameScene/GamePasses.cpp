//
//  GamePasses.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-19.
//
//

#include "GamePasses.h"
#include "GlobalUserDefault.h"
#include "CGAccessaryButton.h"
#include "CGHelper.h"
#include "GameLayer.h"
#include "ChapterLayer.h"

GamePasses::GamePasses()
{
    _firstPoint = ccp(30,600);
    _passesInterval = CCSizeMake(120, 130);
}

GamePasses::~GamePasses()
{
    
}

bool GamePasses::init()
{
    if (!CCLayerRGBA::init()) return false;
    
    _pUILayer = UILayer::create();
    _pUILayer->scheduleUpdate();
    this->addChild(_pUILayer);
    
    _pass_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGamePassesUI].c_str()));
    _pUILayer->addWidget(_pass_root);
    
    _scrollView = static_cast<UIScrollView *>(_pass_root->getChildByName("ScrollView"));
    _scrollView->setZOrder(10);
    _scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    
    _passTitleLabel = static_cast<UILabelBMFont *>(_pass_root->getChildByName("title_BMFLabel"));
    //gameTitle_BMF 电梯图标
    this->passesLayout();
    
    UIButton *backButt = static_cast<UIButton *>(_pass_root->getChildByName("back_butt"));
    backButt->setTouchEnable(true);
    backButt->addTouchEventListener(this, toucheventselector(GamePasses::backChapterLayer));
    
    UILabelBMFont *game_title_BMF = static_cast<UILabelBMFont *>(_pass_root->getChildByName("gameTitle_BMF"));
    game_title_BMF->setTouchEnable(true);
    game_title_BMF->addTouchEventListener(this, toucheventselector(GamePasses::delayAnimation));
    
    return true;
}

void GamePasses::onEnter()
{
    CCLayerRGBA::onEnter();
}

#pragma mark - private Methods

void GamePasses::passesLayout()
{
    CCDictionary * mapDic = GlobalUserDefault::instance()->currPassInfomation();
    _passTitleLabel->setText(GlobalUserDefault::instance()->getCurrentChapterName().c_str());
    int passed_pass = GlobalUserDefault::instance()->getPassedPass(); //获得已经过关的关卡id
    
    CCDictElement *element;
    int pass_id = 0;               //当前章节号
    int row = 0,col = 0;
    int passNum_perRow = 4;
    int totalPasses_perPage = 16;
    int passesAmount = 0;           //章节总数量
    
    CCSize viewSize = _scrollView->getSize();
    CCSize innerSize = _scrollView->getInnerContainerSize();
    
    CCDICT_FOREACH(mapDic, element)
    {
        CCDictionary *passInfoDic = (CCDictionary *)element->getObject();
        
        int game_id = ((CCString*)((passInfoDic->objectForKey("id"))))->intValue();
        CCLog("一个章节中的关卡数 %d passid %d",mapDic->count(),game_id);
        if (game_id == 0)
        {
            continue;
        }
        
        pass_id = game_id - 1;
        row = pass_id/passNum_perRow;
        col = pass_id%passNum_perRow;
        
        CCPoint buttPoint = ccpAdd(_firstPoint, ccp(_passesInterval.width * col,-_passesInterval.height * row));
        
        if (pass_id >= totalPasses_perPage)
            buttPoint = ccp(buttPoint.x + viewSize.width,buttPoint.y + _passesInterval.height * totalPasses_perPage/passNum_perRow);
        
        
        if (game_id <= passed_pass)
        {
            PassButton *passButt = PassButton::create();
            int starNum = ((CCString*)((passInfoDic->objectForKey("star"))))->intValue();
            passButt->setStarNumber(starNum);
            passButt->setShortName(CGHelper::getChar(game_id));
            passButt->setPosition(buttPoint);
            passButt->setPassId(game_id);             //将要进入的关卡
            
            passButt->setCGButtonTouchEnable(true);
            passButt->addCGButtonTouchEventListener(this, toucheventselector(GamePasses::gotoDirectlyGame));
            _scrollView->addChild(passButt);
        }else
        {
            NotPassButton *nPassButt = NotPassButton::create();
            nPassButt->setCGButtonTouchEnable(false);
            
            nPassButt->setPosition(buttPoint);
            _scrollView->addChild(nPassButt);
        }
        
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

void GamePasses::gotoDirectlyGame(cocos2d::CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
        {
             PLAY_EFFECT(TAP_EFFECT);
        }
            break;
        case TOUCH_EVENT_MOVED:
        {
          
        }
            
            break;
        case TOUCH_EVENT_ENDED:
        {
            UIButton *butt = static_cast<UIButton *>(pSender);
            PassButton *passButt = static_cast<PassButton *>(butt->getParent());
            GlobalUserDefault::instance()->setCurrentPass(passButt->getPassId()); //设置进入关卡
            CCLog("关卡 id %d",passButt->getPassId());
            
            CCScene *scene = CCScene::create();
            GameLayer *game = GameLayer::create();
            scene->addChild(game);
            
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

void GamePasses::backChapterLayer(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
        {
             PLAY_EFFECT(TAP_EFFECT);
        }
            break;
        case TOUCH_EVENT_MOVED:
            
            break;
        case TOUCH_EVENT_ENDED:
        {
            CCScene *scene = CCScene::create();
            ChapterLayer *layer = ChapterLayer::create();
            scene->addChild(layer);
            
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


#pragma mark - delayAnimation

void GamePasses::delayAnimation(cocos2d::extension::UIWidget *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN) {
        ActionObject *actionObje = ActionManager::shareManager()->getActionByName("GamePassesUI.ExportJson", "game_Title_BMF_Animation");
        
        if (actionObje != NULL)
        {
            actionObje->setLoop(false);
            actionObje->play();
        }
    }
}



