#pragma once
#include<time.h>
typedef struct Card {
	char aName[19];		//卡号
	char aPwd[9];		//密码
	int  nStatus;		//卡状态（UNUSE-未使用，USING-正在使用，INVALID-已注销）
	time_t tStart;		//开卡时间
	time_t tEnd;		//卡的截止时间
	float  fTotalUse;	//开卡金额
	time_t tLast;		//最后使用时间
	int nUseCount;		//使用次数
	float fBalance;		//余额
	int nDel;			//删除标识（0-未删除，1-删除）
}Card;
typedef struct CardNode {
	Card data;
	struct CardNode* next;
}CardNode;

typedef struct Billing	//计费信息结构体
{
	char aCardName[19];	//卡号
	time_t tStart;		//上机时间
	time_t tEnd;		//下机时间
	float fAmount;		//消费金额
	int nStatus;		//消费状态：0未结算，1已结算
	int nDel;			//删除标记：0未删除，1已删除
}Billing;
typedef struct BillingNode
{
	Billing data;
	struct BillingNode* next;
}BillingNode;

typedef struct LogonInfo	//上机信息结构体
{
	char aCardName[19];		//卡号
	time_t tLogon;			//上机时间
	float fBalance;			//上机时卡余额
}LogonInfo;

typedef struct SettleInfo	//下机信息结构体
{
	char aCardName[19];		//卡号
	time_t tStart;			//上机时间
	time_t tEnd;			//下机时间
	float fAmount;			//消费金额
	float fBalance;			//余额
}SettleInfo;

typedef struct Money		
{
	char aCardName[19];		//卡号
	time_t tTime;			//充值退费时间
	int nStatus;			//状态：0-充值，1-退费
	float fMoney;			//充值退费金额
	int nDel;				//删除标识：0-未删除，1-已删除
}Money;

typedef struct MoneyInfo
{
	char aCardName[19];		//卡号
	float fMoney;			//充值退费金额
	float fBalance;			//余额
}MoneyInfo;