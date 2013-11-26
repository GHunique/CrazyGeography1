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
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;

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
    
    kChapter_Accessary,//------------一些特定的控件
};

const std::string CG_GamePathes[9] =
{
    "CrazyGeography/AheadChapterUI.ExportJson",
    "CrazyGeography/GameChapterLayerUI.ExportJson",
    "CrazyGeography/GameLayerUI.ExportJson",    ///------------游戏界面
    "CrazyGeography/GamePassesUI.ExportJson",   //------------选择关卡
    "CrazyGeography/GameSuccessUI.ExportJson",  ///-----------游戏成功界面
    "provinces/",                               //----------关卡资源目录
    "CrazyGeography/ControlerUI_volume.ExportJson",     ///-----------游戏音效设置界面
    
    "CrazyGeography/GameShopUI.ExportJson"      //--------游戏商店
    
    "CrazyGeography/Chapter_Accesary.ExportJson",     //------------一些特定的控件
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


typedef std::map<std::string, std::string> Map_str_str;

#endif /* defined(__CrazyGeography__CGconfig__) */
