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

- (void)buyCommodities;

- (void)shared;

- (void)show91ToolBar:(BOOL) show;

- (void)switchAccount;

- (void)enterAccountManage;


@end
