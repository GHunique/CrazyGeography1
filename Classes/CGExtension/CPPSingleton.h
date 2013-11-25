//
//  CPPSingleton.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-5.
//
//

#ifndef __CrazyGeography__CPPSingleton__
#define __CrazyGeography__CPPSingleton__

#include "cocos2d.h"

template <typename _TS>

class CPPSingleton
{
    
public:
    static _TS *instance()
    {
       
        
        if (s_instance == NULL) {
            s_instance = new _TS();
        }
        
        return s_instance;
    }
    
protected:
    
    CPPSingleton()
    {
         CC_ASSERT(s_instance == NULL);
    }
    
private:
    static _TS *s_instance;
    
    //定义一个内嵌类用于删除单例。系统会自动调用它的析构函数
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if(CPPSingleton::s_instance)
                delete CPPSingleton::s_instance;
        }
    };
    
    static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数
};
#define STORE_SINGLETON_INSTANCE(_TS) \
template<> _TS* Singleton<_TS>::pInstance_ = NULL;

#endif /* defined(__CrazyGeography__CPPSingleton__) */
