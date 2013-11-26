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
    
    
    [ShareSDK registerApp:@"d2883c13136"];     //参数为ShareSDK官网中添加应用后得到的AppKey
    
//    tencen  App Key:801443052 App Secret:3ee6b8281440e9600dc7fb8c973744cf
//    sina  App Key：382748327   App Secret：83ad60eaebe18275adf7518f029a54aa

    
    //添加新浪微博应用
    [ShareSDK connectSinaWeiboWithAppKey:@"382748327"
                               appSecret:@"83ad60eaebe18275adf7518f029a54aa"
                             redirectUri:@"http://www.weibo.com"];
    //分享腾讯微博
    [ShareSDK connectTencentWeiboWithAppKey:@"801443052"
                                  appSecret:@"3ee6b8281440e9600dc7fb8c973744cf"
                                redirectUri:@"http://dev.t.qq.com/apps"];
    
    //添加QQ空间应用 我自己申请的
    [ShareSDK connectQZoneWithAppKey:@"801443052"
                           appSecret:@"4e240525f2dffdb0cc6c859d381a7691"];
    
//    [ShareSDK connectQZoneWithAppKey:@"100371282"
//                           appSecret:@"aed9b0303e3ed1e27bae87c33761161d"];
    
    //添加微信应用
    [ShareSDK connectWeChatWithAppId:@"wx7f80c2190aed576e"        //此参数为申请的微信AppID
                           wechatCls:[WXApi class]];
    
    //添加微信朋友圈应用
    [ShareSDK connectWeChatTimelineWithAppId:@"wx7f80c2190aed576e"        //此参数为申请的微信AppID
                           wechatCls:[WXApi class]];
    
    //添加QQ应用
    [ShareSDK connectQQWithQZoneAppKey:@"801443052"                 //该参数填入申请的QQ AppId  URL Scheme QQ2fc50cec
                     qqApiInterfaceCls:[QQApiInterface class]
                       tencentOAuthCls:[TencentOAuth class]];
}

void SharedMultiPlatform::sharedAllPlatForm()
{
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"appIconDefault_0"  ofType:@"png"];
    
    //构造分享内容
    id<ISSContent> publishContent = [ShareSDK content:@"分享--内容"
                                       defaultContent:@"默认分享内容，没内容时显示"
                                                image:[ShareSDK imageWithPath:imagePath]
                                                title:@"知乎地标分享"
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
    
    id<ISSShareOptions> shareOptions = [ShareSDK defaultShareOptionsWithTitle:@"分了吧"
                                                              oneKeyShareList:[NSArray defaultOneKeyShareList]
                                                               cameraButtonHidden:NO
                                                          mentionButtonHidden:NO
                                                            topicButtonHidden:NO
                                                               qqButtonHidden:NO
                                                        wxSessionButtonHidden:NO
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



