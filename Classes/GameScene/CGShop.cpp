//
//  CGShop.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-26.
//
//

#include "CGShop.h"
#include "GlobalUserDefault.h"
#include "GameLayer.h"

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
    
    UIButton *back_butt = static_cast<UIButton *>(_shop_root->getChildByName("back_butt")); //返回游戏界面按钮
    back_butt->setZOrder(5);
    back_butt->setTouchEnable(true);
    back_butt->addTouchEventListener(this, toucheventselector(CGShop::backButton));
    
    UIButton *login_butt = static_cast<UIButton *>(_shop_root->getChildByName("login_butt"));
    login_butt->setTouchEnable(true);
    login_butt->addTouchEventListener(this, toucheventselector(CGShop::loginButt));
    
    GlobalUserDefault::instance()->show91ToolBar(false);
    
    return true;
}

void CGShop::buyGold(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
   
    if (type != TOUCH_EVENT_ENDED)
        return;
    
    PLAY_EFFECT(TAP_EFFECT);
    float price = 0.0;
    int count = 1;
    const char * commId = "";
    const char *commNam = "";
    
    switch (pSender->getTag())
    {
        case kBUY_280_$_6:
        {
            price = kBuyGold_6RMB;
            commId = "110237-20131129-111716744-46";
            commNam = "280个金币";
        }
            break;
        case kBUY_600_$_12:
        {
            price = kBuyGold_12RMB;
            commId = "110237-20131129-135945194-16";
            commNam = "600个金币";
        }
            break;
        case kBUY_1600_$_30:
        {
            price = kBuyGold_30RMB;
            commId = "110237-20131129-140022225-34";
            commNam = "1600个金币";
        }
            break;
        case kBUY_3800_$_68:
        {
            price = kBuyGold_68RMB;
            commId = "110237-20131129-140145824-28";
            commNam = "3800个金币";
        }
            break;
        case kBUY_8000_$_128:
        {
            price = kBuyGold_128RMB;
            commId = "110237-20131129-140212870-31";
            commNam = "8000个金币";
        }
            break;
        default:
            break;
    }
    
    if (price != 0.0)
    {
        GlobalUserDefault::instance()->buyCommodities(commId, commNam,price,count);
    }
    else
    {
        //使用NdGetUserProduct() API 或NdGetUserProductsList() API
    }
}

void CGShop::backButton(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
            
        case TOUCH_EVENT_BEGAN:
        {
             PLAY_EFFECT(TAP_EFFECT);
        }
            break;
        case TOUCH_EVENT_ENDED:
        {
            CCScene *scene = CCScene::create();
            GameLayer *game = GameLayer::create();
            scene->addChild(game);
            
            CCTransitionScene *transition = GlobalUserDefault::instance()->randomTransitionScene(scene);
            CCDirector::sharedDirector()->replaceScene(transition);
        }
            break;
            
        default:
            break;
    }
}

void CGShop::loginButt(cocos2d::extension::UIButton *pSender, TouchEventType type)
{
    switch (type) {
            
        case TOUCH_EVENT_BEGAN:
        {
            PLAY_EFFECT(TAP_EFFECT);
        }
            break;
        case TOUCH_EVENT_ENDED:
        {
            GlobalUserDefault::instance()->enterAccountManage();
        }
            break;
            
        default:
            break;
    }
}

