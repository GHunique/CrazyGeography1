//
//  MovingLabel.cpp
//  CrazyGeography
//
//  Created by yong on 13-12-11.
//
//

#include "MovingLabel.h"


bool MovingLabel::init()
{
    if (!Layout::init()) {
        return false;
    }
    
    this->setSize(CCSizeMake(600, 60));
    this->setClippingEnable(true);
    this->setColor(ccWHITE);
    
    _movingLabel = UILabel::create();
    _movingLabel->setFontName("黑体");
    _movingLabel->setFontSize(30);
    _movingLabel->setAnchorPoint(ccp(0, 0));
    _movingLabel->setPosition(ccp(500,0));
    _movingLabel->setColor(ccc3(255, 255, 0));
    _movingLabel->setSizeType(SIZE_PERCENT);
    
    this->addChild(_movingLabel);
    
    
    
    return true;
}

void MovingLabel::setMovingInfo(float detal)
{
    CCSize labelSize = _movingLabel->getSize();
    CCActionInterval *movingTo = CCMoveTo::create(detal, ccp(-(labelSize.width/* + _movingLabel->getPosition().x*/),_movingLabel->getPosition().y));
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(MovingLabel::removeThisFromParent));
    
    _movingLabel->runAction(CCSequence::create(movingTo,callFunc,NULL));
}

void MovingLabel::setTexture(const char *contents)
{
    _movingLabel->setText(contents);
}



void MovingLabel::removeThisFromParent()
{
//    this->removeFromParentAndCleanup(bool cleanup)
    _movingLabel->setPosition(ccp(0,0));
}



