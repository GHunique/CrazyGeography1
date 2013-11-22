//
//  XMLOperation.h
//  myTinyxml2
//
//  Created by xiangshouyong on 13-10-17.
//
//

#ifndef __myTinyxml2__XMLOperation__
#define __myTinyxml2__XMLOperation__

#include "cocos2d.h"
using namespace std;

//第一种读取方式 结构体
typedef std::map<std::string, std::string> KeyVaMap;
typedef std::vector<KeyVaMap> xmlArray;
typedef std::map<std::string, xmlArray> xmlDictionary;

//第二种读取方式 结构体
typedef std:: map<std::string, KeyVaMap> xmlDictionary1;

class XMLOperation {
    
public:
    
    /**
     * 第一种读取方式文件结构是
     *
     * dict < n~dic <
     */
    static void readXML(const char* filePath);
    static void readAttribute(tinyxml2::XMLElement *ele,xmlDictionary &xmlDic);
    static cocos2d::CCDictionary *xmlDicSwitchToCCDic(const char* filePath,bool fullPath = false);//默认的是相对路径,
    
    /**
     *  第二种文件结构读取方式 (推荐)
     */
    static void readXML1(const char* filePath);
    static void readAttribute1(tinyxml2::XMLElement *ele,xmlDictionary1 &xmlDic1);
    
    /**
     * @param filePath 文件名称。
     * @param defId 每一条信息唯一标示符 键名
     * @return 返回一个字典。这个字典的元素是多个子字典，这些多个子字典按照键值对保存每信息。
     */
    static cocos2d::CCDictionary *xmlDicSwitchToCCDic1(const char* filePath,std::string defId = "id",bool fullPath = false);//默认的是每条数据的唯一标示字段为 "id";默认的是相对路径,fullPath = false 标示不需要绝对路径
    /**
     * @param   filePath  修改的文件路径
     * @param   elementId xml 每一条数据的唯一标示符 值;
     * @param   name 需要修改的字段名字; value 修改的值
     * @param   defId 默认的xml数据的唯一标示符 键
     * @param   fullPath 默认false表示不需要绝对路径
     * @return  是否修改 true 表示修改成功
     */
    static bool fixAttribute1(const char* filePath,const char *elementId,const char *name,const char *value,const char* defId = "id",bool fullPath = false);

};

/**
 * 扩展的xml文件加密类
 */
#include <iostream>
class XmlEDocument : public tinyxml2::XMLDocument
{
private:
    const std::string ENCR_KEY = "zhuxiaoc";
    const int READ_SIZE = 16*1024;
public:
    void Load(string filename)
    {
       
    }
};

#endif /* defined(__myTinyxml2__XMLOperation__) */
