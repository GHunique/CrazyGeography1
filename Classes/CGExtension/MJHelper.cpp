//
//  MJHelper.cpp
//  MJGS
//
//  Created by xiangshouyong on 13-4-16.
//
//

#include "MJHelper.h"
#include "sstream"
#include "GameState.h"

//#include "MJUnitSprite.h"

//牌类
enum
{
    TYPE_ZFB = 0,//中发白
    TYPE_DNXB = 1,//东南西北
    TYPE_WAN = 2,//万
    TYPE_SUO = 3,//索
    TYPE_TONG = 4,//筒
    TYPE_HUA = 5,//花
    TYPE_COUNT,//类型种数
};

//牌类中小类
enum
{
    //万、索、筒一样
    SUB_TYPE_1 = 1,//1
    SUB_TYPE_2 = 2,//2
    SUB_TYPE_3 = 3,//3
    SUB_TYPE_4 = 4,//4
    SUB_TYPE_5 = 5,//5
    SUB_TYPE_6 = 6,//6
    SUB_TYPE_7 = 7,//7
    SUB_TYPE_8 = 8,//8
    SUB_TYPE_9 = 9,//9
    
    //中发白
    SUB_TYPE_ZHONG = 1,//中
    SUB_TYPE_FA = 2,//发
    SUB_TYPE_BAI = 3,//白
    
    //东南西北
    SUB_TYPE_DONG = 1,//东风
    SUB_TYPE_NAN = 2,//南风
    SUB_TYPE_XI = 3,//西风
    SUB_TYPE_BEI = 4,//北风
    
};

unsigned int MJHelper::convertToMahJongID(unsigned int main_type, unsigned int sub_type)
{
    
    unsigned int mjType = 0;
    
    switch (main_type)
    {
        case TYPE_ZFB:
        {
            switch (sub_type) {
                case SUB_TYPE_ZHONG:
                {
                    mjType = 10001;
                }
                    break;
                case SUB_TYPE_FA:
                {
                    mjType = 10002;
                }
                    break;
                case SUB_TYPE_BAI:
                {
                    mjType = 10003;
                }
                    break;
                default:
                    //                    CCAssert(0, "[MJHeler] TYPE_ZFB: 没有对应的麻将类型");
                    break;
            }
        }
            break;
            //东南西北
        case TYPE_DNXB:
        {
            switch (sub_type) {
                case SUB_TYPE_DONG:
                {
                    mjType = 20001;
                }
                    break;
                case SUB_TYPE_NAN:
                {
                    mjType = 20002;
                }
                    break;
                case SUB_TYPE_XI:
                {
                    mjType = 20003;
                }
                    break;
                case SUB_TYPE_BEI:
                {
                    mjType = 20004;
                }
                    break;
                    
                default:
                    //                    CCAssert(0, "[MJHeler] TYPE_DNXB: 没有对应的麻将类型");
                    break;
            }
        }
            break;
        case TYPE_WAN:
        {
            //万、索、筒一样
            
            switch (sub_type) {
                case SUB_TYPE_1:
                {
                    mjType = 30001;
                }
                    break;
                case SUB_TYPE_2:
                {
                    mjType = 30002;
                }
                    break;
                case SUB_TYPE_3:
                {
                    mjType = 30003;
                }
                    break;
                case SUB_TYPE_4:
                {
                    mjType = 30004;
                }
                    break;
                case SUB_TYPE_5:
                {
                    mjType = 30005;
                }
                    break;
                case SUB_TYPE_6:
                {
                    mjType = 30006;
                }
                    break;
                case SUB_TYPE_7:
                {
                    mjType = 30007;
                }
                    break;
                case SUB_TYPE_8:
                {
                    mjType = 30008;
                }
                    break;
                case SUB_TYPE_9:
                {
                    mjType = 30009;
                }
                    break;
                    
                default:
                    //                    CCAssert(0, "[MJHeler] TYPE_WAN: 没有对应的麻将类型");
                    break;
            }
        }
            break;
        case TYPE_SUO:
        {
            switch (sub_type) {
                case SUB_TYPE_1:
                {
                    mjType = 40001;
                }
                    break;
                case SUB_TYPE_2:
                {
                    mjType = 40002;
                }
                    break;
                case SUB_TYPE_3:
                {
                    mjType = 40003;
                }
                    break;
                case SUB_TYPE_4:
                {
                    mjType = 40004;
                }
                    break;
                case SUB_TYPE_5:
                {
                    mjType = 40005;
                }
                    break;
                case SUB_TYPE_6:
                {
                    mjType = 40006;
                }
                    break;
                case SUB_TYPE_7:
                {
                    mjType = 40007;
                }
                    break;
                case SUB_TYPE_8:
                {
                    mjType = 40008;
                }
                    break;
                case SUB_TYPE_9:
                {
                    mjType = 40009;
                }
                    break;
                default:
                    //                    CCAssert(0, "[MJHeler] TYPE_SUO: 没有对应的麻将类型");
                    break;
            }
        }
            break;
        case TYPE_TONG:
        {
            switch (sub_type) {
                case SUB_TYPE_1:
                {
                    mjType = 50001;
                }
                    break;
                case SUB_TYPE_2:
                {
                    mjType = 50002;
                }
                    break;
                case SUB_TYPE_3:
                {
                    mjType = 50003;
                }
                    break;
                case SUB_TYPE_4:
                {
                    mjType = 50004;
                }
                    break;
                case SUB_TYPE_5:
                {
                    mjType = 50005;
                }
                    break;
                case SUB_TYPE_6:
                {
                    mjType = 50006;
                }
                    break;
                case SUB_TYPE_7:
                {
                    mjType = 50007;
                }
                    break;
                case SUB_TYPE_8:
                {
                    mjType = 50008;
                }
                    break;
                case SUB_TYPE_9:
                {
                    mjType = 50009;
                }
                    break;
                default:
                    //                    CCAssert(0, "[MJHeler] TYPE_TONG: 没有对应的麻将类型");
                    break;
            }
        }
            break;
            //        case TYPE_HUA:
            //        {
            //
            //        }
            break;
        default:
            //            CCAssert(0, " [MJHelper] 未找到此信息对饮的牌");
            break;
    }
    
    return mjType;
}

std::string MJHelper::convertToMahJongImageID(unsigned int mahjongID, kMaJongShowType mjShowType)
{
    //得到 麻将 标示 id
    
    std::string head_str;
    std::string id_str = getstring(mahjongID);
    
    switch (mjShowType)
    {
        case kMaJongLying_Left:
        {
            head_str = getstring(kMaJongLying_Left);
        }
            break;
        case kMaJongStanding_Left:
        {
            head_str = getstring(kMaJongStanding_Left);
        }
            break;
        case kMaJongStanding_Front:
        {
            head_str = getstring(kMaJongStanding_Front);
        }
            break;
        default:
            //            CCAssert(0, "[MJHelper::convertToMahJongImageID] 没有这种展示牌的方式 %d",int(mjShowType));
            break;
    }
    
    head_str.append(id_str);
    return head_str;
}

std::string MJHelper::getstring(const unsigned int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}

std::string MJHelper::getstring(const char *c)
{
    std::stringstream newstr;
    newstr<<c;
    return newstr.str();
}

int MJHelper::getint(const std::string str)
{
    return atoi(str.c_str());
}

const char* MJHelper::getChar(const unsigned int n)
{
    return  getstring(n).c_str();
}

std::string MJHelper::formatGold(unsigned int gold,bool showFormat,unsigned int place,unsigned int div,std::string gName,std::string div_symbol)
{
    std::string returnStr = "";

    
    if (gold <= 0) {
        returnStr = "0";
        return returnStr;
    }

    std::string temStr = MJHelper::getstring(gold);
    int temStrLength = temStr.size();//长度
    
    if (div < 1) {
        div = 0;
    }else if(div > temStrLength)
    {
        div = temStrLength;
    }
    
    std::string gold_l = "",gold_r = "";
    
    if (temStrLength <= place) {//不大于参数值
        
        if (temStrLength <= div) {
            
            return temStr;
            
        }else{
            
            gold_l = temStr.substr(0,1);
            gold_r = temStr.substr(1);
           
            return gold_l + div_symbol + gold_r;
        }
        
        
    }else
    {
        if (showFormat) {
            temStr = temStr.substr(0,temStrLength - place);
            temStrLength = temStr.size();
        }
        
        int dotNum = (temStrLength - 1)/div;//得到需要的标记位数量。第一个数字前面不需要标记
        int remainder = -1;
        remainder = fmodf(temStrLength, div);
        
        int num = 0,dotNumTem = dotNum;
        std::string returnStrTem = "";
        
        if(remainder == 0) remainder = 3;
        
        returnStr = temStr.substr(0,remainder);
        
        if (dotNum > 0) {
            returnStr = returnStr + div_symbol;
        }

        while (dotNumTem--) {
            
            returnStrTem = temStr.substr(remainder + div * num,div);
            
            if (dotNumTem == 0) {
                returnStr = returnStr + returnStrTem;
            }else
            {
                returnStr = returnStr + returnStrTem + div_symbol;
            }
            
            num++;
            
        }
        
        if (showFormat) {
            returnStr += gName;
        }
        
        return returnStr;
        
    }
        
}


int MJHelper::max(int int1, int int2, int int3)
{
    int tem1 = int1 < int2 ? int2:int1;
    int tem2 = int2 < int3 ? int3:int2;
    
    if (tem1 > tem2) {
        return tem1;
    }else
    {
        return tem2;
    }
}


int MJHelper::min(int int1, int int2, int int3)
{
    int tem1 = int1 > int2 ? int2:int1;
    int tem2 = int2 > int3 ? int3:int2;
    
    if (tem1 > tem2) {
        return tem2;
    }else
    {
        return tem1;
    }
}


void MJHelper::addMJ3DimensionalCoordinate(int layer, cocos2d::CCNode *node)
{
    std::string layerName;
    layerName = layerName + ISBeCovered + getstring(layer);
    
    GameState *gs = GameState::getInstance();
    
    if (gs->getGlobalObject(layerName.c_str()) == NULL)
    {
        CCArray *layerArr = new CCArray();
        layerArr->addObject(node);//添加到数组中
        gs->setGlobalObject(layerName.c_str(), layerArr);
        CC_SAFE_RELEASE(layerArr);
    }else
    {
        CCArray *layerArr = (CCArray*)gs->getGlobalObject(layerName.c_str());
        
        layerArr->addObject(node);
    }
}

bool MJHelper::isBeCovered(int layer, cocos2d::CCNode *node)
{
    CCPoint mjPoint = node->getPosition();
    CCSize mjsize = node->getContentSize();
    CCRect mjRect = CCRectMake(mjPoint.x, mjPoint.y, mjsize.width, mjsize.height);//得到要检测麻将的尺寸
    
    mjRect = getZoomRect(0.8, mjRect);
    
    std::string overLayerName;
    overLayerName = overLayerName + ISBeCovered + getstring(layer + 1);//检查将要移除的牌的上面一层
    
    GameState *gs = GameState::getInstance();
    CCArray *layerArr =(CCArray*)gs->getGlobalObject(overLayerName.c_str());
    
    bool covered = false;//没有被覆盖
    
    if (layerArr != NULL) {
        for (int arrNum = 0;arrNum < layerArr->count(); arrNum++)
        {
            CCNode *overNode = (CCNode*)layerArr->objectAtIndex(arrNum);
            CCPoint overPoint = overNode->getPosition();
            CCSize overSize = overNode->getContentSize();
            CCRect overRect = CCRectMake(overPoint.x, overPoint.y, overSize.width, overSize.height);
            
            overRect = getZoomRect(0.8, overRect);
            
            if (mjRect.intersectsRect(overRect)) {
                covered = true;//被覆盖了
            };
        }
    }
    
    return covered;
    
}

bool MJHelper::setCovered(int layer)
{
    if (layer >= 0)//从第一层开始
    {
        GameState *gs = GameState::getInstance();
        
        std::string layerName;
        layerName = layerName + ISBeCovered + MJHelper::getstring(layer);
        CCArray *layerArr =(CCArray*)gs->getGlobalObject(layerName.c_str());
        
        for (int num = 0; num < layerArr->count(); num++)
        {
            MJUnitSprite *mj = (MJUnitSprite*)layerArr->objectAtIndex(num);//得到的是当前层的麻将
            
            if (MJHelper::isBeCovered(layer, mj)) //判断本层的麻将是否被上一层覆盖
            {
                mj->setBeCovered(true);//检测到被遮盖了 就加上遮罩层
            }else
            {
                mj->setBeCovered(false);//当检测到没被其他牌遮盖的时候就 去除遮罩
            }
        }
        
        return true;
    }else
    {
        return false;
    }

}

bool MJHelper::deleteMJGlobalInfo(int layer, cocos2d::CCNode *node)
{
    std::string layerName;
    layerName = layerName + ISBeCovered + getstring(layer);
    GameState *gs = GameState::getInstance();
    CCArray *layerArr =(CCArray*)gs->getGlobalObject(layerName.c_str());
    
    bool isDelete = false;
    
    if (layerArr != NULL && layerArr->containsObject(node)) {
     
        layerArr->removeObject(node);
        isDelete = true;
    }
    
//    if (layerArr->count() <= 0) {
//        gs->removeGlobalObject(layerName.c_str());
//    }
    
    return isDelete;
}

bool MJHelper::clearMJGlobalInfo()
{
    
    for (int layers = 0;layers < KMahJongLayer_Amount  ; layers++) {
        std::string layerName;
        layerName = layerName + ISBeCovered + getstring(layers);        
        GameState *gs = GameState::getInstance();
        gs->removeGlobalObject(layerName.c_str());
    }
    
    return true;
}

CCRect MJHelper::getZoomRect(float czoom, cocos2d::CCRect rect)
{
    CCRect zoomRect =CCRectMake(rect.origin.x, rect.origin.y,rect.size.width*czoom,rect.size.height*czoom);
    
    return zoomRect;
}

std::string MJHelper::timeFormat(int minutes, int secondes,int hour)
{
    std::string timeStr;
    
    if (hour != 0)
    timeStr = getstring(hour) + "时";
    
    timeStr = timeStr + getstring(minutes) + "分";
    timeStr = timeStr + getstring(secondes) + "秒";
    
    return timeStr;
}

cocos2d::CCRect MJHelper::rect(CCNode *node)
{
    return CCRectMake(node->getPositionX() - node->getContentSize().width * node->getAnchorPoint().x,
                      node->getPositionY() - node->getContentSize().height * node->getAnchorPoint().y,
                      node->getContentSize().width, node->getContentSize().height); // 为了能够自定义自己的位置大小采用了低效的函数而不是直接用成员变量
}


double MJHelper::random(double start, double end)
{
    
    float ran = start +(end - start)*rand()/(RAND_MAX + 1.0);
    
    return ran;
}

bool MJHelper::isChineseChar(const char *pCh)
{
//    bool fChar = false;
//    bool sChar = false;
    bool isChinese = false;
    
    if (pCh == NULL) {
        return false;
    }
    
    int i = 0;
    for (; pCh[i] != '\0'; i++) {
        //ASCII character
        if (!(pCh[i]&0x80)) {
            continue;
        }else if(!((pCh[i]&0xf0)^0xe0)
                 &&pCh[i+1]
                 &&!((pCh[i+1]&0xc0)^0x80)
                 &&pCh[i+2]
                 &&!((pCh[i+2]&0xc0)^0x80))//汉字编码
        {
            isChinese = true;
        }
    }

    return isChinese;
    
}

CCActionInterval* MJHelper::jumpAndZoom(cocos2d::CCPoint point, float jumpHeight, unsigned int times, float dur,float s,bool loop,float dur_offset)
{
    float one_act = dur/4;
    
//    CCJumpBy *jump1 = CCJumpBy::create(one_act,point , jumpHeight, times);
//    CCJumpBy *jump2 = CCJumpBy::create(one_act*2,ccpMult(point, -1 *2) , jumpHeight, times*2);
//    CCJumpBy *jump3 = CCJumpBy::create(one_act, point, jumpHeight, times);
    
    CCMoveBy *move1 = CCMoveBy::create(one_act, point);
    CCMoveBy *move2 = CCMoveBy::create(one_act * 2, ccpMult(point, -1 *2));
    CCMoveBy *move3 = CCMoveBy::create(one_act, point);
    
    if (dur_offset <=0 || dur_offset >=1) {
        dur_offset = 0.5;
    }
    
    CCScaleTo *scale1 = CCScaleTo::create(dur*dur_offset, s);
    CCScaleTo *scale2 = CCScaleTo::create(dur*(1 - dur_offset),1);
    
    CCSequence *seque1 = CCSequence::create(move1,move2,move3,NULL);
    CCSequence *seque2 = CCSequence::create(scale1,scale2,NULL);
    
    CCSpawn *spawn = CCSpawn::create(seque1,seque2,NULL);
    
    
    CCActionInterval *repeat;
    if (loop) {
        repeat = CCRepeatForever::create(spawn);
    }else{
        repeat = CCRepeat::create(spawn, times);
    }
    
    return repeat;
 
}

void MJHelper::afterJumpAndZoom(cocos2d::CCNode *node)
{
    node->setAnchorPoint(CCPointZero);
}

bool MJHelper::isTheSameSequences(unsigned int head1, unsigned int mid1, unsigned int end1, unsigned int head2, unsigned int mid2, unsigned int end2)
{

    unsigned int sequen1_max = max(head1, mid1, end1);
    unsigned int sequen1_min = min(head1, mid1, end1);
    
    unsigned int sequen2_max = max(head2, mid2, end2);
    unsigned int sequen2_min = min(head2, mid2, end2);
    
    if (sequen1_max == sequen2_max && sequen1_min == sequen2_min) {
        return true;
    }
    
    
    return false;

}










