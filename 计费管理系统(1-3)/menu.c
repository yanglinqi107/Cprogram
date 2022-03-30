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
		printf("\n--------��ӿ�--------\n");
		printf("�����뿨�ţ�1~18����");
		gets(newCardName);
		if (strlen(newCardName) > 18|| newCardName[0] =='\0') {
			printf("�������\n");
			return;
		}
		printf("���������루1~8����");
		gets(newCardPwd);
		if (strlen(newCardPwd) > 8 || newCardPwd[0] =='\0') {
			printf("�������\n");
			return;
		}
		printf("�����뿪�����(20~1000):");
		scanf_s("%f", &card.fTotalUse);
		if (card.fTotalUse > 1000 || card.fTotalUse < 20) {
			printf("������\n");
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
		printf("��ӿ��ɹ�\n\n");
}

void displayCards(Card cards[], int* pIndex)
{
	char aStartTime[20] = { 0 };
	for (int i = 0; i < *pIndex; i++) {
		printf("\n���ţ�\t%s\n", cards[i].aName);
		printf("���룺\t%s\n", cards[i].aPwd);
		printf("״̬��\t%s\n", cards[i].nStatus==0?"δ�ϻ�":"���ϻ�");
		timeToString(cards[i].tStart, aStartTime);
		printf("����ʱ�䣺\t%s\n", aStartTime);
		printf("��\t%.2f\n", cards[i].fTotalUse);
		printf("ʹ�ô�����\t%d\n", cards[i].nUseCount);
		printf("\n");
	}
}