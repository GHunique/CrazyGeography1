//
//  CGconfig.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-10-29.
//
//

#ifndef __CrazyGeography__CGconfig__
#define __CrazyGeography__CGconfig__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

//#define GLOBAL_DEBUG  

//战斗场景路径
enum {
    kGamePathesBegin = 0,
    kAheadChapter = kGamePathesBegin,
    kGameChapterLayerUI,
    kGameLayerUI,   ///------------游戏界面
    kGamePassesUI,  //-------------选择关卡
    kGameSuccessUI, ///-----------游戏成功界面
    kGameProvincePath,//----------关卡资源目录
    kControlerUI_volume,///-------游戏音效设置界面
    
    kGameShopUI,          //--------游戏商店
    kGameAlertUI,         ///-------游戏提示(警告)界面
    
    kChapter_Accessary,//------------一些特定的控件
    kGameInfoUI,
    
};

const std::string CG_GamePathes[11] =
{
    "CrazyGeography/AheadChapterUI.ExportJson",
    "CrazyGeography/GameChapterLayerUI.ExportJson",
    "CrazyGeography/GameLayerUI.ExportJson",    ///------------游戏界面
    "CrazyGeography/GamePassesUI.ExportJson",   //------------选择关卡
    "CrazyGeography/GameSuccessUI.ExportJson",  ///-----------游戏成功界面
    "provinces/",                               //----------关卡资源目录
    "CrazyGeography/ControlerUI_volume.ExportJson",     ///-----------游戏音效设置界面
    
    "CrazyGeography/GameShopUI.ExportJson",      //--------游戏商店
    "CrazyGeography/GameAlertUI.ExportJson",     ///-------游戏提示(警告)界面
    
    "CrazyGeography/Chapter_Accesary.ExportJson",     //------------一些特定的控件
    "CrazyGeography/GameInfoUI.ExportJson",
    
};

//Game Data path GD:GameData
enum  {
    kGD_BEGIN_XML = 0,
    KGD_CHAPTER_XML = kGD_BEGIN_XML,    //-----------章节xml配置表路径
    kGD_SETTING_MXL,                    ///----------游戏设置文件
    };

const std::string CG_GAME_DATA[2] =
{
    "CGChapter.xml",    //-----------章节xml配置表路径
    "CGSetting.xml",    ///----------游戏设置文件
};

//特效
enum  {
    kCGANIMATION_BASE_PATH = 0,
    kCGDocument_SUFFIX,
    kCGGoldJUMP_ANIMATION_NAME,
    };
const std::string CG_ANIMATION[3] =
{
    
    "CGAnimations/",    /* 所属文件夹  */
    ".ExportJson",      /*  文件后缀  */
    
    "CGGold_Jump", ///----------金币特效
};

//金币对应的标示
#define CG_GAME_GOLD_KEY  "C1G1_2G1A1M2E_G1O1L2D_1K1E2Y_1X1S2Y"
//游戏中完成关卡所用时间对应等级
#define CG_GAME_CD_LV1          12
#define CG_GAME_CD_LV2          8
#define CG_GAME_CD_LV3          5

//标示是否第一次进入游戏
#define CG_GAME_IS_FRISTIN   "FIRST_IN_GAME"
//游戏初始化金币
#define CG_GAME_INIT_GOLD    120

//完成关卡数量
#define CG_FINISHED_PASS     "CG_FINISHED_PASS_XSY"

enum  {//配置么个等级获得奖励
    
    kGameAward_LV1 = 3,
    KGameAward_LV2 = 7,
    kGameAward_LV3 = 10,
};

typedef std::map<std::string, std::string> Map_str_str;


enum  {
    kRemoveAlterAswer_need  = 30, //去掉一个错误答案需要的金币
    kOneCorrectAswer_need   = 90, //得到一个正确答案需要的金币
    };

//播放声音

#define SWIPE_EFFECT        "sound/Swipe.wav"
#define TAP_EFFECT          "sound/Tap.wav"
#define DU_EFFECT           "sound/Du.mp3"
#define GETGOLD_EFFECT      "sound/getGold.mp3"
#define JUMPDU_EFFECT       "sound/jumpDu.mp3"
#define LEVELUP_EFFECT      "sound/levelup.mp3"
#define GETGOLD2_EFFECT     "sound/getGold2.mp3"


#define PLAY_EFFECT(PATH) CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PATH)


#endif /* defined(__CrazyGeography__CGconfig__) */





