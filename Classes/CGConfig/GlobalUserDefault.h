//
//  GlobalUserDefault.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-5.
//
//

#ifndef __CrazyGeography__GlobalUserDefault__
#define __CrazyGeography__GlobalUserDefault__

#include "cocos2d.h"
#include "CPPSingleton.h"

class SharedMultiPlatform;

USING_NS_CC;
using namespace std;

class GlobalUserDefault : public CPPSingleton<GlobalUserDefault>{
    
public:
    
    CCDictionary *getChapterInfo();
    /**
     * @return 返回一个当前章节所有关卡的信息
     */
    CCDictionary *currPassInfomation();
    
    /**
     * 获得一个关卡的信息
     */
    CCDictionary *currPassInfo();
    
    /**
     * 修改关卡信息【定要早于nextPass() 调用 】
     */
    void setPassInfo(int star);
    
    /**
     * 自动切换时候调用 【下一关】
     */
    void nextPass();
    
    /**
     * 当前的关卡和章节
     */
    int getCurrentPass();
    int getCurrentChapter();
    
    /**
     * 返回已经经过的章节和关卡
     */
    int getPassedChapter();
    int getPassedPass();
    
    std::string getCurrentChapterName();
    
    void showDictionaryKeyAndValue(CCDictionary *dic);
    
    /**
     * @return 返回一个字符串
     */
    const char* stringOfDicObject(CCDictionary *dic,char const *key);
    
    /**
     * @return 返回一个int型
     */
    int intOfDicObject(CCDictionary *dic,char const *key);
    
    /**
     * @return 返回当前关卡路径
     */
    std::string directlyAddressOfCurrPass();
    
    /**
     * @brief 随机返回一种场景转换形式
     */
    CCTransitionScene *randomTransitionScene(CCScene *s);
    
    /**
     * 设置当前的章节和关卡
     */
    void setCurrentChapter(int chap);           //设置章节
    void setCurrentPass(int pass);              //设置关
    
    std::string getDataFilePath();              //获得数据根路径
    std::string makeCacheFileData(std::string filePath,bool change = false);     //制作文件路径
    
    void sharedGame(int type);                  //分享游戏
    void cancelAllAuth();                       //取消所有平台授权
    
    //---- 91平台操作
    void buyCommodities(const char* commId,const char* commName,float price,int count);
    void show91ToolBar(bool show);              //显示或隐藏91工具栏
    void switchAccount();
    void enterAccountManage();
    void submitScoreTo91(unsigned int nLeaderBoardId,unsigned int nCurrentScore,const char* displayText);
    void openScoreBoard(int nLeaderBoardId);
    void openAchievement();
    void unLockAchievement(int achieId,  int percent, const char* displayText);
    
    /**
     * 游戏中金币的处理
     * @param gold 金币数量
     */
    void increaseGameGold(int gold);
    void reduceGameGold(int gold);
    
    int  getGameGold();      //获得当前金币
    void refreshGameGold();  //重置游戏金币
    void initGameGold();     //初始化游戏金币
    
private:
    
    ~GlobalUserDefault();
    GlobalUserDefault();
    
    friend CPPSingleton;
    
    void addCCSpriteResource();                 //添加图片资源
    void chapterMapData();
    
    std::string dataFilePath();                 //初始化数据路径
    
private:
    CCDictionary *g_chapterMapDic;
    CCDictionary *g_passInfomation;
    CCDictionary *g_currPassInfo;
    
    int _currChapter;
    int _currPass;
    int _totalChapters;
    int _totalPasses;
    int _passedChapter;                         //完成的章节
    int _passedPass;                            //完成的关卡
    
    std::string _currChapterName;               //当前(章节)名字
    std::string _perPlistName;                  //前一个plist文件名(用于加载图片资源寻路)
    
    std::string _dataFilePath;           //数据根路径
    
    SharedMultiPlatform *_shareMultPla;  //多平台分享
};
#endif /* defined(__CrazyGeography__GlobalUserDefault__) */
