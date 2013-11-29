//
//  platform91Configure.h
//  CrazyGeography
//
//  Created by xiangshouyong on 13-11-25.
//
//

#import <Foundation/Foundation.h>

@interface platform91Configure : NSObject
{
    NSMutableArray *_recordArr;
}

+ (platform91Configure *)instance;

- (void)willEnterForeground;

//注销登录，传入0表示注销； 传入1表示注销并清除自动登录。
- (void)platform91Logout:(int) type;

- (void)buyCommodities:(NSString *) productName productId:(NSString *) proId price:(float) price originPrice:(float) oriPrice count:(int) count;

- (void)EnterVirtualShop;               //进入虚拟商店
- (void)getVirtualCategoryList;         //获取虚拟商品类别信息
- (void)getVirtualCommodityList;        //获取虚拟商品列表
- (void)buyCommoditiesByFormVir:(NSString *) strProductId productCount:(NSInteger) nCount;

- (void)shared;

- (void)show91ToolBar:(BOOL) show;

- (void)switchAccount;          //注销

- (void)enterAccountManage;     //进入账户管理界面

/**
 *提交排行榜分数
 *排行榜id
 *分值，不能是负数
 *如果不想自定义文本传nil
 */

- (void)submitScoreTo91:(unsigned int) nLeaderBoardId nCurrentScore:(unsigned int )nCurrentScore displayText:(NSString *)displayText;
- (void)openScoreBoard:(int) nLeaderBoardId;        //打开排行榜

/**
 * 进入成就列表界面，可查看所有成就信息及解锁状态。
 */
- (void)openAchievement:(int ) achievementId;
- (void)unLockAchievement:(int) achieId currValuePercent:(int) percent displayText:(NSString *)displayText;


@end
