//
//  GlobalUserDefault.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-5.
//
//

#include "GlobalUserDefault.h"
#include "XMLOperation.h"
#include "TDInvFileUtils.h"
#include "CGHelper.h"
#include "CGconfig.h"
#include "base64.h"
#include "SharedMultiPlatform.h"

//<-----91平台ios处理头文件------>//
#import "platform91Configure.h"
//<--------------------------->

//<--------加密头文件----------->
#include "DataBase64Himi.h"
//<--------------------------->

#define BGMUSIC_VOLUME  "background_music"
#define EFFMUSIC_VOLUME "effect_music"
#define SILENCE         "silence_volume"
#define CURRCHAPTER_ID  "currentChapter"
#define CURRPASS_ID     "currentPass"
#define DEFAULT_RETURN  -112

template<> GlobalUserDefault* CPPSingleton<GlobalUserDefault>::s_instance = NULL;

GlobalUserDefault::GlobalUserDefault()
{
    this->dataFilePath();       //初始化数据文件地址
    
    g_passInfomation = NULL;
    g_currPassInfo = NULL;
    g_chapterMapDic = NULL;
    _perPlistName.clear();
    _currChapter = 1;
    _currPass = 1;
    
    this->chapterMapData();     //初始化章节关卡信息，加载图片资源
    
    
    _shareMultPla = new SharedMultiPlatform();  //初始化分享数据
    this->initGameGold();                       //初始化金币
}

GlobalUserDefault::~GlobalUserDefault()
{
    CC_SAFE_RELEASE_NULL(g_chapterMapDic);
    CC_SAFE_RELEASE_NULL(g_passInfomation);
    
    //结束游戏的时候调用
    CCArmatureDataManager::purge();
	CCSSceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
	cocos2d::extension::UIHelper::instance()->purgeUIHelper();
    CCDirector::sharedDirector()->end();
}

void GlobalUserDefault::setCurrentChapter(int chap)
{
//    const char *value_char = CCString::createWithFormat("%d",chap)->getCString();
//    XMLOperation::fixAttribute1("CGChapter.xml", "0", "currChaId", value_char);
    _currChapter = chap;
}

int GlobalUserDefault::getCurrentChapter()
{
    return _currChapter;
}

std::string GlobalUserDefault::getCurrentChapterName()
{
    return _currChapterName;
}

int GlobalUserDefault::getPassedChapter()
{
    return _passedChapter;
}

int GlobalUserDefault::getPassedPass()
{
    return _passedPass;
}

void GlobalUserDefault::showDictionaryKeyAndValue(cocos2d::CCDictionary *dic)
{
    CCDictElement *dicEle;
    
    CCDICT_FOREACH(dic, dicEle)
    {
        const char *char_key = (dicEle->getStrKey());
        const char *char_value = ((CCString *)(dic->objectForKey(char_key)))->getCString();
        
        CCLog("[ dic有:%d 条数据] [键: %s <--> 值: %s]",dic->count(),char_key,char_value);
    }
}

const char* GlobalUserDefault::stringOfDicObject(cocos2d::CCDictionary *dic, const char *key)
{
    return ((CCString *)dic->objectForKey(key))->getCString();
}

int GlobalUserDefault::intOfDicObject(cocos2d::CCDictionary *dic, const char *key)
{
    return ((CCString *)dic->objectForKey(key))->intValue();
}

std::string GlobalUserDefault::directlyAddressOfCurrPass()
{
    std::string add_str = CG_GamePathes[kGameProvincePath] + _currChapterName +"/";
    return add_str;
}

CCTransitionScene *GlobalUserDefault::randomTransitionScene(cocos2d::CCScene *s)
{
    static bool is_srand = false;
    
    if (!is_srand) {
        is_srand = true;
        srand(unsigned(time(0)));
        cout<<"设置了 srand。只能设置一次"<<endl;
    }
    
    int random_transition = CGHelper::randomNumber(1, 33);
    
    CCTransitionScene *reScene = NULL;
    float jump_time = 1.8;
    float radial_time = 0.5;
    float horizontal_time = 0.8f;
    float vertical_time = 0.8;
    float inOut_time = 0.6f;
    float fade_time = 0.6f;
    float pageTurn_time = 0.5;
    float tiles_time = 0.8;
    float splitRows_time = 0.6;
    float fadeToColor_time = 0.9;
    float flipXoY_time = 0.5;
    float flipAngular_time = 0.8;
    float zoomFlipXoY_time = 0.7;
    float zoomFlipAngular_time = 1;
    
    float shrinkGrow_time = 1;
    float rotoZoom_time = 1;
    float moveInLoR_time = 0.6;
    float moveInBoT_time = 0.6;
    float slideInLoR_time = 0.5;
    float slideInToB_time = 0.5;
    
    switch (random_transition) {
        case 1:
            //    作用： 创建一个跳动的过渡动画
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
            reScene = CCTransitionJumpZoom ::create(jump_time , s);
            break;
        case 2:
            //    作用： 创建一个扇形条形式的过渡动画， 逆时针方向
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressRadialCCW::create(radial_time, s);
            break;
        case 3:
            //    作用： 创建一个扇形条形式的过渡动画， 顺时针方向
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressRadialCW::create(radial_time,s);
            break;
        case 4:
            //    作用： 创建一个水平条形式的过渡动画，
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressHorizontal ::create(horizontal_time,s);
            break;
        case 5:
            //    作用： 创建一个垂直条形式的过渡动画，
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressVertical::create(vertical_time, s);
            break;
        case 6:
            //    作用： 创建一个由里向外扩展的过渡动画，
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressInOut::create(inOut_time, s);
            break;
        case 7:
            //    作用： 创建一个由外向里扩展的过渡动画，
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionProgressOutIn::create(inOut_time, s);
            break;
        case 8:
            //    作用：创建一个逐渐透明的过渡动画
            //    参数1：过渡动作的时间
            //    参数2：切换到目标场景的对象
                reScene = CCTransitionCrossFade::create(fade_time, s);
            break;
        case 9:
            //    作用：创建一个翻页的过渡动画
            //    参数1：过渡动作持续的时间
            //    参数2：切换的目标场景的对象
            //    参数3：是否逆向翻页
                reScene = CCTransitionPageTurn::create(pageTurn_time, s, false);
            break;
        case 10:
            //    作用：创建一个部落格过渡动画， 从左下到右上
            //    参数1：过渡动作持续的时间
            //    参数2：切换的目标场景的对象
                reScene =CCTransitionFadeTR::create(fade_time, s);
            break;
        case 11:
            //    作用：创建一个部落格过渡动画， 从右上到左下
            //    参数1：过渡动作持续的时间
            //    参数2：切换的目标场景的对象
                reScene = CCTransitionFadeBL::create(fade_time, s);
            break;
        case 12:
            //    作用：创建一个从下到上，条形折叠的过渡动画
            //    参数1：过渡动作持续的时间
            //    参数2：切换的目标场景的对象
                reScene= CCTransitionFadeUp::create(fade_time, s);
            break;
        case 13:
            //    作用：创建一个从上到下，条形折叠的过渡动画
            //    参数1：过渡动作持续的时间
            //    参数2：切换的目标场景的对象
                reScene = CCTransitionFadeDown::create(fade_time, s);
            break;
        case 14:
            //    作用：创建一个随机方格消失的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene= CCTransitionTurnOffTiles::create(tiles_time, s);
            break;
        case 15:
            //    作用：创建一个分行划分切换的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene = CCTransitionSplitRows::create(splitRows_time, s);
            break;
        case 16:
            //    作用：创建一个分列划分切换的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene = CCTransitionSplitCols::create(splitRows_time, s);
            break;
        case 17:
            //    作用：创建一个逐渐过渡到目标颜色的切换动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：目标颜色
                reScene= CCTransitionFade::create(fadeToColor_time, s, ccc3(255, 0, 0));
            break;
        case 18:
            //    作用：创建一个x轴反转的切换动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene  = CCTransitionFlipX::create(flipXoY_time, s);
            break;
        case 19:
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene = CCTransitionFlipY::create(flipXoY_time, s);
            break;
        case 20:
            //    作用：创建一个带有反转角切换动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene = CCTransitionFlipAngular::create(flipAngular_time, s);
            break;
        case 21:
            //     作用：创建一个带有缩放的x轴反转切换的动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene=CCTransitionZoomFlipX::create(zoomFlipXoY_time, s);
            break;
        case 22:
            //     作用：创建一个带有缩放的Y轴反转切换的动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene=CCTransitionZoomFlipY::create(zoomFlipXoY_time, s);
            break;
        case 23:
            //     作用：创建一个带有缩放 ，反转角切换的动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            //    参数3：反转类型的枚举变量   左右上下
                reScene=CCTransitionZoomFlipAngular::create(zoomFlipAngular_time, s);
            break;
        case 24:
            //    创建一个放缩交替的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene = CCTransitionShrinkGrow::create(shrinkGrow_time, s);
            break;
        case 25:
            // 创建一个旋转放缩交替的过渡动画
            // 参数1：过渡动作的持续时间
            // 参数2：切换的目标场景的对象
                reScene = CCTransitionRotoZoom::create(rotoZoom_time, s);
            break;
        case 26:
            //    作用：创建一个从左边推入覆盖的过渡动画
            // 参数1：过渡动作的持续时间
            // 参数2：切换的目标场景的对象
                reScene = CCTransitionMoveInL::create(moveInLoR_time, s);
            break;
        case 27:
            //    作用：创建一个从右边推入覆盖的过渡动画
            // 参数1：过渡动作的持续时间
            // 参数2：切换的目标场景的对象
                reScene = CCTransitionMoveInR::create(moveInLoR_time, s);
            break;
        case 28:
            //  作用：创建一个从下边推入覆盖的过渡动画
            // 参数1：过渡动作的持续时间
            // 参数2：切换的目标场景的对象
                reScene = CCTransitionMoveInB::create(moveInBoT_time, s);
            break;
        case 29:
            //    作用：创建一个从上边推入覆盖的过渡动画
            // 参数1：过渡动作的持续时间
            // 参数2：切换的目标场景的对象
                reScene = CCTransitionMoveInT::create(moveInBoT_time, s);
            break;
        case 30:
            //    作用：创建一个从左侧推入并顶出旧场景的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene  =CCTransitionSlideInL::create(slideInLoR_time, s);
            break;
        case 31:
            //    作用：创建一个从右侧推入并顶出旧场景的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene  =CCTransitionSlideInR::create(slideInLoR_time, s);
            break;
        case 32:
            //    作用：创建一个从顶部推入并顶出旧场景的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
                reScene  =CCTransitionSlideInT::create(slideInToB_time, s);
            break;
        case 33:
            //    作用：创建一个从下部推入并顶出旧场景的过渡动画
            //    参数1：过渡动作的持续时间
            //    参数2：切换的目标场景的对象
            reScene = CCTransitionSlideInB::create(slideInToB_time, s);
            break;
        default:
            
            reScene = CCTransitionPageTurn::create(pageTurn_time, s, false);
            
            break;
    }
    
    CCLog("[randomTransitionScene 第%d个场景]",random_transition);
    return reScene;
}

void GlobalUserDefault::setCurrentPass(int pass)
{
//    const char *value_char = CCString::createWithFormat("%d",pass)->getCString();
//    XMLOperation::fixAttribute1("CGChapter.xml", "0", "currPassId", value_char);
    _currPass = pass;
}

std::string GlobalUserDefault::getDataFilePath()
{
    return _dataFilePath;
}

void GlobalUserDefault::addCCSpriteResource()
{
    //加载/移除 图片资源
    std::string plist_name = CG_GamePathes[kGameProvincePath];
    
    if (!_perPlistName.empty()) {
        plist_name = plist_name + _perPlistName + ".plist";
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist_name.c_str());
        
    }
    _perPlistName.clear();
    _perPlistName = _currChapterName;
    
    plist_name = plist_name + _currChapterName + ".plist";
    std::string pvr_name = CG_GamePathes[kGameProvincePath];
    pvr_name = pvr_name + _currChapterName + ".pvr";
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist_name.c_str(), pvr_name.c_str());
}

int GlobalUserDefault::getCurrentPass()
{
    //    return CCUserDefault::sharedUserDefault()->getIntegerForKey(GameChapterDefault[1].c_str());
    return _currPass;
}

CCDictionary * GlobalUserDefault::getChapterInfo()
{
    return g_chapterMapDic;
}

void GlobalUserDefault::chapterMapData()
{
   
    if (g_chapterMapDic == NULL) {
//        CCDictionary *tempDic = XMLOperation::xmlDicSwitchToCCDic1(CG_GAME_DATA[KGD_CHAPTER_XML].c_str(),"id");
        
        CCDictionary *tempDic = XMLOperation::xmlDicSwitchToCCDic1(makeCacheFileData(CG_GAME_DATA[KGD_CHAPTER_XML]).c_str(),"id",true);
        g_chapterMapDic = (CCDictionary*)tempDic->copy();
        
        //得到当前章节信息
        _passedChapter = ((CCString *)(((CCDictionary *)g_chapterMapDic->objectForKey("0"))->objectForKey("passedChaId")))->intValue();
        _passedPass = ((CCString *)(((CCDictionary *)g_chapterMapDic->objectForKey("0"))->objectForKey("passedPassId")))->intValue();
        
        _totalChapters = g_chapterMapDic->count() - 1;             //减去一条陈述信息得到章节数据数量
    }
    
    //    this->addCCSpriteResource();
}

CCDictionary *GlobalUserDefault::currPassInfomation()
{
    CC_SAFE_RELEASE_NULL(g_passInfomation);
    
    //键 “name” 是CGChapter.xml 表里面配置的关卡名字
    CCString *chapter_name = (CCString *)(((CCDictionary *)(g_chapterMapDic->objectForKey(CGHelper::getChar(_currChapter))))->objectForKey("name"));
    _currChapterName = chapter_name->getCString();
    
    //先要得到关卡名字才能继续读取当前关卡信息
    std::string pass_name = CG_GamePathes[kGameProvincePath];
    pass_name = pass_name +_currChapterName + "/" + _currChapterName + ".xml";
    
    CCLog("{ 读取的关卡名字：%s } { currChapter :%d currPass :%d} {总共关卡数量 %d}",pass_name.c_str(),_currChapter,_currPass,g_chapterMapDic->count());
    
    CCDictionary *tempDic = XMLOperation::xmlDicSwitchToCCDic1(makeCacheFileData(pass_name).c_str(),"id",true);
    g_passInfomation = (CCDictionary*)tempDic->copy();
    _totalPasses = g_passInfomation->count();                   //得到关卡数据数量
    
    CC_ASSERT(g_passInfomation != NULL && g_chapterMapDic->count() > 0);
    return g_passInfomation;
}

CCDictionary *GlobalUserDefault::currPassInfo()
{
    g_currPassInfo = (CCDictionary*)((g_passInfomation->objectForKey(CGHelper::getstringFromint(_currPass))));
    
    return g_currPassInfo;
}

void GlobalUserDefault::setPassInfo(int star)
{
    //先要得到关卡名字才能继续读取当前关卡信息
    std::string pass_name = CG_GamePathes[kGameProvincePath];
    pass_name = pass_name +_currChapterName + "/" + _currChapterName + ".xml";
    
    if( XMLOperation::fixAttribute1(makeCacheFileData(makeCacheFileData(pass_name)).c_str(), CGHelper::getChar(_currPass), "star", CGHelper::getChar(star),"id",true))
    {
        CCLog("<------修改关卡完成------>");
    }
}

void GlobalUserDefault::nextPass()
{
    int passNum = _currPass + 1;
    int chapNum = _currChapter + 1;

    if (passNum > _totalPasses)                //如果是最后一关,则进入下一章节
    {
        if (chapNum > _totalChapters)          //所有章节完成
        {
            CCLog("<!!!!passed--All!!!!>");
            
        }else
        {
            _passedChapter = chapNum;
            _currChapter = chapNum;
            _passedPass = 1;
            _currPass   = 1;
            
            XMLOperation::fixAttribute1(makeCacheFileData(CG_GAME_DATA[KGD_CHAPTER_XML]).c_str(), "0", "passedChaId", CGHelper::getChar(_passedChapter),"id",true);
            XMLOperation::fixAttribute1(makeCacheFileData(CG_GAME_DATA[KGD_CHAPTER_XML]).c_str(), "0", "passedPassId", CGHelper::getChar(_passedPass),"id",true);
            
            this->currPassInfomation();        //加载新关卡的所有章节信息
        }
    }else
    {
        if (passNum > _passedPass)
        {
            _currPass = _passedPass = passNum;
            XMLOperation::fixAttribute1(makeCacheFileData(CG_GAME_DATA[KGD_CHAPTER_XML]).c_str(), "0", "passedPassId", CGHelper::getChar(_passedPass),"id",true);
        }
    }
}

std::string GlobalUserDefault::dataFilePath()
{
    
    _dataFilePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    return _dataFilePath;
    
}

std::string GlobalUserDefault::makeCacheFileData(std::string filePath,bool change)
{
    std::vector<std:: string> division_path = CGHelper::split(filePath, "/");
    std::string last_path = division_path.at(division_path.size()-1);
    
    std::string filePath_full = _dataFilePath + last_path;

    bool existFile = CCFileUtils::sharedFileUtils()->isFileExist(filePath_full);
    cout<<" filePaht_full  "<<filePath_full<<" 是否存在:"<<existFile<<endl;
    
    if (!existFile)
    {
        using namespace tinyxml2;
        std::string filePath_resource = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath.c_str());//获得源文件路径
        XMLDocument *pDoc = new XMLDocument();
        pDoc->LoadFile(filePath_resource.c_str());
        if (pDoc->SaveFile(filePath_full.c_str()) != XML_SUCCESS)
        {
            return "";
        }
        CC_SAFE_DELETE(pDoc);
        
    }
    
    
    return filePath_full;
}

#pragma mark - shareGame
void GlobalUserDefault::sharedGame(int type)
{
    _shareMultPla->registerApp();
    _shareMultPla->sharedAllPlatForm();
}

void GlobalUserDefault::cancelAllAuth()
{
    _shareMultPla->cancelAuth(0);
}

#pragma mark - buyCommodity

void GlobalUserDefault::buyCommodities(const char *commId, const char *commName, float price, int count)
{
    NSString *commIdStr = [NSString stringWithUTF8String:commId];
    NSString *commNameStr = [NSString stringWithUTF8String:commName];
    
    //没有打折所以原价和当前价格一样
    [[platform91Configure instance] buyCommodities:commNameStr productId:commIdStr price:price originPrice:price count:count];
}

void GlobalUserDefault::show91ToolBar(bool show)
{
    [[platform91Configure instance] show91ToolBar:show];
}

void GlobalUserDefault::switchAccount()
{
    [[platform91Configure instance] switchAccount];
}

void GlobalUserDefault::enterAccountManage()
{
    [[platform91Configure instance] enterAccountManage];
}

void GlobalUserDefault::submitScoreTo91(unsigned int nLeaderBoardId, unsigned int nCurrentScore, const char *displayText)
{
    NSString *disString = [NSString stringWithUTF8String:displayText];
    [[platform91Configure instance] submitScoreTo91:nLeaderBoardId nCurrentScore:nCurrentScore displayText:disString];
}

void GlobalUserDefault::openScoreBoard(int nLeaderBoardId)
{
    [[platform91Configure instance] openScoreBoard:nLeaderBoardId];
}

void GlobalUserDefault::openAchievement()
{
    [[platform91Configure instance] openAchievement:0];
}

void GlobalUserDefault::unLockAchievement(int achieId, int percent, const char *displayText)
{
     NSString *disString = [NSString stringWithUTF8String:displayText];
    [[platform91Configure instance] unLockAchievement:achieId currValuePercent:percent displayText:disString];
}

void GlobalUserDefault::enterVirtualShop()
{
    [[platform91Configure instance] EnterVirtualShop];
}

#pragma mark - 本地游戏金币处理

void GlobalUserDefault::increaseGameGold(int addGold)
{
    int local_gold = getGameGold();
    
    local_gold += addGold;
    
    std::string sValue = CGHelper::getstring(local_gold);
    string value_str = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(CG_GAME_GOLD_KEY, value_str);
    CCUserDefault::sharedUserDefault()->flush();
    
}

void GlobalUserDefault::reduceGameGold(int reGold)
{
    int local_gold = getGameGold();
    
    local_gold -= reGold;
    
    std::string sValue = CGHelper::getstring(local_gold);
    
#ifdef GLOBAL_DEBUG
    CCLog("----------存储------");
       CCLog("存储之前数据 key：index: Himi, value: %s  ",sValue.c_str());
#endif
    
    string value_str = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
#ifdef GLOBAL_DEBUG
        CCLog("存储加密后的数据 key：index: Himi, value: %s  ",value_str.c_str());
#endif
    
    CCUserDefault::sharedUserDefault()->setStringForKey(CG_GAME_GOLD_KEY, value_str);
    CCUserDefault::sharedUserDefault()->flush();
}

int GlobalUserDefault::getGameGold()
{
    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    
    std::string local_gold_str = userDefault->getStringForKey(CG_GAME_GOLD_KEY);
    local_gold_str = himiParseData(local_gold_str);         //解密
    
    int local_gold = 0;
    if (!local_gold_str.empty())
    {
        local_gold = CGHelper::getint(local_gold_str);      //得到当前金币数量
    }

#ifdef GLOBAL_DEBUG
        CCLog("<--GlobalUserDefault::getGameGold--/n 得到金币 %d> %s",local_gold,userDefault->getXMLFilePath().c_str());
#endif
    
    return local_gold;
}

void GlobalUserDefault::refreshGameGold()
{
    std::string sValue = CGHelper::getstring(CG_GAME_INIT_GOLD);
    
#ifdef GLOBAL_DEBUG
    CCLog("----------存储------");
    CCLog("存储之前数据 key：index: Himi, value: %s  ",sValue.c_str());
#endif
    
    string value_str = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
#ifdef GLOBAL_DEBUG
        CCLog("存储加密后的数据 key：index: Himi, value: %s  ",value_str.c_str());
    
#endif
    CCUserDefault::sharedUserDefault()->setStringForKey(CG_GAME_GOLD_KEY, value_str);
    CCUserDefault::sharedUserDefault()->flush();
}

void GlobalUserDefault::initGameGold()
{
    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    int inGameFirst = userDefault->getIntegerForKey(CG_GAME_IS_FRISTIN);// 0 标示是第一次进入游戏
    if (inGameFirst == 0)
    {
        //初始化游戏金币
        userDefault->setIntegerForKey(CG_GAME_IS_FRISTIN, 1);
        increaseGameGold(CG_GAME_INIT_GOLD);                    //   初始化游戏币
    }
}


