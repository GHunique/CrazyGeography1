//
//  GameLayer.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-10-29.
//
//

#include "GameLayer.h"
#include "CGconfig.h"
#include "CGHelper.h"
#include "XMLOperation.h"
#include "MacroDefine.h"
#include "GamePasses.h"
#include "GlobalUserDefault.h"
#include "CGShop.h"
#include "UIFUAlert.h"
#include "GameInfoUI.h"

using namespace std;

GameLayer::GameLayer()
:_directlyCandidateDic(NULL)
{
    CG_FISTANBUTT_POINT        = CCPointMake(56, 70);
    CG_ANSWER_BUTT_SPACE_SIZE = CCSizeMake(75, 80);
    CG_ANSWER_SELECTED_FIRST_POINT  = CCSizeMake(220, 350); //后面计算得到起始x值
    CG_ANSWER_SELECTED__SPACE_SIZE   = CCSizeMake(60, 0);
    CG_PROCESS_DIVISION_SHOW_POINT  = CCPointMake(80, 360);
    
    CG_MAX_ANSWER_NUMBER = 0;
    CG_ENGLISH_ANSWER_NUMBER = 0;
    GlobalUserDefault::instance()->show91ToolBar(false);
}

GameLayer::~GameLayer()
{
//    CC_SAFE_RELEASE_NULL(_candidateAnswerDic);
    GlobalUserDefault::instance()->show91ToolBar(true);
}

bool GameLayer::init()
{
    if (!CCLayer::init()) return false;
    
    _yUILayer = UILayer::create();
    _yUILayer->scheduleUpdate();
    addChild(_yUILayer,1);
    
    _play_root = static_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGameLayerUI].c_str()));
//    _play_root->setEnabled(false);
    this->setOpacity(150);
    _yUILayer->addWidget(_play_root);
    
    //返回到选关界面按钮
    UIButton *fanhui_butt = static_cast<UIButton *>(_play_root->getChildByName("fanhui_butt"));
    fanhui_butt->setTouchEnable(true);
    fanhui_butt->setZOrder(4);
    fanhui_butt->addTouchEventListener(this,toucheventselector(GameLayer::fanHuiButt));
    
    //获得金币按钮
    UIButton *getGold_butt = static_cast<UIButton *>(_play_root->getChildByName("getGold_butt"));
    getGold_butt->setTouchEnable(true);
    getGold_butt->setZOrder(4);
    getGold_butt->addTouchEventListener(this, toucheventselector(GameLayer::getGoldButt));
    
    //帮组按钮
    UIButton *help_butt = static_cast<UIButton *>(_play_root->getChildByName("help_butt"));
    help_butt->setTouchEnable(true);
    help_butt->addTouchEventListener(this, toucheventselector(GameLayer::helpButt));
    
    //分享按钮
    UIButton *share_butt = static_cast<UIButton *>(_play_root->getChildByName("share_butt"));
    share_butt->setTouchEnable(true);
    share_butt->addTouchEventListener(this, toucheventselector(GameLayer::shareButt));
    
    //跳过按钮
    UIButton *next_butt = static_cast<UIButton *>(_play_root->getChildByName("next_butt"));
    next_butt->setTouchEnable(true);
    next_butt->addTouchEventListener(this, toucheventselector(GameLayer::nextButt));
    
    
    UIButton *game_info = static_cast<UIButton *>(_play_root->getChildByName("gameInfo_butt"));
    game_info->setTouchEnable(true);
    game_info->addTouchEventListener(this, toucheventselector(GameLayer::gameInfo));
    
    //答案界面层
    _answerLayer = static_cast<Layout *>(_play_root->getChildByName("answer_layer"));
    _answerLayer->setZOrder(2);
    
    //答案图片提示层
    _imageLayer = static_cast<Layout *>(_play_root->getChildByName("image_layer"));
    
    _answerLabel = UILabel::create();
    _answerLabel->setText("");
    _answerLabel->setPosition(ccp(400, 500));
    _yUILayer->addWidget(_answerLabel);
    
//    _processShow = UILabelBMFont::create();
//    _processShow->setFntFile("CGFont_Didot.fnt");
//    _processShow->setPosition(CG_PROCESS_DIVISION_SHOW_POINT);
//    _yUILayer->addWidget(_processShow);
   
    _processShow = static_cast<UILabelBMFont *>(_play_root->getChildByName("process_BMFLabel"));
    
    _gameGold_BMF = static_cast<UILabelBMFont *>(_play_root->getChildByName("gameGold_BMFLabel"));
    
    _gold_label = static_cast<UILabel *>(_play_root->getChildByName("gold_Label"));
    _gold_label->setText(CGHelper::getChar(GlobalUserDefault::instance()->getGameGold()));
    
    return true;
}

void GameLayer::onEnter()
{
    cocos2d::CCLayer::onEnter();
    
    this->refreshGameData();                                    //设置游戏参数
    
    //当前系统时间
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    _start_cd_seconds = now.tv_sec;
    _startCD = true;
    _total_award_cd = CG_GAME_CD_LV1;
    this->scheduleUpdate();             //启动计时器
    
    
    //设置金币
    int gold_int = GlobalUserDefault::instance()->getGameGold();
//    _gameGold_BMF->setText(CGHelper::getChar(gold_int));

}

void GameLayer::onExit()
{
    //
    cocos2d::CCLayer::onExit();
}

#pragma mark - protected methods

void GameLayer::fanHuiButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
      PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED)
    {
        CCLog(" begin = end = 0 总长:%ld", _standardAnswer.length());
        begin = end = 0;
        
        CCScene *scene = CCScene::create();                 //添加场景
        GamePasses *gamePass = GamePasses::create();
        scene->addChild(gamePass);
        CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
        CCDirector::sharedDirector()->replaceScene(transition);

    }
}

void GameLayer::getGoldButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
       
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED)
    {
         CCLog("(end ++ --),%d",end + 1);
        end++;
        
        CCScene *scene = CCScene::create();                 //添加场景
        CGShop *gameLayer = CGShop::create();               //章节
        scene->addChild(gameLayer);
        CCTransitionScene *transition = CCTransitionProgressInOut::create(0.2, scene);
//        CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}

void GameLayer::helpButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
        PLAY_EFFECT(TAP_EFFECT);
        pSender->setOpacity(150);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        CCPoint movingPoint = pSender->getTouchMovePos();
        
        if (!pSender->hitTest(movingPoint))
        {
            CCLog(" 移除到外面了-----  ");
            pSender->setOpacity(255);
        }else {
            pSender->setOpacity(150);
        }
        
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED) {
        CCLog(" begin ++ ----- %d",begin + 1);
        pSender->setOpacity(255);
        begin++;
        
        UIFUAlert *alert = UIFUAlert::createWithFileName();
        addChild(alert, 1,11211);
        alert->boundCancelEvent(this, toucheventselector(GameLayer::oneCorrectButtCancel));
        alert->boundConfirmEvent(this, toucheventselector(GameLayer::oneCorrectButtConfirm));
        std::string cost_gold_str = "  您确定花费";
        cost_gold_str += CGHelper::getstring(kOneCorrectAswer_need)+"金币提示一个正确答案?";
        alert->setTipsTextArea(cost_gold_str.c_str());
        
        _play_root->setTouchEnable(false,true);         //取消界面中所有触摸事件
        
    }
}

void GameLayer::shareButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
        PLAY_EFFECT(TAP_EFFECT);
        pSender->setOpacity(150);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        CCPoint movingPoint = pSender->getTouchMovePos();
        
        if (!pSender->hitTest(movingPoint))
        {
            CCLog(" 移除到外面了-----  ");
            pSender->setOpacity(255);
        }else {
            pSender->setOpacity(150);
        }
        
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED) {
        pSender->setOpacity(255);
        
        GlobalUserDefault::instance()->sharedGame(0);       //分享
        
        if (end <= _standardAnswer.length()) {
            
            string str = _standardAnswer.substr(begin,end);
            cout<<"解释出来了嘛："<<begin<<" "<<end<<" = "<<str<<endl;
        }
        
    }
}

void GameLayer::nextButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
        PLAY_EFFECT(TAP_EFFECT);
        pSender->setOpacity(150);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        CCPoint movingPoint = pSender->getTouchMovePos();
        
        if (!pSender->hitTest(movingPoint))
        {
            CCLog(" 移除到外面了-----  ");
            pSender->setOpacity(255);
        }else {
            pSender->setOpacity(150);
        }
    }else if(type == TOUCH_EVENT_ENDED)
    {
       
        UIFUAlert *alert = UIFUAlert::createWithFileName();
        addChild(alert, 1,11211);
        alert->boundCancelEvent(this, toucheventselector(GameLayer::removeWrongButtCancel));
        alert->boundConfirmEvent(this, toucheventselector(GameLayer::removeWrongButtConfirm));
        std::string cost_gold_str = "  您确定花费";
        cost_gold_str += CGHelper::getstring(kRemoveAlterAswer_need)+"金币去掉一个错误答案?";
        alert->setTipsTextArea(cost_gold_str.c_str());
        
        _play_root->setTouchEnable(false,true);         //取消界面中所有触摸事件
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
//        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        exit(0);
#endif
#endif
    }
}

void GameLayer::gameInfo(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
      PLAY_EFFECT(TAP_EFFECT);
    }
    else if (type == TOUCH_EVENT_ENDED)
    {
        
        GameInfoUI *game_info = GameInfoUI::create();
        game_info->setTextArea("  紫禁城是中国明、清两代24个皇帝的皇宫。明朝第三位皇帝朱棣在夺取帝位后，决定迁都北京，即开始营造紫禁城宫殿，至明永乐十八年（1420年）落成。依照中国古代星象学说，紫微垣（即北极星）位于中天，乃天帝所居，天人对应，是以皇帝的居所又称紫禁城.紫禁城是中国明、清两代24个皇帝的皇宫。明朝第三位皇帝朱棣在夺取帝位后，决定迁都北京，即开始营造紫禁城宫殿，至明永乐十八年（1420年）落成。依照中国古代星象学说，紫微垣（即北极星）位于中天，乃天帝所居，天人对应，是以皇帝的居所又称紫禁城.紫禁城.");
        
        game_info->setZOrder(10);
        game_info->setParent(_play_root);
        
    }
}

void GameLayer::initAnswerLayer(std::vector<std::string> &StrVector)
{
    CCArray *answerChildren = _answerLayer->getChildren();
    
    _canAnsImageSize = static_cast<UIButton *>(answerChildren->objectAtIndex(0))->getContentSize();
    
    CCObject *obj_butt;
    
    int countPerRow = 8;
    int row = 0,col = 0;
    int currCount = 0;
    
    CCARRAY_FOREACH(answerChildren, obj_butt)
    {
        row = currCount / countPerRow;
        col = currCount % countPerRow;
        
        UIButton *anButt = (UIButton *)(obj_butt);
        anButt->setTouchEnable(true);
        anButt->addTouchEventListener(this,toucheventselector(GameLayer::answerButt));
        
        CCPoint buttPoint = CCPointMake(CG_FISTANBUTT_POINT.x + (CG_ANSWER_BUTT_SPACE_SIZE.width)* col, CG_FISTANBUTT_POINT.y + (CG_ANSWER_BUTT_SPACE_SIZE.height) * row);
        
        anButt->setPosition(buttPoint);
        
        std::string butt_titlt_str = StrVector.at(currCount);
        
        if (!CGHelper::isChineseChar(butt_titlt_str.c_str())) {
            anButt->setTitleFontSize(20);
        }
        
        anButt->setText(butt_titlt_str.c_str());
        currCount++;
    }
}

void GameLayer::answerButt(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(TAP_EFFECT);
        butt->setOpacity(150);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        CCPoint movingPoint = butt->getTouchMovePos();
        
        if (!butt->hitTest(movingPoint))
        {
            CCLog(" 移除到外面了-----  ");
            butt->setOpacity(255);
        }else {
            butt->setOpacity(150);
        }
        
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED)
    {
        CCLog(" 结束 ----- ");
        butt->setOpacity(255);
        butt->setColor(ccWHITE);
        
//        _answerLabel->setText(butt->getTitleText());
        
        this->layoutSelectedAnswer(butt);
        
    }
}

void GameLayer::answerSelectedButt(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(SWIPE_EFFECT);
        butt->setOpacity(150);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        CCPoint movingPoint = butt->getTouchMovePos();
        
        if (!butt->hitTest(movingPoint))
        {
            CCLog(" 移除到外面了-----  ");
            butt->setOpacity(255);
        }else {
            butt->setOpacity(150);
        }
        
        CCLog("(moving moving 移动)");
    }else if (type == TOUCH_EVENT_ENDED)
    {
        CCLog(" 结束 ----- ");
        butt->setOpacity(255);
        butt->setColor(ccWHITE);
        
//        _answerLabel->setText(butt->getTitleText());
        
        this->returnToOraginPlace(butt);                //重新打开答案按钮触摸事件
        
    }
}

void GameLayer::layoutSelectedAnswer(cocos2d::CCObject *pObj)       //选中到答案的按钮操作函数
{
    if ( _hState.getCount() >= CG_MAX_ANSWER_NUMBER) {
        return;
    }else
    {
        
        UIButton *butt = static_cast<UIButton *>(pObj);
        
        if (!_selectedAnswerArr.containsObject(butt))
        {
            _selectedAnswerArr.addObject(butt);         //添加到已经选择答案数组中
        }
        
//        butt->oldPoint = butt->getPosition();           //将此时坐标保存
        
        butt->addTouchEventListener(this, toucheventselector(GameLayer::answerSelectedButt));
        
        int holdIndex = _hState.getCloselyBlankIndex();
        
        _hState.setPartAnswer(butt->getTitleText());
 
        CCPoint p = ccp(CG_ANSWER_SELECTED_FIRST_POINT.x + CG_ANSWER_SELECTED__SPACE_SIZE.width * holdIndex,CG_ANSWER_SELECTED_FIRST_POINT.y);
    
        CCLog(" 答案<%s> holdindex:%d 将要去到的地方 (%f,%f) ",butt->getTitleText(),holdIndex,p.x,p.y);
        
        _hState.setOldPoint(butt->getPosition());
        
        butt->setPosition(p);

        _hState.setCloselyHoldClose();
        
        this->setProcessShow(_hState.getCount());
        
        if (_hState.getCount() == CG_MAX_ANSWER_NUMBER)         //调用判断答案函数
        {
            this->compareAnswer();
        }
        
    }
}

void GameLayer::returnToOraginPlace(cocos2d::CCObject *pObj)
{
    
    UIButton *butt = static_cast<UIButton *>(pObj);
    
    butt->addTouchEventListener(this, toucheventselector(GameLayer::answerButt));
    
    int holdIndex = (butt->getPosition().x - CG_ANSWER_SELECTED_FIRST_POINT.x) / CG_ANSWER_SELECTED__SPACE_SIZE.width;
    
    _hState.openHoldPlace(holdIndex);                //重新设置对饮索引未被占用
    
    butt->setPosition(_hState.getOldPoint(holdIndex));              //将此时坐标保存
    
    this->setProcessShow(_hState.getCount());
    
    for (int i = 0; i < _selectedAnswerArr.count(); i++) {
        UIButton * buttTmep = (UIButton *)_selectedAnswerArr.objectAtIndex(i);
        buttTmep->setColor(ccWHITE);
    }
    
    _selectedAnswerArr.removeObject(butt);
}

void GameLayer::setProcessShow(int pre)
{
    CCString *proStr = CCString::createWithFormat("%d/%d",pre,CG_MAX_ANSWER_NUMBER);
    
    _processShow->setText(proStr->getCString());
    
}

#pragma mark - compareAnswer Methods
void GameLayer::compareAnswer()
{
    std::string anSwer = _hState.getAnswerString();
    std::cout<<"打印出答案："<<anSwer<<std::endl;
    
    if (strcmp(anSwer.c_str(), _standardAnswer.c_str()) == 0)//匹配成功跳转到下一题目
    {
        std::cout<<"匹配成功  ："<<anSwer<<"  "<<_standardAnswer<<std::endl;
        _startCD = false;
        
        int passed = CCUserDefault::sharedUserDefault()->getIntegerForKey(CG_FINISHED_PASS);
        passed++;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(CG_FINISHED_PASS,passed);
        
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        long curr_seconds = now.tv_sec;
        _total_award_cd = curr_seconds - _start_cd_seconds;
        
        for (int i = 0; i < _selectedAnswerArr.count(); i++) {
            UIButton *butt = (UIButton *)_selectedAnswerArr.objectAtIndex(i);
            butt->setColor(ccGREEN);
        }
        
        this->scheduleOnce(schedule_selector(GameLayer::successfully), 1);
        
    }
    else{
        for (int i = 0; i < _selectedAnswerArr.count(); i++) {
            UIButton *butt = (UIButton *)_selectedAnswerArr.objectAtIndex(i);
            butt->setColor(ccRED);
        }
    }
}

#pragma mark - private methods

void GameLayer::refreshGameData()
{
    UILabelBMFont *title_label = static_cast<UILabelBMFont *>(_play_root->getChildByName("title_BMFLabel"));
    title_label->setText(GlobalUserDefault::instance()->getCurrentChapterName().c_str());
    
    _directlyCandidateDic = GlobalUserDefault::instance()->currPassInfo();
//    GlobalUserDefault::instance()->showDictionaryKeyAndValue(_directlyCandidateDic);
    
    CC_ASSERT(_directlyCandidateDic != NULL);
    
    // begin -- 得到备选答案字符串
    std::string candidate_answer_str =
    ((CCString *)(_directlyCandidateDic->objectForKey("candidate")))->getCString();
    
    CGHelper::stringArrFromChineseString(candidate_answer_str,strVector);
    
    //如果有英文备选答案(一般只有一个)
    std::string candidate_answer_str_en =
    ((CCString *)(_directlyCandidateDic->objectForKey("candidate_english")))->getCString();
    
    if (!candidate_answer_str_en.empty()) {
        strVector.push_back(candidate_answer_str_en);
//        CG_ENGLISH_ANSWER_NUMBER = CGHelper::stringLengthExceptChinese(candidate_answer_str);
        CG_ENGLISH_ANSWER_NUMBER = candidate_answer_str_en.length() - 1;
    }
    //得到备选答案字符串 -- end
    
    initAnswerLayer(strVector);
    
    CCString *answer_str =
    (CCString *)(_directlyCandidateDic->objectForKey("answer"));
    
    _standardAnswer.clear();
    _standardAnswer = std::string(answer_str->getCString());             //获得本次关卡答案
//    _standardAnswer = "CCTV总";
    this->initialTipView();                         ///获得答案后才调用提示初始化
    
    std::string picName = GlobalUserDefault::instance()->stringOfDicObject(_directlyCandidateDic, "picFrontName") ;
    
    int pic_num = GlobalUserDefault::instance()->intOfDicObject(_directlyCandidateDic, "picNum");//留给后面有多张图片用
    
    picName = GlobalUserDefault::instance()->directlyAddressOfCurrPass()+ picName + "0.jpg";
    
    _imageLayer->setBackGroundImage(picName.c_str());
    
}

void GameLayer::initialTipView()
{
    CG_MAX_ANSWER_NUMBER = CGHelper::stringLengthIncludeChinese(_standardAnswer);           //设置最大答案位置数量
    CG_MAX_ANSWER_NUMBER -= CG_ENGLISH_ANSWER_NUMBER;                                       //英文答案只算一个位置
    
    cout<<"最大数量:"<<CG_MAX_ANSWER_NUMBER<<_standardAnswer<<endl;
    _hState.setMaxHoldNum(CG_MAX_ANSWER_NUMBER);                        //设置最大答案位置数量
    
    float width_answer = (CG_MAX_ANSWER_NUMBER - 1) * CG_ANSWER_SELECTED__SPACE_SIZE.width;
    
    CG_ANSWER_SELECTED_FIRST_POINT = ccp((CG_ScreenSize.width - width_answer)/2,350);
    
    UIImageView *answerBG_image = static_cast<UIImageView *>(_play_root->getChildByName("answerBG_image"));
    
    for (int i = 0; i < CG_MAX_ANSWER_NUMBER; i++)
    {
        CCPoint point = ccp(CG_ANSWER_SELECTED_FIRST_POINT.x,CG_ANSWER_SELECTED_FIRST_POINT.y);
        
        if (i == 0)
        {
            answerBG_image->removeFromParent();
            _play_root->addChild(answerBG_image);
            answerBG_image->setZOrder(-1);
            answerBG_image->setPosition(point);
            answerBG_image->setScale(0.3);
            continue;
        }
        
        UIImageView *image_bg = UIImageView::create();
        image_bg->loadTexture("blankAnswerImage.png",UI_TEX_TYPE_PLIST);
        image_bg->setPosition(ccp(CG_ANSWER_SELECTED_FIRST_POINT.x + (CG_ANSWER_SELECTED__SPACE_SIZE.width)* i,CG_ANSWER_SELECTED_FIRST_POINT.y));
        _play_root->addChild(image_bg);
        image_bg->setScale(0.3);
        
    }
    
    this->setProcessShow(0);                                            //设置进度
}

#pragma mark - 倒计时
void GameLayer::update(float delta)
{
    if (!_startCD) return;                  //没有开始倒计时不执行代码
    
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    long long curr_seconds = now.tv_sec;
    
    if (curr_seconds - _start_cd_seconds >= CG_GAME_CD_LV1) //时间到
    {
        _startCD = false;
        CCLog(" <------规定时间没有完成，所以没有奖励了----->  ");
    }
    
}

#pragma mark - 去掉一个备选答案
void GameLayer::removeWrongButtCancel(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        this->getChildByTag(11211)->removeFromParentAndCleanup(true);
        _play_root->setTouchEnable(true,true);
    }

}

void GameLayer::removeWrongButtConfirm(cocos2d::extension::UIButton *butt, TouchEventType type)

{
    if (type == TOUCH_EVENT_BEGAN)
    {
      PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        this->getChildByTag(11211)->removeFromParentAndCleanup(true);
        _play_root->setTouchEnable(true,true);
        this->removeAlternativeAnswer(kRemoveAlterAswer_need); //去掉一个错误答案
    }

}

void GameLayer::removeAlternativeAnswer(int nGold)
{
    std::vector<std::string>  answer_strVector;
    if(!CGHelper::stringArrFromString(_standardAnswer, answer_strVector))
        return;
    
    std::vector<std::string>::iterator answer_it = answer_strVector.begin();
    bool operationDone = false;
    
    CCArray *arr = _answerLayer->getChildren();
    
    for (int i = 0; i < arr->count(); i++)
    {
        UIButton *butt = (UIButton *)arr->randomObject();
        if (!butt->isEnabled()) continue;
        
        const char * text = butt->getTitleText();
        bool allNotEque = true;
        for (int j = 0;j < answer_strVector.size();j++)
        {
            if (strcmp(text, (answer_strVector.at(j)).c_str()) == 0)
            {
                allNotEque = false;
                CCLog(" 相同的 %s ",text);
                break;
            }
        }
        
        if (allNotEque)     //全部都不等于备选答案
        {
            CCLog("没有一个相同的 %s ",text);
            butt->removeFromParentAndCleanup(true); //设置该按钮不操作
            operationDone = true;
            break;
        }
    }
    
    //设置金币数量
    if(operationDone)
    {
        GlobalUserDefault::instance()->reduceGameGold(nGold);
         _gold_label->setText(CGHelper::getChar(GlobalUserDefault::instance()->getGameGold()));
    }
}

#pragma mark - 提示一个正确答案

void GameLayer::oneCorrectButtCancel(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        this->getChildByTag(11211)->removeFromParentAndCleanup(true);
        _play_root->setTouchEnable(true,true);
    }
}

void GameLayer::oneCorrectButtConfirm(cocos2d::extension::UIButton *butt, TouchEventType type)
{
    if (type == TOUCH_EVENT_BEGAN)
    {
         PLAY_EFFECT(TAP_EFFECT);
    }else if (type == TOUCH_EVENT_MOVED)
    {
        
    }else if (type == TOUCH_EVENT_ENDED)
    {
        this->getChildByTag(11211)->removeFromParentAndCleanup(true);
        _play_root->setTouchEnable(true,true);
        this->oneCorrectAnswer(kOneCorrectAswer_need); //提示一个正确答案
    }
}

void GameLayer::oneCorrectAnswer(int nGold)
{
    std::vector<std::string>  answer_strVector;
    if(!CGHelper::stringArrFromString(_standardAnswer, answer_strVector))
        return;
    
    bool operationDone = false;
    
    CCArray *arr = _answerLayer->getChildren();
    for (int i = 0; i < arr->count(); i++)
    {
        UIButton *butt = (UIButton *)arr->objectAtIndex(i);
        const char * text = butt->getTitleText();
       
        int holdIndex = _hState.getCloselyBlankIndex();     //获得当前答案空位的索引
        std::string oneAnswer = answer_strVector.at(holdIndex);
        
        if (strcmp(text, oneAnswer.c_str()) == 0)
        {
            butt->setColor(ccYELLOW);
            operationDone = true;
            break;
        }
    }
    
    //设置金币数量
    if(operationDone)
    {
        GlobalUserDefault::instance()->reduceGameGold(nGold);
         _gold_label->setText(CGHelper::getChar(GlobalUserDefault::instance()->getGameGold()));
    }
    
}

void GameLayer::successfully()
{
    int award_amount;
    int star_amount;
    
    if (_total_award_cd <= CG_GAME_CD_LV3)
    {
        award_amount = kGameAward_LV3;
        star_amount = 3;
    }else if(_total_award_cd <= CG_GAME_CD_LV2)
    {
        award_amount = KGameAward_LV2;
        star_amount = 2;
    }else
    {
        award_amount = kGameAward_LV1;
        star_amount = 1;
    }
    
    /**
     * 1.）修改通关结果
     * 2.) 设置下一关章节和关卡id
     * 3.) 获得奖励后修改金币数量
     */
    
    GlobalUserDefault::instance()->setPassInfo(star_amount);
    GlobalUserDefault::instance()->nextPass();                  //下一关
    GlobalUserDefault::instance()->increaseGameGold(award_amount);
    
    SuccessLayer *_succLayer  = SuccessLayer::create();         //通关界面
    CCScene *success_scene = CCScene::create();
    success_scene->addChild(_succLayer,10);
    
    Map_str_str dic;
    dic.insert(make_pair("xingshu",CGHelper::getChar(star_amount)));
    dic.insert(make_pair("answer", _standardAnswer));
    dic.insert(make_pair("jiangli", CGHelper::getChar(award_amount)));
    dic.insert(make_pair("shijian", CGHelper::getChar(_total_award_cd)));
    _succLayer->setSuccessData(dic);
    
    CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(success_scene);
    CCDirector::sharedDirector()->replaceScene(transition);
}
