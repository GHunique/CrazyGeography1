//
//  SharedMultiPlatform.cpp
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-11.
//
//

#include "SharedMultiPlatform.h"
#import <ShareSDK/ShareSDK.h>
#import "WXApi.h"
#import <TencentOpenAPI/QQApiInterface.h>
#import <TencentOpenAPI/TencentOAuth.h>


SharedMultiPlatform::SharedMultiPlatform()
{
    _regist_ios = false;
    _regist_android = false;
}

SharedMultiPlatform::~SharedMultiPlatform()
{
    
}

void SharedMultiPlatform::registerApp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    registerAppWithIOSPlatform();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    registerAppWithAndroidPlatform();
#endif
}

void SharedMultiPlatform::registerAppWithIOSPlatform()
{
    if (!_regist_ios)
        _regist_ios = true;
    else
        return;
    
    
    [ShareSDK registerApp:@"api20"];     //参数为ShareSDK官网中添加应用后得到的AppKey
    
    //添加新浪微博应用
//    [ShareSDK connectSinaWeiboWithAppKey:@"382748327"
//                               appSecret:@"83ad60eaebe18275adf7518f029a54aa"
//                             redirectUri:@"http://open.weibo.com"];
    
    [ShareSDK connectSinaWeiboWithAppKey:@"568898243"
                               appSecret:@"38a4f8204cc784f81f9f0daaf31e02e3"
                             redirectUri:@"http://www.sharesdk.cn"];
    
    //添加腾讯微博应用
    [ShareSDK connectTencentWeiboWithAppKey:@"801307650"
                                  appSecret:@"ae36f4ee3946e1cbb98d6965b0b2ff5c"
                                redirectUri:@"http://www.sharesdk.cn"];
    //添加QQ空间应用
    [ShareSDK connectQZoneWithAppKey:@"100371282"
                           appSecret:@"aed9b0303e3ed1e27bae87c33761161d"];
    //添加微信应用
    [ShareSDK connectWeChatWithAppId:@"wx6dd7a9b94f3dd72a"        //此参数为申请的微信AppID
                           wechatCls:[WXApi class]];
    
    //添加微信应用
    [ShareSDK connectWeChatTimelineWithAppId:@"wx6dd7a9b94f3dd72a"        //此参数为申请的微信AppID
                           wechatCls:[WXApi class]];
    
    //添加QQ应用
    [ShareSDK connectQQWithQZoneAppKey:@"100371282"                 //该参数填入申请的QQ AppId
                     qqApiInterfaceCls:[QQApiInterface class]
                       tencentOAuthCls:[TencentOAuth class]];
}

void SharedMultiPlatform::sharedAllPlatForm()
{
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"zhupo"  ofType:@"jpg"];
    
    //构造分享内容
    id<ISSContent> publishContent = [ShareSDK content:@"分享--内容"
                                       defaultContent:@"默认分享内容，没内容时显示"
                                                image:[ShareSDK imageWithPath:imagePath]
                                                title:@"ShareSDK"
                                                  url:@"http://www.sharesdk.cn"
                                          description:@"这是一条测试信息"
                                            mediaType:SSPublishContentMediaTypeText];

    id<ISSAuthOptions> authOptions = [ShareSDK authOptionsWithAutoAuth:NO
                                                         allowCallback:YES
                                                         authViewStyle:SSAuthViewStylePopup
                                                          viewDelegate:nil
                                               authManagerViewDelegate:nil];
    
    //在授权页面中添加关注官方微博
    [authOptions setFollowAccounts:[NSDictionary dictionaryWithObjectsAndKeys:
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeSinaWeibo),
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeTencentWeibo),
                                    nil]];
    
    //创建弹出菜单容器
    id<ISSContainer> container = [ShareSDK container];
    [container setIPadContainerWithView:nil arrowDirect:UIPopoverArrowDirectionUp];
    
    id<ISSShareOptions> shareOptions = [ShareSDK defaultShareOptionsWithTitle:@"XXXX分享快乐旅程"
                                                              oneKeyShareList:[NSArray defaultOneKeyShareList]
                                                               cameraButtonHidden:NO
                                                          mentionButtonHidden:NO
                                                            topicButtonHidden:NO
                                                               qqButtonHidden:NO
                                                        wxSessionButtonHidden:YES
                                                       wxTimelineButtonHidden:NO
                                                         showKeyboardOnAppear:NO
                                                            shareViewDelegate:nil
                                                          friendsViewDelegate:nil
                                                        picViewerViewDelegate:nil];
    
    [ShareSDK showShareViewWithType:ShareTypeAny
                          container:nil
                            content:publishContent
                      statusBarTips:YES
                        authOptions:authOptions
                       shareOptions:shareOptions
                             result:^(ShareType type, SSResponseState state, id<ISSPlatformShareInfo> statusInfo, id<ICMErrorInfo> error, BOOL end) {
                                 if (state == SSResponseStateSuccess) {
                                     NSLog(@"分享成功");
                                 }else if(state == SSResponseStateFail)
                                 {
                                     NSLog(@"分享失败,错误码:%d,错误描述:%@", [error errorCode], [error errorDescription]);
                                 }
                             }];
    
    return;
    
    [ShareSDK showShareActionSheet:nil
                         shareList:nil
                           content:publishContent
                     statusBarTips:YES
                       authOptions:authOptions
                      shareOptions: nil
                            result:^(ShareType type, SSResponseState state, id<ISSPlatformShareInfo> statusInfo, id<ICMErrorInfo> error, BOOL end) {
                                if (state == SSResponseStateSuccess)
                                {
                                    NSLog(@"分享成功");
                                }
                                else if (state == SSResponseStateFail)
                                {
                                    NSLog(@"分享失败,错误码:%d,错误描述:%@", [error errorCode], [error errorDescription]);
                                }
                            }];
    
}

void SharedMultiPlatform::registerAppWithAndroidPlatform()
{
    if (!_regist_android)
        _regist_android = true;
    else
        return;
    
}


void SharedMultiPlatform::cancelAuth(int type)
{
    [ShareSDK cancelAuthWithType:ShareTypeSinaWeibo];
    [ShareSDK cancelAuthWithType:ShareTypeTencentWeibo];
    [ShareSDK cancelAuthWithType:ShareTypeWeixiTimeline];
}

/* 添加到 AppDelegate 中的
 
 - (BOOL)application:(UIApplication *)application  handleOpenURL:(NSURL *)url
 {
 return [ShareSDK handleOpenURL:url
 wxDelegate:self];
 }
 
 - (BOOL)application:(UIApplication *)application
 openURL:(NSURL *)url
 sourceApplication:(NSString *)sourceApplication
 annotation:(id)annotation
 {
 
 return [ShareSDK handleOpenURL:url
 sourceApplication:sourceApplication
 annotation:annotation
 wxDelegate:self];
 }
 
 */



