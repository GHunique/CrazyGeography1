//
//  MJHelper.h
//  MJGS
//
//  Created by xiangshouyong on 13-4-16.
//
//

#ifndef __MJGS__MJHelper__
#define __MJGS__MJHelper__

#include <iostream.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MJUnitSprite.h"
#include "ActionSprite.h"


#define ISBeCovered "sq_zjl_zy_xsy"

enum kMaJongShowType
{
    kMaJongLying_Left = 1,
    
    kMaJongStanding_Left = 2,
    
    kMaJongStanding_Front = 3,
};

enum
{
    //组合牌的区域  格子索引 Tag 起始偏移 值 
    kMJIndex_InCombineArea_Begin = 20000,
};

//保存麻将信息 1 为有麻将 2 为没有麻将 .0 表示没有初始化。数组 下标分别为 layer, col , row
static int MJARRAY_OF_EXIT[10][30][7];
#define MJ_EXIT_INMJARRAY  1
#define MJ_NOT_INMJARRAY   2

#define CreateMJUnitSpriteTag_CaptureArea(layerNum,col,row)     ((layerNum)*(1000) + (col)*(10) + (row))
#define CreateMJUnitSpriteTag_CombineArea(tag)                  ((kMJIndex_InCombineArea_Begin) + (tag))
#define PUSHMJ_EXITINFO_INTO_3DARRAY(layerNum,col,row)          (MJARRAY_OF_EXIT[layerNum][col][row])

struct MemberInfo
{
    int group_idx;
    int leader_idx;
    int position;
    unsigned int char_idx;// 玩家ID
    char name[20];// 名字
    int state;// 状态
    int curtitle; // 头衔（等级）
    unsigned int magnate_value; // 大亨值
    unsigned int copper;     // 游戏币
    int authority; // 权限
    int camp; // 阵营
    int char_type;//头像
    int gold;// 金币
    int charisma_value;//魅力值
    
    MemberInfo(){
    
        charisma_value = 0;
        magnate_value = 0;
        group_idx = -1;
        gold = 0;
        copper = 0;
    
    };
    
}; typedef MemberInfo MemberInfo;

struct sendCombinedMJElem//发送组合后的麻将的信息
{
    int assemble_type;
    int begin_idx;
    int end_idx;
    bool isSameMJ;
    
    unsigned int typeId_begin;
    unsigned int typeId_end;
    
    unsigned int typeid_mid;
    
};typedef sendCombinedMJElem sendCombinedMJElem;


typedef std::map<int, MemberInfo> Map_MemberInfo;
typedef std::vector<MemberInfo> Vector_MemberInfo;
typedef std::map<int, std::vector<MemberInfo> > Map_of_MemberInfoVecor;
typedef std::vector<MJUnitSprite*> Vector_Of_MJUnitSprite;
typedef std::map<int, CCSprite*> Map_Of_Sprite;
typedef std:: map<int, CCMenuItemImage*> Map_of_CCMenuItemImage;
typedef std:: map<int, CCLabelTTF*> Map_of_CCLabelTTF;
typedef std::map<int, CCControlButton*> Map_of_CCControButton;



class  MJHelper {

public:
    
    /**
     * 根据麻将信息包判断出麻将编号
     *
     *  @param    mjInfo 麻将的一个信息包 
     *  @return   返回一个麻将编号
     */
    static unsigned int convertToMahJongID(unsigned int main_type,unsigned int sub_type);
    /**
     * 方法根据麻将展示的类型 给将麻将的标号再在首位加上一个标示符
     *
     *  @name      convertToMahJongImageID
     *  @param     mjID 麻将的编号 
     *  @param     mjShowType 麻将展示的类型
     *  @return    返回一个添加了首部的麻将编号 string
     */
    static std::string convertToMahJongImageID(unsigned int mahjongID,kMaJongShowType mjShowType);
    
    /**
     * 将 整数类型转化为c++ 字符串
     *  @param      n 为待转化的整数
     *  @return     返回一个 string 
     */
    static std::string getstring(const unsigned int n);
    
    /**
     * 将 c++ 字符串 类型转化为 数组
     *  @param      c 为待转化的 字符串指针
     *  @return     返回一个 int型整数
     */
    static std::string getstring(const char *c);
    
    /**
     * 将 c++ 字符串 类型转化为整数
     *  @param      str 为待转化的 string
     *  @return     返回一个 int型整数
     */
    static int getint(const std::string str);
    
    /**
     * 将 整数类型转化为 const char* 字符串
     *  @param      n 为待转化的整数
     *  @return     返回一个 const char*
     */
    static const char* getChar(const unsigned int n);
    
    /**
     *  格式化数字显示格式 
     *  1万 或者 1，234万  或者 1,320 
     *  @param showFormat 显示格式化，false 为不显示“万”效果 
     *  @param place 标示单位位数 hundreds place = 2，thousand place = 3
     *  @param div 划分间距 也就是每隔div位添加一个分隔符
     *  @param div_symbol 分隔符
     */
    static std::string formatGold(unsigned int gold,bool showFormat,unsigned int place = 4,unsigned int div = 3,std::string gName = "万",std::string div_symbol = ",");
    
    /**
     *  求3个数的最大值
     *  @param      int1 ,int2, int3
     *  @return     返回一个 int
     */
    static int max(int int1,int int2,int int3);
    
    /**
    *  求3个数的最小值
    *  @param      int1 ,int2, int3
    *  @return     返回一个 int
    */
    static int min(int int1,int int2,int int3);
    
    /**
     *  保存 麻将层，行，列，信息到全局 GameState
     *  @param      layer 当前层,node 当前的麻将精灵
     */
    static void  addMJ3DimensionalCoordinate(int layer,cocos2d::CCNode *node);
    
    /**
     *  根据将麻将层，行，列。信息判断麻将是否没有被覆盖
     *  @param      layer 当前层,node 当前的麻将精灵
     *  @return     返回一个 bool.true 表示该坐标信息下麻将不是在最顶层(有被覆盖)
     */
    static bool isBeCovered(int layer,cocos2d::CCNode *node);
    
    /**
     *  根据判断覆盖的结果,设置麻将的遮盖层。被遮盖了就显示遮盖，反之则不显示
     *  @param  layer 需要检测的层。也就是判断该层是否有被覆盖的麻将有的话就设置为覆盖效果
     */
    static bool setCovered(int layer);
    
    /**
     *  根据将麻将层，行，列。信息删除麻将信息
     *  @param      layer 当前层,node 当前的麻将精灵
     *  @return     返回一个 bool.true 表示该坐标信息下麻将是否被删除
     */
    static bool deleteMJGlobalInfo(int layer,cocos2d::CCNode *node);
    
    /**
     *  移除所有麻将层信息
     */
    static bool clearMJGlobalInfo();
    
    /**
     *  根据需要指定按照比例缩放 RECT
     *  @param czoom 得到的比例
     */
    static cocos2d::CCRect getZoomRect(float czoom,cocos2d::CCRect rect);
    
    /**
     *  根据 分钟，秒 显示时间
     */
    static std::string timeFormat(int minutes,int secondes,int hour = 0);
    
    /**
     *  返回一个node 的 rect
     *  @param  node 传入的节点参数
     */
    static CCRect rect(CCNode *node);
    
    /**
     *  生成一个 随机数
     */
    static double random(double start,double end);
    
    /**
     *  判断是否有汉字
     */
    static bool isChineseChar(const char *pCh);
    
    /**
     *  精灵 跳动，放大缩小 特效
     * @param dur 完成一次动作的时间
     * @param s 为缩放的倍数
     * @param loop 是否循环
     * @param dur_offset 缩放偏差值。默认0.5. dur_offset 为 放大/缩小 所用时间 的比值
     */
    static CCActionInterval* jumpAndZoom(CCPoint point,float jumpHeight,unsigned int times,float dur,float s,bool loop = false,float dur_offset = 0.5f);
    
    /**
     * 更具两个组合 首尾编号 判断是否是相同的连子
     * @param head 一聚牌的开头麻将牌ID
     * @param end  一聚牌的结尾麻将牌ID
     */
    static bool isTheSameSequences(unsigned int head1,unsigned int mid1, unsigned int end1,unsigned int head2,unsigned int mid2,unsigned int end2);
    
private:
    /**
     *  jumpAndZoom 的姊妹函数 处理 后续事宜
     */
    static void afterJumpAndZoom(CCNode *node);
    
public:
    
    static int h_mjsMaxAmount;//麻将可以组合的最大值
    
    static int h_mjsCurrAmount;//麻将当前的最大值
    
    static bool h_canCaptured;//标示是否能抓取麻将牌
        
};


#define OPEN_FIRSTCBOX_PAY   "花费20钻石购买第5个格子？"
#define OPEN_SECONDCBOX_PAY  "花费40钻石购买第6个格子？"
#define OPEN_THIRDCBOX_PAY   "花费60钻石购买第7个格子？"


#endif /* defined(__MJGS__MJHelper__) */
