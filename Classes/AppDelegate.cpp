#include "AppDelegate.h"
#include "MacroDefine.h"
#include "AheadChapter.h"
#include "GlobalUserDefault.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
    
    CCDirector *yDirector = CCDirector::sharedDirector();
    CCEGLView *yEGLView = CCEGLView::sharedOpenGLView();
    
    yDirector->setOpenGLView(yEGLView);
    yDirector->setDisplayStats(false);
    
    yDirector->setAnimationInterval(1.0/60);
    
    CCSize screenSize = CG_ScreenSize;
    CCSize designSize = DESIGN_RESOLUTION_960X640_V;
   
    std::vector<std::string> searchPaths;
    CCSize resourceSize = designSize;
    
    /**
    if(screenSize.height > DESIGN_RESOLUTION_1024X768_V.height)
    {
        searchPaths.push_back("ipad@x2");
        resourceSize = DESIGN_RESOLUTION_2048X1536_V;
    }
    else if (screenSize.height > DESIGN_RESOLUTION_960X640_V.height)
    {
        searchPaths.push_back("ipad");
        resourceSize = DESIGN_RESOLUTION_1024X768_V;
    }else if(screenSize.height > DESIGN_RESOLUTION_480X320_V.height)
    {
        searchPaths.push_back("iphone@x2");
        resourceSize = DESIGN_RESOLUTION_960X640_V;
    }else
    {
        searchPaths.push_back("iphone");
        resourceSize = DESIGN_RESOLUTION_480X320_V;
    }
    */
    
    searchPaths.push_back("ipad");
    resourceSize = DESIGN_RESOLUTION_960X640_V;
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);        //设置搜索路径
    
//    yDirector->setContentScaleFactor(resourceSize.height/designSize.height);
 
    yEGLView->setDesignResolutionSize(designSize.width, designSize.height,kResolutionExactFit);
    
    CCScene *scene = CCScene::create();                 //添加场景
    AheadChapter *gameLayer = AheadChapter::create();
    scene->addChild(gameLayer);
    
    CCTransitionScene *transition = CCTransitionProgressVertical::create(0.2, scene);
    yDirector->runWithScene(transition);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
