//
//  CGAccessaryButton.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-18.
//
//

#ifndef __CrazyGeography__CGAccessaryButton__
#define __CrazyGeography__CGAccessaryButton__

#include "CGconfig.h"

class CGButton : public UIWidget
{
public:
    CGButton();
    ~CGButton();
    
    void setCGButtonTouchEnable(bool enable);
    void addCGButtonTouchEventListener(cocos2d::CCObject *target, SEL_TouchEvent selector);
    
    /**
     * 设置按钮星级和显示名字
     */
    void setStarNumber(int num);
    void setShortName(const char* sName);
    
    void setChapterId(int chapterId);
    int  getChapterId();
    void setPassId(int passId);
    int  getPassId();
    
protected:
    
    UIButton* provinceButton();
    UIButton* passButton();
    UIButton* notPassButton();
    
    Layout *_accessary_root;
    UIButton* _onlybutt;
    
private:
    
    int _chapter_id;        //章节id
    int _pass_id;           //关卡id
};

#pragma mark - ProvinceButton class

class ProvinceButton : public CGButton
{
public:
    
    CREATE_FUNC(ProvinceButton);
    bool init();
    void lock(bool lock);   //图标被锁定

};

#pragma mark - PassButton class

class PassButton : public CGButton
{
public:
    
    CREATE_FUNC(PassButton);
    bool init();
    
};

#pragma mark - NotPassButton class

class NotPassButton : public CGButton
{
public:
    
    CREATE_FUNC(NotPassButton);
    bool init();
    
};


#endif /* defined(__CrazyGeography__CGAccessaryButton__) */
