#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"model.h"
#include"service.h"
#include"menu.h"
#include"tool.h"
#include"global.h"

void add(CardNode** ppCardNodeHead)
{
	CardNode* pCardNode = NULL;
	CardNode* pCardNodeTail=NULL;
	pCardNode = (CardNode*)malloc(sizeof(CardNode));
	
	char newCardName[50];
	char newCardPwd[20];
	struct tm* startTime;
	struct tm* endTime;
	
	printf("\n--------添加卡--------\n");
	printf("请输入卡号（1~18）：");
	gets(newCardName);
	if (strlen(newCardName)>18||newCardName[0]=='\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	pCardNodeTail= *ppCardNodeHead;
	while (pCardNodeTail != NULL)
	{
		if (strcmp(pCardNodeTail->data.aName, newCardName) == 0)
		{
			printf("卡已存在\n");
			return;
		}
		else
			pCardNodeTail = pCardNodeTail->next;
	}
	printf("请输入密码（1~8）：");
	gets(newCardPwd);
	if (strlen(newCardPwd) > 8|| newCardPwd[0]=='\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("请输入开卡金额:");
	scanf("%f", &(pCardNode->data.fTotalUse));
	while (getchar() != '\n');
	if (pCardNode->data.fTotalUse<=0)
	{
		printf("金额错误\n");
		return;
	}
	strcpy(pCardNode->data.aName,newCardName);
	strcpy(pCardNode->data.aPwd, newCardPwd);
	pCardNode->data.nStatus = UNUSE;
	pCardNode->data.nUseCount = 0;
	pCardNode->data.fBalance = pCardNode->data.fTotalUse;
	pCardNode->data.tStart= pCardNode->data.tEnd = pCardNode->data.tLast = time(NULL);
	startTime = localtime(&pCardNode->data.tStart);
	endTime = localtime(&pCardNode->data.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	pCardNode->data.tEnd = mktime(endTime);
	
	pCardNodeTail = *ppCardNodeHead;
	if(*ppCardNodeHead==NULL)
	{
		*ppCardNodeHead = pCardNode;
		pCardNodeTail = pCardNode;
		pCardNodeTail->next = NULL;
	}
	else
	{
		while (pCardNodeTail->next != NULL)
		{
			pCardNodeTail = pCardNodeTail->next;
		}
		pCardNodeTail->next = pCardNode;
		pCardNodeTail = pCardNodeTail->next;
		pCardNodeTail->next = NULL;
	}
	saveCard(&pCardNode->data, CARDPATH);
	printf("添加卡成功\n\n");
}

void displayCards(CardNode* pCardNodeHead)
{
	CardNode* pCardNode;
	pCardNode = pCardNodeHead;
	char aStartTime[20] = { 0 };
	while (pCardNode != NULL) {
		printf("\n卡号：\t%s\n",pCardNode->data.aName);
		printf("密码：\t%s\n", pCardNode->data.aPwd);
		if (pCardNode->data.nStatus == UNUSE)
			printf("状态：\t未上机\n");
		if (pCardNode->data.nStatus == USING)
			printf("状态：\t正在上机\n");
		if (pCardNode->data.nStatus == INVALID)
			printf("状态：\t已注销\n");
		timeToString(pCardNode->data.tStart, aStartTime);
		printf("开卡时间：\t%s\n", aStartTime);
		printf("金额：\t%.2f\n", pCardNode->data.fBalance);
		printf("使用次数：\t%d\n", pCardNode->data.nUseCount);
		printf("\n");
		pCardNode = pCardNode->next;
	};
}

void shangji(CardNode* pCardNodeHead, BillingNode** ppBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };
	
	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("\n------上机信息------\n\n");
	LogonInfo* pInfo = malloc(sizeof(LogonInfo));
	char aTime[20] = { 0 };
	int nResult = logon(aName, aPwd, pInfo, pCardNodeHead, ppBillingNodeHead);
	switch (nResult)
	{
		case NOFINDCARD:
		case NOMATCH:
		{
			printf("\n卡不存在，或卡信息错误，不能上机！\n\n");
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tLogon, aTime);
			printf("\n卡号：\t%s\n", aName);
			printf("余额：\t%.2f\n", pInfo->fBalance);
			printf("上机时间：\t%s\n", aTime);
			break;
		}
		case USING:
		{
			printf("\n该卡正在使用，不能重复上机！\n\n");
			break;
		}
		case INVALID:
		{
			printf("\n该卡已注销，不能上机！\n\n");
			break;
		}
		case ENOUGHMONEY:
		{
			printf("\n卡余额为0，不能上机！\n\n");
			break;
		}
		default:
			break;
	}
	free(pInfo);
}

void xiaji(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };
	
	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	SettleInfo* pInfo = malloc(sizeof(SettleInfo));
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	printf("\n------下机信息------\n\n");
	int nResult = settle(aName, aPwd, pInfo, pCardNodeHead, pBillingNodeHead);
	switch (nResult)
	{
	case NOFINDCARD:
	case NOMATCH:
	{
		printf("\n卡不存在，或信息不对，不能下机\n\n");
		break;
	}
	case SUCCESS:
	{
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);

		printf("\n卡号：\t%s\n", aName);
		printf("\n消费：\t%.2f\n", pInfo->fAmount);
		printf("\n余额：\t%.2f\n", pInfo->fBalance);
		printf("\n上机时间：\t%s\n", aStartTime);
		printf("\n下机时间：\t%s\n", aEndTime);
		break;
	}
	case UNUSE:
	{
		printf("\n该卡没有上机！\n\n");
		break;
	}
	case ENOUGHMONEY:
	{
		printf("\n卡余额不足，请先充值再上机！\n\n");
		break;
	}
	default:
		break;
	}
	free(pInfo);
}

void shangji2(CardNode* pCardNodeHead, BillingNode** ppBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入错误\n");
		return;
	}
	printf("\n------上机信息------\n\n");
	LogonInfo* pInfo = malloc(sizeof(LogonInfo));
	char aTime[20] = { 0 };
	int nResult = logon2(aName, aPwd, pInfo, pCardNodeHead, ppBillingNodeHead);
	if (nResult == TRUE)
	{
		timeToString(pInfo->tLogon, aTime);
		printf("\n卡号：\t%s\n", aName);
		printf("余额：\t%.2f\n", pInfo->fBalance);
		printf("上机时间：\t%s\n", aTime);
	}
	free(pInfo);
}

void xiaji2(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	SettleInfo* pInfo = malloc(sizeof(SettleInfo));
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	printf("\n------下机信息------\n\n");
	int nResult = settle2(aName, aPwd, pInfo, pCardNodeHead, pBillingNodeHead);
	if (nResult == TRUE)
	{

		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);

		printf("\n卡号：\t%s\n", aName);
		printf("\n消费：\t%.2f\n", pInfo->fAmount);
		printf("\n余额：\t%.2f\n", pInfo->fBalance);
		printf("\n上机时间：\t%s\n", aStartTime);
		printf("\n下机时间：\t%s\n", aEndTime);
	}
	free(pInfo);
}

void addMoney(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };
	float fmoney;

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%98s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("请输入充值金额:");
	scanf("%f", &fmoney);
	while (getchar() != '\n');
	if (fmoney <= 0)
	{
		printf("金额错误\n");
		return;
	}

	MoneyInfo pInfo;
	printf("\n-------充值信息如下-------\n\n");
	int nResult = AddMoney(aName, aPwd, fmoney, &pInfo, pCardNodeHead);
	if (nResult == FALSE)
		printf("充值失败！\n");
	if (nResult == TRUE)
	{
		printf("卡号:\t%s\n", aName);
		printf("充值金额:\t%.2f\n", fmoney);
		printf("余额:\t%.2f\n", pInfo.fBalance);
	}
}

void returnMoney(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}

	MoneyInfo pInfo;
	printf("\n-------退费信息如下-------\n\n");
	int nResult = ReturnMoney(aName, aPwd, &pInfo, pCardNodeHead);
	if (nResult == FALSE)
		printf("退费失败！\n");
	if (nResult == TRUE)
	{
		printf("卡号:\t%s\n", aName);
		printf("退费金额:\t%.2f\n", pInfo.fMoney);
		printf("余额:\t%.2f\n", pInfo.fBalance);
	}
}

void statNewCard(CardNode* pCardNodeHead)
{
	unsigned yearStart, monthStart, dayStart;
	unsigned yearEnd, monthEnd, dayEnd;

	printf("请输入统计的开始时间（年-月-日）：");
	(void)scanf("%u-%u-%u", &yearStart, &monthStart, &dayStart);
	if (IsLegal(yearStart, monthStart, dayStart) == 0)
	{
		printf("统计的开始时间不合法\n");
		return;
	}
	printf("请输入统计的结束时间（年-月-日）：");
	(void)scanf("%u-%u-%u", &yearEnd, &monthEnd, &dayEnd);
	if (IsLegal(yearEnd, monthEnd, dayEnd) == 0)
	{
		printf("统计的结束时间不合法\n");
		return;
	}

	char timeStart[TIMELENGTH] = { 0 }, timeEnd[TIMELENGTH] = { 0 };

	sprintf(timeStart, "%d-%d-%d 0:0", yearStart, monthStart, dayStart);
	sprintf(timeEnd, "%d-%d-%d 23:59", yearEnd, monthEnd, dayEnd);

	time_t sTime, eTime;
	sTime = stringToTime(timeStart);
	eTime = stringToTime(timeEnd);

	if (eTime <= sTime)
	{
		printf("统计时间不合法\n");
		return;
	}

	FILE* fp = NULL;
	if ((fp = fopen("card_tj.txt", "w")) == NULL)
		return;

	*(strchr(timeStart, ' ')) = '\0';
	*(strchr(timeEnd, ' ')) = '\0';

	fprintf(fp, "%s", "\t\t\t开卡数统计报表\n");
	fprintf(fp, "\t\t%s---%s\n", timeStart, timeEnd);
	fprintf(fp, "%s", "-----------------------------------------\n");
	fprintf(fp,"%s","卡号   \t开卡时间   \t\t\t卡余额\n");

	CardNode* pCardNode = pCardNodeHead;
	int cardCnt = 0;

	while (pCardNode != NULL)
	{
		if (pCardNode->data.tStart >= sTime && pCardNode->data.tStart <= eTime)
		{
			char timeTmp[TIMELENGTH] = { 0 };
			timeToString(pCardNode->data.tStart, timeTmp);
			fprintf(fp, "%s\t%s\t%.2f\n", pCardNode->data.aName, timeTmp, pCardNode->data.fBalance);
			cardCnt++;
		}
		pCardNode = pCardNode->next;
	}
	fprintf(fp, "%s", "-----------------------------------------\n");
	fprintf(fp, "\t\t开卡总数：%d\n", cardCnt);

	fclose(fp);
	printf("\n共开了%d张新卡，报表已生成！\n", cardCnt);

	return;
}

void logout(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	printf("输入密码（1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}

	int nResult = Logout(aName, aPwd, pCardNodeHead);
	if (nResult == FALSE)
		printf("注销失败！\n");
	if (nResult == TRUE)
		printf("注销成功！\n");
}

void query(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };

	printf("请输入卡号（1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("输入的数据长度错误\n");
		return;
	}
	queryCard(aName, pCardNodeHead);
}