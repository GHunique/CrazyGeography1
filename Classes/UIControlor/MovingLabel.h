//
//  MovingLabel.h
//  CrazyGeography
//
//  Created by yong on 13-12-11.
//
//

#ifndef __CrazyGeography__MovingLabel__
#define __CrazyGeography__MovingLabel__

#include "CGconfig.h"

class MovingLabel : public Layout {
    
public:
    CREATE_FUNC(MovingLabel);
    
    bool init();
    
    void setMovingInfo(float detal);
    void setTexture(const char* contents);
private:
    UILabel *_movingLabel;
    
    void removeThisFromParent();
};

#endif /* defined(__CrazyGeography__MovingLabel__) */
