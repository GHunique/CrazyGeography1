//
//  TDInvFileUtils.h
//  CrazyGeography
//
//  Created by yong on 13-11-21.
//
//

#ifndef __CrazyGeography__TDInvFileUtils__
#define __CrazyGeography__TDInvFileUtils__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/** 负责操作文件储存和读取
 */

class TDInvFileUtils {
public:
    /** 读取本地文件，返回数据 */
    static string getFileByName(string pFileName);
    
    /** 储存内容到文件 */
    static bool saveFile(const char* pContent,string pFileName);
    
};


#endif /* defined(__CrazyGeography__TDInvFileUtils__) */
