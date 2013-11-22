//
//  SharedMultiPlatform.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-11.
//
//

#ifndef __CrazyGeography__SharedMultiPlatform__
#define __CrazyGeography__SharedMultiPlatform__

#include <iostream>


class SharedMultiPlatform 
{
public:
    ~SharedMultiPlatform();
    SharedMultiPlatform();
    
    void registerApp();
    void sharedAllPlatForm();

    /**
     * 取消授权
     */
    void cancelAuth(int type);
    
private:

    void registerAppWithIOSPlatform();
    void registerAppWithAndroidPlatform();
    bool isregistedIOSApp();
    
private:
    bool _regist_ios;
    bool _regist_android;
};

#endif /* defined(__CrazyGeography__SharedMultiPlatform__) */
