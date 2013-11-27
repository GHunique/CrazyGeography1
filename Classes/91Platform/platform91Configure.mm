//
//  platform91Configure.m
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-25.
//
//

#import "platform91Configure.h"

#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>

//要使用同步购买功能，首先请包含以下的头文件：
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NdComPlatformError.h>

//本地游戏数据处理
#import "GlobalUserDefault.h"


#define DEBUG_RELEASE_91 1
#define BUY_RECORD_KEY   @"BUY_RECORD_KEY"

static platform91Configure *_platform91;

@interface platform91Configure ()

- (void)addRecord:(NSString *) record;
- (void)removeRecord:(NSString *)record;
- (NSArray *)getUnCheckedRecord;

@end

@implementation platform91Configure

+ (platform91Configure *)instance
{
    if (!_platform91) {
        _platform91 = [[platform91Configure alloc] init];
        
    }
    
    return _platform91;
}

- (id)init
{
    if (![super init])
        return nil;
    
    //完成您必要的初始化工作，例如设置您的rootViewController
    //初始化平台
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
    cfg.appid =100010;
    cfg.appKey =@"C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
    //versionCheckLevel的设置详见上面的说明
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
    //orientation的设置详见上面的说明(这里以设置竖屏为例)
      cfg.orientation = UIInterfaceOrientationPortrait;
    
    [[NdComPlatform defaultPlatform] NdSetScreenOrientation:UIInterfaceOrientationPortrait];
    
    [[NdComPlatform defaultPlatform] NdInit:cfg];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
    
    if (DEBUG_RELEASE_91) [[NdComPlatform defaultPlatform] NdSetDebugMode:0];
    
    [[NdComPlatform defaultPlatform] NdSetDebugMode:0];
    
    //离开91界面监听消息
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(SNSLeaveComplatformUI:)
                                                 name:(NSString *)kNdCPLeavePlatformNotification
                                               object:nil];
    //注册登陆监听消息
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginResult:)
                                                 name:(NSString *)kNdCPLoginNotification
                                               object:nil];
    //注册暂停关闭暂停页面
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSPauseExit:) name:(NSString *)kNdCPPauseDidExitNotification object:nil];
    
    //为了监听购买的结果，您需要在您的初始化函数（例如-viewDidLoad或者-init）中添加以下代码：
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(NdUniPayResult:)
                                                 name:kNdCPBuyResultNotification
                                               object:nil];
    
    _recordArr = [[NSMutableArray alloc] init];
    
    //程序启动时检查未核对结果的交易在合适的地方添加类似以下的检查代码
    NSArray *recordArray = [self getUnCheckedRecord];
    for (NSString *cooOrderSerial in recordArray) {
        [[NdComPlatform defaultPlatform] NdCheckPaySuccess : cooOrderSerial delegate : self];
    }
    
    //获取我的详细信息
    [[NdComPlatform defaultPlatform] NdGetMyInfoDetail:self];
    
    return self;
}

//---91platform

- (void)SNSInitResult:(NSNotification *)notify
{
    [[NdComPlatform defaultPlatform] NdLogin:0];
//    [[NdComPlatform defaultPlatform] NdLoginEx:0];
   
}

- (void)willEnterForeground
{
    [[NdComPlatform defaultPlatform] NdPause];
}



- (void)platform91Logout:(int)type
{
    [[NdComPlatform defaultPlatform] NdLogout:type];
}

- (void)buyCommodities:(NSString *)orderSerial productId:(NSString *)proId price:(float)price originPrice:(float)oriPrice count:(int)count
{
    NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
    //订单号必须唯一！
    buyInfo.cooOrderSerial = @"120F6CD4018C4D9A8E852AF7D2F32666";
    //你的产品id
    buyInfo.productId = @"com.91.product.apple";
    buyInfo.productName = @"苹果";
    buyInfo.productPrice = price; //价格不能为0！
    buyInfo.productOrignalPrice = oriPrice; //原价不能为0！
    buyInfo.productCount = count;
    //发起请求并检查返回值。注意！该返回值并不是交易结果！
    int res = [[NdComPlatform defaultPlatform] NdUniPay:buyInfo];
    if (res < 0)
    {
        //输入参数有错！无法提交购买请求
    }else
    {
        //记录下该笔交易
        [self addRecord:buyInfo.cooOrderSerial];
    }
}

//购买完成后，您的监听函数会被回调。在你的监听函数中，可以获取到本次购买的订单序列号，购买结果以及错误信息。示例代码如下：
- (void)NdUniPayResult:(NSNotification*)notify
{
    NSDictionary *dic = [notify userInfo];
    BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
    NSString* str = bSuccess ? @"购买成功" : @"购买失败";
    
    NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
    
    if (!bSuccess) {
        //TODO: 购买失败处理
        NSString* strError = nil;
        int nErrorCode = [[dic objectForKey:@"error"] intValue];
        switch (nErrorCode) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL:
                strError = @"用户取消操作";
                break;
            case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
                strError = @"网络连接错误";
                break;
            case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                strError = @"服务端处理失败";
                break;
            default:
                strError = @"购买过程发生错误";
                break;
        }
        str = [str stringByAppendingFormat:@"\n%@", strError];
    }
    else {
        //TODO: 购买成功处理
        GlobalUserDefault::instance()->increaseGameGold(buyInfo.productPrice * buyInfo.productCount);
    }
    //本次购买的请求参数
    GlobalUserDefault::instance()->increaseGameGold(buyInfo.productPrice * buyInfo.productCount); // ---- 删除
    str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d, cooOrderSerial = %@>",
           buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
    NSLog(@"NdUiPayResult: %@", str);
    [self removeRecord:buyInfo.cooOrderSerial];
}

- (void)shared
{
    NSDate* date = [NSDate date];
    NSString* str = [NSString stringWithFormat:@"我回来了! --%@", [date description]];
    [[NdComPlatform defaultPlatform] NdShareToThirdPlatform: str
                                                 imageInfo : [NdImageInfo imageInfoWithScreenShot] ] ;
}

- (void)show91ToolBar:(BOOL)show
{
    if (show) {
        [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtBottomRight];
    }else
    {
        [[NdComPlatform defaultPlatform] NdHideToolBar];
    }
}

- (void)switchAccount
{
    [[NdComPlatform defaultPlatform] NdSwitchAccount];
}

- (void)enterAccountManage
{
    [[NdComPlatform defaultPlatform] NdEnterAccountManage];
}

- (void)submitScoreTo91:(unsigned int)nLeaderBoardId nCurrentScore:(unsigned int)nCurrentScore displayText:(NSString *)displayText
{
    [[NdComPlatform defaultPlatform] NdSubmitScore:nLeaderBoardId
                                             score:nCurrentScore displayText:displayText delegate:self];
}

//target 需要实现的回调方法
- (void)submitScoreDidFinish:(int)error
{
    NSString* str = nil;
    if (error >= ND_COM_PLATFORM_NO_ERROR) {
        str = @"提交成功";
        NSLog(@" 分享排行榜情况 %@ ",str);
    }
    else if (ND_COM_PLATFORM_ERROR_LEADERBOARD_NOT_EXIST == error) {
        str = @"排行榜不存在";
        NSLog(@" 分享排行榜情况 %@ ",str);
    }
    else if (ND_COM_PLATFORM_ERROR_NOT_LOGINED == error) {
        str = @"离线提交";
        NSLog(@" 分享排行榜情况 %@ ",str);
    }
    else {
        str = @"提交失败";
        NSLog(@" 分享排行榜情况 %@ ",str);
    }
    //TODO: 提交结果提示
}

- (void)openScoreBoard:(int)nLeaderBoardId
{
    [[NdComPlatform defaultPlatform] NdOpenLeaderBoard:nLeaderBoardId flag:0];
}

- (void)openAchievement:(int)achievementId
{
    //打开成就榜列表界面
    [[NdComPlatform defaultPlatform] NdOpenAchievement:0];
}

- (void)unLockAchievement:(int)achieId currValuePercent:(int)percent displayText:(NSString *)displayText
{
    [[NdComPlatform defaultPlatform] NdUnLockAchievement: achieId
                                                   value: percent displayText: displayText delegate: self];
}

//unLockAchievement 需要实现的回调方法
- (void)unlockAchievementDidFinish:(int)error
{
    NSString* str = nil;
    if (error >= 0) {
        str = @"提交成功";
    }
    else if (ND_COM_PLATFORM_ERROR_ACHIEVEMENT_NOT_EXIST == error) {
        str = @"不存在该成就";
    }
    else {
        str = @"提交失败";
    }
    
     NSLog(@" 提交成就情况 %@ ",str);
    //TODO: 结果提示
}

- (void)checkPaySuccessDidFinish:(int)error
                  cooOrderSerial:(NSString*)cooOrderSerial
                        bSuccess:(BOOL)bSuccess
{
    if (bSuccess)
    {
        //说明该笔订单购买成功
//        [self dealWithBuySuccess:cooOrderSerial];
    }
    else
    {
        //说明该笔订单购买失败
//        [self dealWithBuyFailure:cooOrderSerial];
    }
    
//    [self removeRecord:cooOrderSerial];
}

#pragma mark - notification methods

//离开91界面监听消息
- (void)SNSLeaveComplatformUI:(NSNotification *)notify
{
    
}

//登陆情况
- (void)SNSLoginResult:(NSNotification *)notify
{
    NSDictionary *dict = [notify userInfo];
    BOOL success = [[dict objectForKey:@"result"] boolValue];
    NdGuestAccountStatus* guestStatus = (NdGuestAccountStatus*)[dict objectForKey:@"NdGuestAccountStatus"];
    //TODO:登录成功后处理
    if([[NdComPlatform defaultPlatform] isLogined] && success) {
        //也可以通过[[NdComPlatform defaultPlatform] getCurrentLoginState]判断是否游客登录状态
        if (guestStatus) {
            if ([guestStatus isGuestLogined]) {
                NSLog(@" //游客账号登录成功;");
                
            }
            else if ([guestStatus isGuestRegistered]) {
                NSLog(@" //游客成功注册为普通账号");
            }
        }
        else {
            NSLog(@" //普通账号登录成功！");
        }
    }
    //登录失败处理和相应提示
    else {
        int error = [[dict objectForKey:@"error"] intValue];
        NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
        switch (error) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
                if (([[NdComPlatform defaultPlatform] getCurrentLoginState] == ND_LOGIN_STATE_GUEST_LOGIN)) {
                    strTip = @"当前仍处于游客登录状态";
                }
                else {
                    strTip = @"用户未登录";
                }
                break;
            case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
                strTip = @"登录失败, 请检查appId/appKey";
                break;
            case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
                strTip = @"登录失败, 无效的应用ID";
                break;
            case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
                strTip = @"有关联的91账号，不能以游客方式登录";
                break;
            default:
                //其他类型的错误提示
                break;
        }
    }
    
    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtBottomRight];
    
}


//在监听函数中实现你所需要的逻辑
- (void)SNSPauseExit:(NSNotification *)notify
{
    //do what you want
}

//NdGetMyInfoDetail 和NdGetUserInfoDetail 的回调
- (void)getUserInfoDidFinish:(int)error userInfo:(NdUserInfo *)userInfo
{
    if (error < 0 ) {
        //TODO: 下载用户信息失败
    }
    else {
        //userInfo中包含昵称，生日，地区，心情等详细数据
    }
}





#pragma mark -  ()
- (void)addRecord:(NSString *)record
{
    [_recordArr addObject:record];
    [[NSUserDefaults standardUserDefaults] setValue:_recordArr forKey:BUY_RECORD_KEY];
}

- (void)removeRecord:(NSString *)record
{
    for (int i = 0; i < _recordArr.count; i++) {
        NSString *cooOrderSerialStr = (NSString *)[_recordArr objectAtIndex:i];
        if ([cooOrderSerialStr isEqualToString:record]) {
            [_recordArr removeObjectAtIndex:i];
            NSLog(@"移除购买了的东西 %@",cooOrderSerialStr);
        }
    }
    
    [[NSUserDefaults standardUserDefaults] setValue:_recordArr forKey:BUY_RECORD_KEY];
}

- (NSArray *)getUnCheckedRecord
{
    return [[NSUserDefaults standardUserDefaults] arrayForKey:BUY_RECORD_KEY];
}

- (void)dealloc
{
    [_recordArr release];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kNdCPPauseDidExitNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kNdCPLeavePlatformNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kNdCPLoginNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kNdCPBuyResultNotification object:nil];
    [super dealloc];
}

@end
