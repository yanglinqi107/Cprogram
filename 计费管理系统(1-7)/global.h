#pragma once
#define CARDPATH "card.dat"			//卡信息文件
#define BILLINGPATH "billing.dat"	//计费信息文件
#define MONEYPATH "money.dat"		//充值退费记录文件

#define TIMELENGTH 20				//时间字符数组长度

#define SUCCESS 0					//操作成功
#define FINDCARD 1					//找到卡
#define NOFINDCARD 2				//没找到卡
#define NOMATCH 3					//卡号密码不匹配
#define ENOUGHMONEY 4				//卡余额不足
#define NOFARE 5					//未找到计费信息
#define USING 6						//正在上机
#define UNUSE 7						//未上机
#define INVALID 8					//已注销

#define NOSETTLEMENT 0				//上机未结算
#define YESSETTLEMENT 1				//上机已结算

#define UNIT 15						//最小收费单元
#define CHARGE 0.5					//每个计费单元收费

#define TRUE 0						//成功
#define FALSE 1						//失败

#define ADD 0						//充值
#define RETURN 1					//退费