//
//  91PlatformConfigure.mm
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-25.
//
//

#include "91PlatformConfigure.h"
#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#define DEBUG_RELEASE_91 1


template<> NOPlatformConfigure* CPPSingleton<NOPlatformConfigure>::s_instance = NULL;

NOPlatformConfigure::NOPlatformConfigure()
{
    }

NOPlatformConfigure::~NOPlatformConfigure()
{
    
}

void NOPlatformConfigure::logout91platform(int type)
{
    
}
