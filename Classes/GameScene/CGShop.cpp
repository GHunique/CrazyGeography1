//
//  CGShop.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-26.
//
//

#include "CGShop.h"
#include "GlobalUserDefault.h"

enum  {
    kBUY_280_$_6        = 2806,
    kBUY_600_$_12       = 60012,
    kBUY_1600_$_30      = 160030,
    kBUY_3800_$_68      = 380068,
    kBUY_8000_$_128     = 8000128,
    };

enum  {
    kCGShopBegin = 0,
    kCommId = kCGShopBegin,
    kCommName ,
    };

const char * shopInfo[2] =
{
    "",
    "",
};

bool CGShop::init()
{
    if (!CCLayerRGBA::init()) return false;
    
    _sUILayer = UILayer::create();
    this->addChild(_sUILayer);
    
    _shop_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kGameShopUI].c_str()));
    _sUILayer->addWidget(_shop_root);
    
    UIButton *butt6     = static_cast<UIButton *>(_shop_root->getChildByName("buy_butt_6"));
    UIButton *butt12    = static_cast<UIButton *>(_shop_root->getChildByName("buy_butt_12"));
    UIButton *butt30    = static_cast<UIButton *>(_shop_root->getChildByName("buy_butt_30"));
    UIButton *butt68    = static_cast<UIButton *>(_shop_root->getChildByName("buy_butt_68"));
    UIButton *butt128   = static_cast<UIButton *>(_shop_root->getChildByName("buy_butt_128"));
    butt6->addTouchEventListener(this, toucheventselector(CGShop::buyGold)); butt6->setTag(kBUY_280_$_6);
    butt12->addTouchEventListener(this, toucheventselector(CGShop::buyGold)); butt12->setTag(kBUY_600_$_12);
    butt30->addTouchEventListener(this, toucheventselector(CGShop::buyGold)); butt30->setTag(kBUY_1600_$_30);
    butt68->addTouchEventListener(this, toucheventselector(CGShop::buyGold)); butt68->setTag(kBUY_3800_$_68);
    butt128->addTouchEventListener(this, toucheventselector(CGShop::buyGold));butt128->setTag(kBUY_8000_$_128);
    
    return true;
}

void CGShop::buyGold(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    float price = 0.0;
    int count = 1;
    
    switch (pSender->getTag())
    {
        case kBUY_280_$_6:
        {
            price = 6;
        }
            break;
        case kBUY_600_$_12:
        {
            price = 12;
        }
            break;
        case kBUY_1600_$_30:
        {
            price = 30;
        }
            break;
        case kBUY_3800_$_68:
        {
            price = 68;
        }
            break;
        case kBUY_8000_$_128:
        {
            price = 128;
        }
            break;
        default:
            break;
    }
    
    if (price != 0.0)
    {
        GlobalUserDefault::instance()->buyCommodities(shopInfo[kCommId], shopInfo[kCommName],price,count);
    }
    else
    {
        
    }
}



