//
//  91PlatformConfigure.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-25.
//
//

#ifndef __CrazyGeography__91PlatformConfigure__
#define __CrazyGeography__91PlatformConfigure__


#include "CPPSingleton.h"

class NOPlatformConfigure :public CPPSingleton<NOPlatformConfigure>
{
public:
    
    void logout91platform(int type);
    
private:
    NOPlatformConfigure();
    ~NOPlatformConfigure();
    
    friend CPPSingleton;
    
};

#endif /* defined(__CrazyGeography__91PlatformConfigure__) */
