//
//  XMLOperation.cpp
//  myTinyxml2
//
//  Created by xiangshouyong on 13-10-17.
//
//

#include "XMLOperation.h"
#include "CGconfig.h"

#define SHOW_MODULE 0

using namespace tinyxml2;
using namespace std;

static xmlDictionary _xmlDic;
static xmlDictionary1 _xmlDic1;
static std::string default_info_id = "id";

void XMLOperation::readXML(const char *filePath)
{
    XMLDocument *pDoc = new XMLDocument();
    pDoc->LoadFile(filePath);
    
    XMLElement *rootElement = pDoc->FirstChildElement();
    XMLElement *xElement = rootElement->FirstChildElement();
    
    while (xElement) {
        
        cout<<xElement->Name()<<endl;
        
        XMLOperation::readAttribute(xElement, _xmlDic);
        
        xElement = xElement->NextSiblingElement();
    }
    
    delete pDoc;
    
}

void XMLOperation::readAttribute(tinyxml2::XMLElement *ele, xmlDictionary &xmlDic)
{
    const tinyxml2::XMLAttribute *attr = ele->FirstAttribute();
    
    xmlArray xmlArr;
    
    while (attr) {
        KeyVaMap kvMap;
        std::string aName = attr->Name();
        std::string aValue = attr->Value();
        
        kvMap.insert(make_pair(attr->Name(), attr->Value()));
        
        xmlArr.push_back(kvMap);
    
        attr = attr->Next();
    }
    
    xmlDic.insert(make_pair(ele->Name(), xmlArr));//元素名字 -（对应）-- 元素属性数组
}

cocos2d::CCDictionary* XMLOperation::xmlDicSwitchToCCDic(const char* filePath,bool fullPath)
{
    char *path_char;
    
    if (!fullPath) {
        std::string fullpath_str = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
        sprintf(path_char, "%s",fullpath_str.c_str());
    }else
    {
        sprintf(path_char, "%s",filePath);
    }
    
    XMLOperation::readXML(path_char);//读取 并解析 xml 文件 (方法1)
    
    cocos2d::CCDictionary *ccDic = cocos2d::CCDictionary::create();//转换所需字典
    
    xmlDictionary::iterator xmlIt = _xmlDic.begin();
    
    for (; xmlIt != _xmlDic.end(); xmlIt++) {
        
        std::string dicKey = xmlIt->first;//每一条数据的名字 （ID）
        xmlArray dicValue = xmlIt->second;//数据数组
        
        cocos2d::CCArray *ccArr = cocos2d::CCArray::create();//转换所需数组
        
        xmlArray::iterator arrIt = dicValue.begin();
        for (; arrIt < dicValue.end(); arrIt++) {
            KeyVaMap kvMap = *arrIt;
            
            std::string akey = kvMap.begin()->first;//属性键
            
            if (akey.size() <= 0) {
                continue;
            }
            
            std::string avalue = kvMap.begin()->second;//属性值
            
            cocos2d::CCString *keyStr = cocos2d::CCString::createWithFormat("%s",akey.c_str());
            
            cocos2d::CCDictionary *dicTem = cocos2d::CCDictionary::create();
            dicTem->setObject(keyStr, avalue);
            
            ccArr->addObject(dicTem);
        }
        
        if (ccArr->count() > 0) {
            ccDic->setObject(ccArr, dicKey);
        }
        
    }
    _xmlDic.clear();
    return ccDic;
}

#pragma mark - second


void XMLOperation::readXML1(const char *filePath)
{
    CCLog("读取xml文件路径: %s",filePath);
    
    XMLDocument *pDoc = new XMLDocument();
    pDoc->LoadFile(filePath);
    
    XMLElement *rootElement = pDoc->FirstChildElement();
    XMLElement *xElement = rootElement->FirstChildElement();
    
    while (xElement) {
    
        if (SHOW_MODULE) cout<<"<"<<xElement->Name()<<">"<<endl;
        
        XMLOperation::readAttribute1(xElement,_xmlDic1);
        
        xElement = xElement->NextSiblingElement();
    }
    
    delete pDoc;
    
}

void XMLOperation::readAttribute1(tinyxml2::XMLElement *ele, xmlDictionary1 &xmlDic1)
{
    const tinyxml2::XMLAttribute *attr = ele->FirstAttribute();
    KeyVaMap kvMap;
    std::string dic_id;
    while (attr) {
        
        std::string aName = attr->Name();
        std::string aValue = attr->Value();
        
        if (strcmp(aName.c_str(), default_info_id.c_str()) == 0)
            dic_id = aValue;
        
        
        kvMap.insert(make_pair(attr->Name(), attr->Value()));
        
        if (SHOW_MODULE) cout<<"  键:"<<aName<<" == 值:"<<aValue<<endl;
        
        attr = attr->Next();
    }
    
    if (SHOW_MODULE) cout<<"</"<<ele->Name()<<">"<<" dic_id "<<dic_id<<endl;
    
    xmlDic1.insert(make_pair(dic_id, kvMap));//元素名字 -（对应）-- 元素值
}


cocos2d::CCDictionary* XMLOperation::xmlDicSwitchToCCDic1(const char* filePath,std::string defId,bool fullPath)
{
    std::string fullpath_str = filePath;
    default_info_id = defId;
    
    if (!fullPath) {
        fullpath_str.clear();
        fullpath_str = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
    }
    
    
    XMLOperation::readXML1(fullpath_str.c_str());//读取 并解析 xml 文件 （方法2）
    
    cocos2d::CCDictionary *ccDic = cocos2d::CCDictionary::create();//转换所需字典
    
    xmlDictionary1::iterator xmlIt = _xmlDic1.begin();
    
    for (; xmlIt != _xmlDic1.end(); xmlIt++) {
        
        std::string dicKey = xmlIt->first;//每一条数据的名字 （ID）
        KeyVaMap dicValue = xmlIt->second;//数据数组
        
        cocos2d::CCDictionary *valueDic = cocos2d::CCDictionary::create();
        
        KeyVaMap::iterator mapIt = dicValue.begin();
        for (; mapIt != dicValue.end(); mapIt++) {
            std::string aKey = mapIt->first;
            std::string aValue =  mapIt->second;
            
            //设置该条数据的唯一标示符字段 (要确保xml中已有该字段，默认是 "id")
            if (strcmp(aKey.c_str(), defId.c_str()) == 0)
            {
                dicKey.clear();
                dicKey = aValue; //拿 “id” 的值来作为本条数据的唯一标示
            }
            
            cocos2d::CCString *aValueStr = cocos2d::CCString::createWithFormat("%s",aValue.c_str());
            
            valueDic->setObject(aValueStr, aKey);
            
        }
        ccDic->setObject(valueDic, dicKey);
    }
    _xmlDic1.clear();
    return ccDic;
}

bool XMLOperation::fixAttribute1(const char *filePath, const char *elementId, const char *name, const char *value,const char* defId,bool fullPath)
{
    std::string fullpath_str = filePath;
    
    if (!fullPath)
    {
        fullpath_str.clear();
        fullpath_str = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
        
    }
    
    cout<<"修改文件读取的路径:"<<fullpath_str<<endl;
    
    XMLDocument *pDoc = new XMLDocument();
    pDoc->LoadFile(fullpath_str.c_str());
    
    XMLElement *rootElement = pDoc->FirstChildElement();
    XMLElement *xElement = rootElement->FirstChildElement();
    
    bool isFixed = false;
    
    while (xElement)//一条记录
    {
        if (strcmp(xElement->Attribute(defId),elementId) == 0)
        {
            xElement->SetAttribute(name, value);
//            cout<<"属性id 值："<<xElement->Attribute(defId)<<"比较id "<<elementId<<" name "<<name<<" value:"<<value<<endl;
            
        if (pDoc->SaveFile(fullpath_str.c_str()) == XML_SUCCESS) {
                isFixed = true;
            }
            break;

        }
    
        xElement = xElement->NextSiblingElement();
    }
    
    delete pDoc;
    
    return isFixed;
}



