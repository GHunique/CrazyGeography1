//
//  CGHelper.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-10-29.
//
//

#include "CGHelper.h"

#include "sstream"

std::string CGHelper::getstringFromint(const unsigned int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}

std::string CGHelper::getstring(const char *c)
{
    std::stringstream newstr;
    newstr<<c;
    return newstr.str();
}

int CGHelper::getint(const std::string str)
{
    return atoi(str.c_str());
}

const char* CGHelper::getChar(const unsigned int n)
{
    return  getstring(n).c_str();
}

std::string CGHelper::getstring(const float fl)
{
    std::stringstream newstr;
    newstr<<fl;
    return newstr.str();
}

float CGHelper::getfloat(const std::string str)
{
    return atof(str.c_str());
}

bool CGHelper::isChineseChar(const char *pCh)
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

bool CGHelper::stringArrFromString(std::string str, std::vector<std::string> &returnStrVector)
{
    int begin_index = 0;
    int length = str.length();
    std::string tem_str;
    std::string englishTemp_str;        //保存连续的英文
    
    while (1) {
        
        tem_str = str.substr(begin_index,3);
        
        if (isChineseChar(tem_str.c_str()))
        {
            
            if (!englishTemp_str.empty())  //本次扫描已经是汉子了，所以保存上次连续的英文字母
            {
                std::cout<<"解析出来的 "<<englishTemp_str<<std::endl;
                returnStrVector.push_back(englishTemp_str);
                englishTemp_str.clear();
            }
            
            begin_index += 3;
            returnStrVector.push_back(tem_str);
            std::cout<<"解析出来的 "<<tem_str<<std::endl;
        }else
        {
            tem_str.clear();
            tem_str = str.substr(begin_index,1);
            begin_index += 1;
            englishTemp_str.append(tem_str);
        }
        
        
        
        if (begin_index == length)
        {
            if (!englishTemp_str.empty())
            {
                std::cout<<"解析出来的 "<<englishTemp_str<<std::endl;
                returnStrVector.push_back(englishTemp_str);
                englishTemp_str.clear();
            }
            break;
        }
    }
    
    return returnStrVector.size();
}

bool CGHelper::stringArrFromChineseString(std::string str, std::vector<std::string> &returnStrVector)
{
    int begin_index = 0;
    int length = str.length();
    std::string tem_str;
    
    while (1) {
    
         tem_str = str.substr(begin_index,3);
        
        if (isChineseChar(tem_str.c_str()))
        {
            begin_index += 3;
            returnStrVector.push_back(tem_str);
            
        }else
        {
            tem_str.clear();
            tem_str = str.substr(begin_index,1);
            begin_index += 1;
            returnStrVector.push_back(tem_str);
        }
        
//        std::cout<<"解析出来的 "<<tem_str<<std::endl;
        
        if (begin_index == length) break;
        
    }
    
    return returnStrVector.size();
}

int CGHelper::stringLengthIncludeChinese(std::string str)
{
    std::vector<std::string> str_arr;
    stringArrFromChineseString(str,str_arr);
    return str_arr.size();
}

bool CGHelper::stringArrFromNonChineseString(std::string str, std::vector<std::string> &returnStrVector)
{
    int begin_index = 0;
    int length = str.length();
    std::string tem_str;
    
    while (1) {
        
        tem_str = str.substr(begin_index,3);
        
        if (isChineseChar(tem_str.c_str()))
        {
            begin_index += 3;
        }else
        {
            tem_str.clear();
            tem_str = str.substr(begin_index,1);
            begin_index += 1;
            returnStrVector.push_back(tem_str);
        }
        
        if (begin_index == length) break;
        
    }
    
    return returnStrVector.size();
}

int CGHelper::stringLengthExceptChinese(std::string str)
{
    std::vector<std::string> str_arr;
    stringArrFromNonChineseString(str, str_arr);
    return str_arr.size();
}

// 字符串分割函数
std::vector<std:: string> CGHelper::split(std:: string str,std:: string pattern)
{
    std:: string::size_type pos;
    std::vector<std:: string> result;
    str+=pattern; // 扩展字符串以方便操作
    int size=str.size();
    
    for( int i= 0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std:: string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()- 1;
        }
    }
    return result;
}


