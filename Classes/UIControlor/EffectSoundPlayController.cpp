//
//  EffectSoundPlayController.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-12-12.
//
//

#include "EffectSoundPlayController.h"
#include "SimpleAudioEngine.h"

bool EffectSoundPlayController::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    _playTimes = 0;
    _start = false;
    
    return true;
}

void EffectSoundPlayController::setEffect(const char *pFile, int playTimes, float playInterval, float delay)
{
    _pFile = pFile;
    _playTimes = playTimes;
    this->schedule(schedule_selector(EffectSoundPlayController::playEffect), playInterval, playTimes, delay);
}

void EffectSoundPlayController::playEffect()
{
    PLAY_EFFECT(_pFile);
    _playTimes--;
    
    if (_playTimes == 0)
    {
        CCLog("结束了。结束了`");
    }
}

void EffectSoundPlayController::setEffect(const char *pFile, float effectTime, cocos2d::CCArray *InterValTimeArr,float delay)
{
    //当前系统时间
    _pFile = pFile;
    _playTimes = InterValTimeArr->count();
    _currTimes = 0;
    _interValTimeArr = InterValTimeArr;
    _canPlayTime = ((CCString *)(InterValTimeArr->objectAtIndex(_currTimes)))->floatValue();
    
    
    CCTime::gettimeofdayCocos2d(&_startTimeval, NULL);
    
    if (delay) {
        _start = true;
    }else
    {
        this->scheduleOnce(schedule_selector(EffectSoundPlayController::setStart), delay);
    }
}

void EffectSoundPlayController::update(float dt)
{
    struct cc_timeval endTimeval;
    CCTime::gettimeofdayCocos2d(&endTimeval, NULL);
    
    double canPlayTime = CCTime::timersubCocos2d(&_startTimeval, &endTimeval);
    
    if (_start && _playTimes &&  canPlayTime >= _canPlayTime)
    {
        _playTimes--;
        _currTimes++;
        PLAY_EFFECT(_pFile);
        _canPlayTime = ((CCString *)(_interValTimeArr->objectAtIndex(_currTimes)))->floatValue();
    }
    
}

void EffectSoundPlayController::setStart(bool start)
{
    _start = true;
}

