//
//  CGHelper.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-10-29.
//
//

#ifndef __CrazyGeography__CGHelper__
#define __CrazyGeography__CGHelper__

#include <iostream>
#include "vector.h"
#include "math.h"

class CGHelper {
    
public:
    
    /**
     * 将 整数类型转化为c++ 字符串
     *  @param      n 为待转化的整数
     *  @return     返回一个 string
     */
    static std::string getstringFromint(const unsigned int n);
    
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
     * 将 浮点类型转化为c++ 字符串
     *  @param      fl 为待转化的浮点型
     *  @return     返回一个 string
     */
    static std::string getstring(const float fl);
    
    /**
     * 将 c++ 字符串 类型转化为浮点型
     *  @param      str 为待转化的 string
     *  @return     返回一个 浮点型
     */
    static float getfloat(const std::string str);
    
    /**
     *  判断是否有汉字
     */
    static bool isChineseChar(const char *pCh);
    
    /**
     * @param 从一个字符串  std::string str 中得到子字符串,会把一段连续的英取到一个字符串
     * @param  returnStrVector 传入一个对应类型地址
     * @return ture标示获得成功
     */
    static bool stringArrFromString(std::string str,std::vector<std::string> &returnStrVector);
    
    /**
     *  @param 从一个字符串 std::string str 中取得汉子和其他符号
     *  @param returnStrVector 传入一个对应类型地址
     *  @return ture标示获得成功
     */
    static bool stringArrFromChineseString(std::string str,std::vector<std::string> &returnStrVector);
    
    /**
     * 获得一个string字符串的长度包括汉子，和标点
     */
    static int stringLengthIncludeChinese(std::string str);
    
    /**
     *  @param 从一个非汉子的 std::string str 中取得其他符号
     *  @param returnStrVector 传入一个对应类型地址
     *  @return ture标示获得成功
     */
    static bool stringArrFromNonChineseString(std::string str,std::vector<std::string> &returnStrVector);
    
    /**
     * 获得一个string字符串的长度，和标点
     */
    static int stringLengthExceptChinese(std::string str);
    
    /**
     * @param  T 一种基础数据类型 可以是 int double float
     * @return T 返回一个随机数
     * @brief  用之前调用 srand(unsigned(time(0))) 就能设置不同的随机种子
     */
    
    template <typename T>
    static T randomNumber(T begin, T end)
    {
        double random_rand = rand()/(RAND_MAX + 1.0);
        double random_num = (begin+(end-begin)*random_rand);
        cout<<"随机数参考数:"<<random_rand<<"  随机数生成："<<random_num<<endl;
        return (T)random_num;
    }
    
    /**
     * 字符串拆分函数
     */
    static  std::vector<std:: string> split(std:: string str,std:: string pattern);
};

#endif /* defined(__CrazyGeography__CGHelper__) */
