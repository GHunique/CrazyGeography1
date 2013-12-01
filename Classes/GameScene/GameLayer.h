//
//  GameLayer.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-10-29.
//
//

#ifndef __CrazyGeography__GameLayer__
#define __CrazyGeography__GameLayer__
//
//#include "cocos-ext.h"
//#include "cocos2d.h"
#include "SuccessLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer : public  CCLayerRGBA {
    
public:
    GameLayer();
    ~GameLayer();
    
    void onEnter();
    void onExit();
    bool init();
    
    CREATE_FUNC(GameLayer);
protected:
    UILayer *_yUILayer;
    Layout  *_answerLayer;                      //备选答案层
    Layout  *_imageLayer;                       //答案提示图片
    UILabel *_answerLabel;
    
    Layout  *_play_root;
    
    CCPoint CG_FISTANBUTT_POINT;                //没选中的起始坐标
    CCSize  CG_ANSWER_BUTT_SPACE_SIZE;          //没选中的间隔
    
    CCPoint CG_ANSWER_SELECTED_FIRST_POINT;     //选中后的起始点
    CCSize  CG_ANSWER_SELECTED__SPACE_SIZE;     //选中后的间隔
    
    CCPoint CG_PROCESS_DIVISION_SHOW_POINT;
    
    int CG_MAX_ANSWER_NUMBER;
    int CG_ENGLISH_ANSWER_NUMBER;
    
    struct HoldState
    {
    private:
        //标示是否被占用 true 标示被占用
        static const int maxContent = 10;
        
        bool isHold[maxContent];
        int max;
        int count;
        cocos2d::CCPoint oldPoint[maxContent];
        std::string answerStr[maxContent];
    public:
        
        //必须要先设置最大的
        void setMaxHoldNum(int i)
        {
            max = i;
            count = 0;
            for(int n = 0;n < maxContent;n++)
            {
                isHold[n] = false;
            }
            
        }
        
        //返回当前占有位置数量
        int getCount()
        {
            return count;
        }
        
        //返回从从左到右的第一个空位索引
        int getCloselyBlankIndex()
        {
            int i = 0;
            for(;i < max;i++){
                if(!isHold[i]) break;
            }
            
            return i;
        }
        
        //设置(打开)该位置没有被占用
        void openHoldPlace(int i)
        {
            isHold[i] = false;
            count--;
        }
        
        //设置该位置被占用
        void closeHold(int i)
        {
    
            isHold[i] = true;
        }
        
        //关闭从左到右第一个位置为
        int setCloselyHoldClose()
        {
            int closely = getCloselyBlankIndex();
            
            closeHold(closely);
            
            count++;
            
            return closely;
        }
        
        void setOldPoint(cocos2d::CCPoint oldP)
        {
            oldPoint[getCloselyBlankIndex()] = oldP;
        }
        
        //返回一个坐标
        cocos2d::CCPoint getOldPoint(int index)
        {
            return oldPoint[index];
        }
        
        void setPartAnswer(std::string anStr)
        {
            int closely = getCloselyBlankIndex();
            
            answerStr[closely].clear();
            answerStr[closely] = anStr;
        }
        
        //返回答案字符串
        std::string getAnswerString()
        {
            std::string anStr;
            
            for(int n = 0;n < max;n++)
            {
                anStr.append(answerStr[n]);
            }
            
            return anStr;
        }
        
    };
    
    HoldState _hState;                          //占位标示
    
    UILabelBMFont *_processShow;                //显示答案进度
    
    std::string _answerStr;                     //答案字符串
    std::string _standardAnswer;                //标准答案
    int begin,end;
    
    CCSize _canAnsImageSize;                    //备选答案图标大小
    
private:
    CCDictionary *_candidateAnswerDic;          //答案字典
    CCDictionary *_directlyCandidateDic;        //本次关卡的候选答案字典
    
    int _currChapter;                           //当前章节
    int _currPass;                              //当前章节
    
    UILabelBMFont *_gameGold_BMF;               //显示金币标签
    long _start_cd_seconds;                     //开始倒计时时间点
    long _total_award_cd;                             //剩余奖励时间
    bool _startCD;                              //是否倒计时
    
protected:
    
    void fanHuiButt(UIButton *pSender, TouchEventType type);        //返回选关界面按钮调用函数
    void getGoldButt(UIButton *pSender, TouchEventType type);       //获得金币按钮调用函数
    void helpButt(UIButton *pSender, TouchEventType type);          //帮助按钮调用函数
    void shareButt(UIButton *pSender, TouchEventType type);         //分享按钮调用界面
    void nextButt(UIButton *pSender, TouchEventType type);          //下一个问题
    
    void initAnswerLayer(std::vector<std::string> &StrVector);      //初始化答案界面
    
    void answerButt(UIButton *butt, TouchEventType type);           //答案按钮调用函数
    void answerSelectedButt(UIButton *butt, TouchEventType type);   //选中后的按钮调用的函数
    
    void layoutSelectedAnswer(CCObject *pObj);                      //布置选中的答案按钮位置等
    void returnToOraginPlace(CCObject *pObj);                       //设置选中答案的触摸事件
    
    void setProcessShow(int pre);                                   //设置进度
    
    void compareAnswer();                                           //对比选择的答案和标准答案
    
private:
    
    void refreshGameData();                                         //每次刷新游戏数据函数
    void initialTipView();                                          //初始化提示信息界面(包括答案进度,答案位置提示)
    void update(float delta);
    void nextButtCancel(UIButton *butt,TouchEventType type);
    void nextButtConfirm(UIButton *butt,TouchEventType type);  //分享，下一关，提示处理
};

#endif /* defined(__CrazyGeography__GameLayer__) */
