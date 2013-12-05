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

//虚拟商店
#import <NdComPlatform/NdComPlatform+VirtualGoods.h>
#import <NdComPlatform/NdComPlatformAPIResponse+VirtualGoods.h>

//本地游戏数据处理
#import "GlobalUserDefault.h"


#define DEBUG_RELEASE_91  1
#define BUY_RECORD_KEY    @"BUY_RECORD_KEY"
#define BUY_CooOrderSerial_HEAD  @"ZHIHUDIBIAOXSYLY"

static platform91Configure *_platform91;

@interface platform91Configure ()

- (void)addRecord:(NdBuyInfo *) buyInfo;
- (void)removeRecord:(NSString *)record;
- (NSArray *)getUnCheckedRecord;
- (void)dealWithBuySuccess:(NSString *) cooOrderSerial;
- (void)dealWithBuyFailure:(NSString *) cooOrderSerial;


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
//    cfg.appid =100010;
//    cfg.appKey =@"C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
    //我自己的游戏
    cfg.appid =110237;
    cfg.appKey =@"1ec5e323e5d561ea0553ba2b76df5fed304ddff14bb5c6e2";
    //versionCheckLevel的设置详见上面的说明
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
    //orientation的设置详见上面的说明(这里以设置竖屏为例)
    cfg.orientation = UIInterfaceOrientationPortrait;
    
    [[NdComPlatform defaultPlatform] NdSetScreenOrientation:UIInterfaceOrientationPortrait];
    
    [[NdComPlatform defaultPlatform] NdInit:cfg];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
    
    if (DEBUG_RELEASE_91) [[NdComPlatform defaultPlatform] NdSetDebugMode:0];
    
    [[NdComPlatform defaultPlatform] NdSetDebugMode:0];
    
    //离开91界面监听消息 包括退出虚拟商店
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
    for (NSDictionary *infoDic in recordArray)
    {
        NSString *cooOrderSerial = [infoDic objectForKey:@"productId"];
        NSLog(@"cooOrderSerial :%@",cooOrderSerial);
        [[NdComPlatform defaultPlatform] NdCheckPaySuccess : cooOrderSerial delegate : self];
        //回调方法是 checkPaySuccessDidFinish
    }
    
    //获取我的详细信息
    [[NdComPlatform defaultPlatform] NdGetMyInfoDetail:self];
    
    //监听虚拟商店的相关消息。
    //1.每一次的购买结果
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(NdBuyCommodityResult:)
                                                 name:kNdCPBuyResultNotification
                                               object:nil];
    
    
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

- (void)buyCommodities:(NSString *)productName productId:(NSString *)proId price:(float)price originPrice:(float)oriPrice count:(int)count
{
    NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
    //订单号必须唯一！
    NSDate *date = [[NSDate alloc] init];
    NSTimeInterval timeinterval = [date timeIntervalSince1970];
    NSString *time_str = [NSString stringWithFormat:@"%@%f",BUY_CooOrderSerial_HEAD,timeinterval * 1000000];
    time_str = [time_str substringToIndex:32];
//    NSLog(@" 单号 %@  ",time_str);
    [date release];
    /*
     1385711941.252368
     1385712020336631.000000
     138571274246195
     ZHIHUDIBIAOXYLY1385712954445276
     ZHIHUDIBIAOXYLY1385713044236889.
     ZHIHUDIBIAOXSYLY1385713149793058
     */
    buyInfo.cooOrderSerial = time_str;
    //你的产品id
    buyInfo.productId = proId;
    buyInfo.productName = productName;
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
        [self addRecord:buyInfo];
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
        int payPrice = (int)buyInfo.productPrice;
        int add_gold = 0;
        switch (payPrice) {
            case kBuyGold_6RMB:
                add_gold = kAddGolg_6RMB;
                break;
            case kBuyGold_12RMB:
                add_gold = kAddGold_12RMB;
                break;
            case kBuyGold_30RMB:
                add_gold = kAddGold_30RMB;
                break;
            case kBuyGold_68RMB:
                add_gold = kAddGold_68RMB;
                break;
            case kBuyGold_128RMB:
                add_gold = kAddGold_128RMB;
                break;
            default:
                break;
        }
        
        GlobalUserDefault::instance()->increaseGameGold(add_gold);
    }
    //本次购买的请求参数
    str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d, cooOrderSerial = %@>",
           buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
    NSLog(@"NdUiPayResult: %@", str);
    [self removeRecord:buyInfo.cooOrderSerial];
}

#pragma mark - 虚拟商店购买操作

- (void)EnterVirtualShop
{
    //进入虚拟商店，显示所有类别，所有计费类型的商品
    int nFeeType = ND_VG_FEE_TYPE_POSSESS | ND_VG_FEE_TYPE_SUBSCRIBE | ND_VG_FEE_TYPE_CONSUME;
    [[NdComPlatform defaultPlatform] NdEnterVirtualShop:nil feeType:nFeeType];
}

- (void)getVirtualCategoryList
{
    //获取虚拟商品类别信息
    [[NdComPlatform defaultPlatform] NdGetCategoryList: self];
}

//回去虚拟商品类别信息 需要实现的回调方法
- (void)getCategoryListDidFinish:(int)error records:(NSArray *)records
{
    if (error < 0) {
        //TODO: 下载类别信息失败
    }
    else {
        //TODO: 类别信息处理
        for (NdVGCategory* category in records) {
            //...
            NSLog(@"<-----上平类别 Id %@   名字 %@ ----->",category.strCateId,category.strCateName);
            
        }
    }
}

- (void)getVirtualCommodityList
{
    //分页获取虚拟商品信息，不指定类别，计费类型
    NdPagination* pagination = [[NdPagination new] autorelease];
    pagination.pageSize = 5; //5的倍数，不要超过50
    pagination.pageIndex= 1; //获取页的索引值，从1开始，总共的页数可以通过返回接口里result.totalCount字段计算出来，第一次请求用1
    [[NdComPlatform defaultPlatform] NdGetCommodityList:nil feeType:7 pagination:pagination packageId:nil delegate: self];
}

//获取虚拟商品信息 需要实现的回调方法
- (void)getCommodityListDidFinish:(int)error cateId:(NSString*)cateId
                          feeType:(int)feeType packageId:(NSString *)packageId result:(NdBasePageList*)result
{
    if (error < 0) {
        NSLog(@"TODO: 下载商品信息列表失败 %d",error);
    }
    else {
        
        //TODO: 返回某一页的信息列表
        //result.pagination; 当前返回的页索引信息
        //计算出总的页数，可以用来处理下一页的请求。如果没有商品时，nPageCount为0，可能需要特殊处理。
        int nPageCount = (result.totalCount + result.pagination.pageSize - 1) / result.pagination.pageSize;
        for (NdVGCommodityInfo* info in result.records) {
            //商品信息，...
            
            NSLog(@"商品 id %@ . 商品名字 %@ 。 npage %d",info.strProductId,info.strProductName,nPageCount);
            
        }
    }
}

- (void)NdBuyCommodityResult:(NSNotification*)notify
{
    NSDictionary *dic = [notify userInfo];
    BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
    NSString* str = bSuccess ? @"购买成功" : @"购买失败";
    if (!bSuccess) {
        //TODO: 购买失败处理
        NSString* strError = nil;
        int nErrorCode = [[dic objectForKey:@"error"] intValue];
        switch (nErrorCode) {
                // {{购买虚拟商品(91豆/游戏币)必须处理的错误码
            case ND_COM_PLATFORM_ERROR_USER_CANCEL:
                strError = @"用户取消操作";
                break;
            case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
                strError = @"网络连接错误";
                break;
            case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                strError = @"服务端处理失败";
                break;
            case ND_COM_PLATFORM_ERROR_VG_MONEY_TYPE_FAILED:
                strError = @"查询虚拟商品币种失败";
                break;
                // }}
                // {{ 1.购买虚拟商品（91豆）必须处理的错误码
            case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED:
                //!!!: 异步支付，用户进入充值界面了
                strError = @"支付订单已提交";
                break;
            case ND_COM_PLATFORM_ERROR_PARAM:
                //可能是虚拟商品价格为0，或者总额超过最大值
                strError = @"购买的虚拟商品91豆价格总额不合法";
                break;
            case ND_COM_PLATFORM_ERROR_VG_ORDER_FAILED:
                strError = @"获取虚拟商品订单号失败";
                break;
                // }}
                // {{ 2购买虚拟商品（游戏币）必须处理的错误码
            case ND_COM_PLATFORM_ERROR_VG_BACK_FROM_RECHARGE:
                strError = @"有进入虚拟币直充界面";
                break;
            case ND_COM_PLATFORM_ERROR_PAY_FAILED:
                strError = @"购买虚拟商品失败";
                break;
                // }}
            default:
                strError = @"购买过程发生错误";
                break;
        }
        str = [str stringByAppendingFormat:@"\n%@", strError];
    }
    else {
        //TODO: 购买成功处理
    }
    // 如果购买失败，可能无法得到cooOrderSerial, productPrice等字段值
    NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
    str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d, cooOrderSerial = %@>",
           buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
    // 如果购买虚拟商品失败，可以从vgErrorInfo获取具体失败详情，参照NdVGErrorInfo定义
    NdVGErrorInfo* vgErrInfo = (NdVGErrorInfo*)[dic objectForKey:@"vgErrorInfo"];
    if (vgErrInfo) {
        str = [str stringByAppendingFormat:@"\n\n%@", vgErrInfo.strErrDesc];
    }
    NSLog(@" 打印: NdBuyCommodityResult: %@", str);
}

- (void)buyCommoditiesByFormVir:(NSString *)strProductId productCount:(NSInteger) nCount
{
    //购买虚拟商品
    NdVGOrderRequest* orderRqst = [NdVGOrderRequest orderRequestWithProductId : strProductId
                                                                 productCount : nCount payDescription:nil];
    //orderRqst.vgCommodityInfo = vgCommodityInfo; //(建议)如果已经获取该商品信息，传入该值
    int res = [[NdComPlatform defaultPlatform] NdBuyCommodity:orderRqst];
    if (res < 0) {
        switch (res) {
            case ND_COM_PLATFORM_ERROR_NOT_LOGINED:
                NSLog(@"未登录");
                break;
            case ND_COM_PLATFORM_ERROR_PARAM:
                
                NSLog(@"参数错误");
                break;
            default:
                NSLog(@"%@",[NSString stringWithFormat:@"购买失败error = %d", res]);
                break;
        }
    }else
    {
        NSLog(@" 虚拟商品可以购买 ");
    }
}

#pragma mark - 分享
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
                [self dealWithBuySuccess:cooOrderSerial];
    }
    else
    {
        //说明该笔订单购买失败
                [self dealWithBuyFailure:cooOrderSerial];
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
- (void)addRecord:(NdBuyInfo *)buyInfo
{
    NSMutableDictionary *buyInfoDic = [[NSMutableDictionary alloc] init];
    
    [buyInfoDic setValue:buyInfo.productId forKey:@"productId"];
    [buyInfoDic setValue:buyInfo.productName forKey:@"productName"];
    [buyInfoDic setValue:[NSNumber numberWithFloat: buyInfo.productPrice] forKey:@"productPrice"];
    [buyInfoDic setValue:[NSNumber numberWithFloat: buyInfo.productOrignalPrice ] forKey:@"productOrignalPrice"];
    [buyInfoDic setValue:[NSNumber numberWithUnsignedInt: buyInfo.productCount] forKey:@"productCount"];
    
    [_recordArr addObject:buyInfoDic];
    [[NSUserDefaults standardUserDefaults] setObject:_recordArr forKey:BUY_RECORD_KEY];
    [buyInfoDic release];
}

- (void)removeRecord:(NSString *)record
{
    for (int i = 0; i < _recordArr.count; i++) {
        NSDictionary *buyInfo = (NSDictionary *)[_recordArr objectAtIndex:i];
        
        if ( [((NSString *)[buyInfo objectForKey:@"productId"]) isEqualToString:record])
        {
            [_recordArr removeObjectAtIndex:i];
            NSLog(@"移除购买了的东西 %@",((NSString *)[buyInfo objectForKey:@"productId"]));
        }
    }
    
    [[NSUserDefaults standardUserDefaults] setValue:_recordArr forKey:BUY_RECORD_KEY];
}

- (void)dealWithBuySuccess:(NSString *)cooOrderSerial
{
    NSLog(@"您最近一次充值已经到账 %@",cooOrderSerial);
}

- (void)dealWithBuyFailure:(NSString *)cooOrderSerial
{
    for (int i = 0; i < _recordArr.count; i++) {
        NSDictionary *buyInfo = (NSDictionary *)[_recordArr objectAtIndex:i];
        if ([((NSString *)[buyInfo objectForKey:@"productId"]) isEqualToString:cooOrderSerial])
        {
            [self buyCommodities:((NSString *)[buyInfo objectForKey:@"productName"])
                       productId:((NSString *)[buyInfo objectForKey:@"productId"])
                           price:[[buyInfo objectForKey:@"productPrice"] floatValue]
                     originPrice:[[buyInfo objectForKey:@"productOrignalPrice"] floatValue]
                           count:[[buyInfo objectForKey:@"productCount"] unsignedIntValue]];
            
            NSLog(@"再次请求购买上次未能成功的商品 :%@",((NSString *)[buyInfo objectForKey:@"productName"]));
        }
    }
   
}

- (NSArray *)getUnCheckedRecord
{
    return [[NSUserDefaults standardUserDefaults] arrayForKey:BUY_RECORD_KEY];
}

- (void)dealloc
{
    [_recordArr release];
    /*
     [[NSNotificationCenter defaultCenter] removeObserver:self
     name:kNdCPPauseDidExitNotification object:nil];
     [[NSNotificationCenter defaultCenter] removeObserver:self
     name:kNdCPLeavePlatformNotification object:nil];
     [[NSNotificationCenter defaultCenter] removeObserver:self
     name:kNdCPLoginNotification object:nil];
     [[NSNotificationCenter defaultCenter] removeObserver:self
     name:kNdCPBuyResultNotification object:nil];
     */
    [[NSNotificationCenter defaultCenter] removeObserver : self];
    
    [super dealloc];
}

@end
