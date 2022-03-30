#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<string.h>
#include"model.h"
#include"tool.h"

void add(Card cards[], int* pIndex)
{
		Card card;
		char newCardName[50] = {0};
		char newCardPwd[20] = {0};
		struct tm* startTime;
		struct tm* endTime;
		printf("\n--------添加卡--------\n");
		printf("请输入卡号（1~18）：");
		gets(newCardName);
		if (strlen(newCardName) > 18|| newCardName[0] =='\0') {
			printf("输入错误\n");
			return;
		}
		printf("请输入密码（1~8）：");
		gets(newCardPwd);
		if (strlen(newCardPwd) > 8 || newCardPwd[0] =='\0') {
			printf("输入错误\n");
			return;
		}
		printf("请输入开卡金额(20~1000):");
		scanf_s("%f", &card.fTotalUse);
		if (card.fTotalUse > 1000 || card.fTotalUse < 20) {
			printf("金额错误\n");
			return;
		}
		strcpy(card.aName,newCardName);
		strcpy(card.aPwd, newCardPwd);
		card.nStatus = 0;
		card.nUseCount = 0;
		card.fBalance = card.fTotalUse;
		card.tStart = card.tEnd = card.tLast = time(NULL);
		startTime = localtime(&card.tStart);
		endTime = localtime(&card.tEnd);
		endTime->tm_year = startTime->tm_year + 1;
		card.tEnd = mktime(endTime);
		cards[*pIndex] = card;
		(*pIndex)++;
		printf("添加卡成功\n\n");
}

void displayCards(Card cards[], int* pIndex)
{
	char aStartTime[20] = { 0 };
	for (int i = 0; i < *pIndex; i++) {
		printf("\n卡号：\t%s\n", cards[i].aName);
		printf("密码：\t%s\n", cards[i].aPwd);
		printf("状态：\t%s\n", cards[i].nStatus==0?"未上机":"已上机");
		timeToString(cards[i].tStart, aStartTime);
		printf("开卡时间：\t%s\n", aStartTime);
		printf("金额：\t%.2f\n", cards[i].fTotalUse);
		printf("使用次数：\t%d\n", cards[i].nUseCount);
		printf("\n");
	}
}