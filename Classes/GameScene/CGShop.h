//
//  CGShop.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-26.
//
//

#ifndef __CrazyGeography__CGShop__
#define __CrazyGeography__CGShop__

#include "CGConfig.h"

class CGShop : public CCLayerRGBA
{
public:
    CREATE_FUNC(CGShop);
    bool init();
    
    void buyGold(UIButton *pSender,TouchEventType type); //购买金币
    
private:
    UILayer *_sUILayer;
    Layout  *_shop_root;
    
};

#endif /* defined(__CrazyGeography__CGShop__) */
