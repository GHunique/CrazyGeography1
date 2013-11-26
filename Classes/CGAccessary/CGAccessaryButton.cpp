//
//  CGAccessaryButton.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-18.
//
//

#include "CGAccessaryButton.h"
#include "CGHelper.h"

CGButton::CGButton()
:_pass_id(0)
,_chapter_id(0)
{
    _accessary_root = static_cast<Layout *>(CCUIHELPER->createWidgetFromJsonFile(CG_GamePathes[kChapter_Accessary].c_str()));
}

CGButton::~CGButton()
{
    
}

UIButton* CGButton::provinceButton()
{
    return static_cast<UIButton *>(_accessary_root->getChildByName("province_butt"));
}

UIButton* CGButton::passButton()
{
    return static_cast<UIButton *>(_accessary_root->getChildByName("pass_butt"));
}

UIButton* CGButton::notPassButton()
{
    return static_cast<UIButton *>(_accessary_root->getChildByName("notPass_butt"));
}

void CGButton::setCGButtonTouchEnable(bool enable)
{
    _onlybutt->setTouchEnable(enable);
}

void CGButton::addCGButtonTouchEventListener(cocos2d::CCObject *target, SEL_TouchEvent selector)
{
    _onlybutt->addTouchEventListener(target, selector);
}

void CGButton::setStarNumber(int num)
{
    
    for (int i = 0; i < 3; i++)     //初始化，没有一颗星
    {
        std::string star_image_name = "star_image_";
        star_image_name.append(CGHelper::getstring(i));
        UIImageView *starImage = (UIImageView *)_onlybutt->getChildByName(star_image_name.c_str());
        starImage->loadTexture("xing-xing0.png",UI_TEX_TYPE_PLIST);
    }
    
    for (int i = 0; i < num; i++)
    {
        std::string star_image_name = "star_image_";
        star_image_name.append(CGHelper::getstring(i));
        UIImageView *starImage = (UIImageView *)_onlybutt->getChildByName(star_image_name.c_str());
        starImage->loadTexture("xing-xing1.png",UI_TEX_TYPE_PLIST);
    }
    
}

void CGButton::setShortName(const char *sName)
{
    UILabelBMFont *sNameLabel = static_cast<UILabelBMFont *>(_onlybutt->getChildByName("labelBMF"));
    sNameLabel->setText(sName);
}

void CGButton::setChapterId(int chapterid)
{
    _chapter_id = chapterid;
}

int CGButton::getChapterId()
{
    return _chapter_id;
}

void CGButton::setPassId(int passId)
{
    _pass_id = passId;
}

int CGButton::getPassId()
{
    return _pass_id;
}

#pragma mark - ProvinceButton
bool ProvinceButton::init()
{
    if (!CGButton::init()) return false;
    
    //取得章节按钮
    _onlybutt = static_cast<UIButton *>(_accessary_root->getChildByName("province_butt"));
    _onlybutt->setPosition(CCPointZero);
    CC_SAFE_RETAIN(_onlybutt);
    _onlybutt->removeFromParent();
    this->addChild(_onlybutt);
    CC_SAFE_RELEASE(_onlybutt);
    
    return true;
}

void ProvinceButton::lock(bool lock)
{
    UIImageView *lock_image = static_cast<UIImageView *>(_onlybutt->getChildByName("lock_image"));
    lock_image->setZOrder(4);
    UILabelBMFont *sNameLabel = static_cast<UILabelBMFont *>(_onlybutt->getChildByName("labelBMF"));
    
    if (lock) {
        this->setColor(ccGRAY);
        this->setCGButtonTouchEnable(false);
        lock_image->setVisible(true);
        sNameLabel->setVisible(false);
    }else{
        this->setColor(ccWHITE);
        this->setCGButtonTouchEnable(true);
        lock_image->setVisible(false);
        sNameLabel->setVisible(true);
    }
}

#pragma mark - PassButton class

bool PassButton::init()
{
    if (!CGButton::init()) return false;
    
    //取得关卡已经开启按钮
    _onlybutt = static_cast<UIButton *>(_accessary_root->getChildByName("pass_butt"));
    _onlybutt->setPosition(CCPointZero);
    CC_SAFE_RETAIN(_onlybutt);
    _onlybutt->removeFromParent();
    this->addChild(_onlybutt);
    CC_SAFE_RELEASE(_onlybutt);
    
    return true;
        
}

#pragma mark - NotPassButton class

bool NotPassButton::init()
{
    if (!CGButton::init()) return false;
    
    //关卡未开启按钮
    _onlybutt = static_cast<UIButton *>(_accessary_root->getChildByName("notPass_butt"));
    _onlybutt->setPosition(CCPointZero);
    CC_SAFE_RETAIN(_onlybutt);
    _onlybutt->removeFromParent();
    this->addChild(_onlybutt);
    CC_SAFE_RELEASE(_onlybutt);
    
    return true;
}







