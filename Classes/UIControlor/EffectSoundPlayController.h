//
//  EffectSoundPlayController.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-12-12.
//
//

#ifndef __CrazyGeography__EffectSoundPlayController__
#define __CrazyGeography__EffectSoundPlayController__

#include "CGconfig.h"

class EffectSoundPlayController : public CCLayer
{
public:
    CREATE_FUNC(EffectSoundPlayController);
    
    bool init();
    
    /**
     * @param pFile 文件路径
     * @param playTimes 播放时间
     * @param playInterval 播放间隔
     * @param delay 延时
     */
    void setEffect(const char* pFile,int playTimes,float playInterval,float delay);
    
    /**
     * @param pFile 文件路径
     * @param effectTime 音效长度
     * @param InterValTimeArr 音效播放时间表 数组
     * @param delay 延时播放
     */
    
    void setEffect(const char* pFile,float effectTime,CCArray *InterValTimeArr,float delay = 0);
    
private:
    const char* _pFile;
    int _playTimes;
    int _currTimes;
    
    struct cc_timeval _startTimeval;     //当前系统时间
    float _canPlayTime;                  //间隔时间
    
    bool _start;                         //开始播放音效
    CCArray *_interValTimeArr;
    
    void playEffect();
    void update(float dt);
    
};

#endif /* defined(__CrazyGeography__EffectSoundPlayController__) */
