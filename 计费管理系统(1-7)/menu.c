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
	
	printf("\n--------��ӿ�--------\n");
	printf("�����뿨�ţ�1~18����");
	gets(newCardName);
	if (strlen(newCardName)>18||newCardName[0]=='\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	pCardNodeTail= *ppCardNodeHead;
	while (pCardNodeTail != NULL)
	{
		if (strcmp(pCardNodeTail->data.aName, newCardName) == 0)
		{
			printf("���Ѵ���\n");
			return;
		}
		else
			pCardNodeTail = pCardNodeTail->next;
	}
	printf("���������루1~8����");
	gets(newCardPwd);
	if (strlen(newCardPwd) > 8|| newCardPwd[0]=='\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�����뿪�����:");
	scanf("%f", &(pCardNode->data.fTotalUse));
	while (getchar() != '\n');
	if (pCardNode->data.fTotalUse<=0)
	{
		printf("������\n");
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
	printf("��ӿ��ɹ�\n\n");
}

void displayCards(CardNode* pCardNodeHead)
{
	CardNode* pCardNode;
	pCardNode = pCardNodeHead;
	char aStartTime[20] = { 0 };
	while (pCardNode != NULL) {
		printf("\n���ţ�\t%s\n",pCardNode->data.aName);
		printf("���룺\t%s\n", pCardNode->data.aPwd);
		if (pCardNode->data.nStatus == UNUSE)
			printf("״̬��\tδ�ϻ�\n");
		if (pCardNode->data.nStatus == USING)
			printf("״̬��\t�����ϻ�\n");
		if (pCardNode->data.nStatus == INVALID)
			printf("״̬��\t��ע��\n");
		timeToString(pCardNode->data.tStart, aStartTime);
		printf("����ʱ�䣺\t%s\n", aStartTime);
		printf("��\t%.2f\n", pCardNode->data.fBalance);
		printf("ʹ�ô�����\t%d\n", pCardNode->data.nUseCount);
		printf("\n");
		pCardNode = pCardNode->next;
	};
}

void shangji(CardNode* pCardNodeHead, BillingNode** ppBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };
	
	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("\n------�ϻ���Ϣ------\n\n");
	LogonInfo* pInfo = malloc(sizeof(LogonInfo));
	char aTime[20] = { 0 };
	int nResult = logon(aName, aPwd, pInfo, pCardNodeHead, ppBillingNodeHead);
	switch (nResult)
	{
		case NOFINDCARD:
		case NOMATCH:
		{
			printf("\n�������ڣ�����Ϣ���󣬲����ϻ���\n\n");
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tLogon, aTime);
			printf("\n���ţ�\t%s\n", aName);
			printf("��\t%.2f\n", pInfo->fBalance);
			printf("�ϻ�ʱ�䣺\t%s\n", aTime);
			break;
		}
		case USING:
		{
			printf("\n�ÿ�����ʹ�ã������ظ��ϻ���\n\n");
			break;
		}
		case INVALID:
		{
			printf("\n�ÿ���ע���������ϻ���\n\n");
			break;
		}
		case ENOUGHMONEY:
		{
			printf("\n�����Ϊ0�������ϻ���\n\n");
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
	
	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	SettleInfo* pInfo = malloc(sizeof(SettleInfo));
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	printf("\n------�»���Ϣ------\n\n");
	int nResult = settle(aName, aPwd, pInfo, pCardNodeHead, pBillingNodeHead);
	switch (nResult)
	{
	case NOFINDCARD:
	case NOMATCH:
	{
		printf("\n�������ڣ�����Ϣ���ԣ������»�\n\n");
		break;
	}
	case SUCCESS:
	{
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);

		printf("\n���ţ�\t%s\n", aName);
		printf("\n���ѣ�\t%.2f\n", pInfo->fAmount);
		printf("\n��\t%.2f\n", pInfo->fBalance);
		printf("\n�ϻ�ʱ�䣺\t%s\n", aStartTime);
		printf("\n�»�ʱ�䣺\t%s\n", aEndTime);
		break;
	}
	case UNUSE:
	{
		printf("\n�ÿ�û���ϻ���\n\n");
		break;
	}
	case ENOUGHMONEY:
	{
		printf("\n�����㣬���ȳ�ֵ���ϻ���\n\n");
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

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("�������\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("�������\n");
		return;
	}
	printf("\n------�ϻ���Ϣ------\n\n");
	LogonInfo* pInfo = malloc(sizeof(LogonInfo));
	char aTime[20] = { 0 };
	int nResult = logon2(aName, aPwd, pInfo, pCardNodeHead, ppBillingNodeHead);
	if (nResult == TRUE)
	{
		timeToString(pInfo->tLogon, aTime);
		printf("\n���ţ�\t%s\n", aName);
		printf("��\t%.2f\n", pInfo->fBalance);
		printf("�ϻ�ʱ�䣺\t%s\n", aTime);
	}
	free(pInfo);
}

void xiaji2(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	SettleInfo* pInfo = malloc(sizeof(SettleInfo));
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	printf("\n------�»���Ϣ------\n\n");
	int nResult = settle2(aName, aPwd, pInfo, pCardNodeHead, pBillingNodeHead);
	if (nResult == TRUE)
	{

		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);

		printf("\n���ţ�\t%s\n", aName);
		printf("\n���ѣ�\t%.2f\n", pInfo->fAmount);
		printf("\n��\t%.2f\n", pInfo->fBalance);
		printf("\n�ϻ�ʱ�䣺\t%s\n", aStartTime);
		printf("\n�»�ʱ�䣺\t%s\n", aEndTime);
	}
	free(pInfo);
}

void addMoney(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };
	float fmoney;

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%98s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������ֵ���:");
	scanf("%f", &fmoney);
	while (getchar() != '\n');
	if (fmoney <= 0)
	{
		printf("������\n");
		return;
	}

	MoneyInfo pInfo;
	printf("\n-------��ֵ��Ϣ����-------\n\n");
	int nResult = AddMoney(aName, aPwd, fmoney, &pInfo, pCardNodeHead);
	if (nResult == FALSE)
		printf("��ֵʧ�ܣ�\n");
	if (nResult == TRUE)
	{
		printf("����:\t%s\n", aName);
		printf("��ֵ���:\t%.2f\n", fmoney);
		printf("���:\t%.2f\n", pInfo.fBalance);
	}
}

void returnMoney(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}

	MoneyInfo pInfo;
	printf("\n-------�˷���Ϣ����-------\n\n");
	int nResult = ReturnMoney(aName, aPwd, &pInfo, pCardNodeHead);
	if (nResult == FALSE)
		printf("�˷�ʧ�ܣ�\n");
	if (nResult == TRUE)
	{
		printf("����:\t%s\n", aName);
		printf("�˷ѽ��:\t%.2f\n", pInfo.fMoney);
		printf("���:\t%.2f\n", pInfo.fBalance);
	}
}

void statNewCard(CardNode* pCardNodeHead)
{
	unsigned yearStart, monthStart, dayStart;
	unsigned yearEnd, monthEnd, dayEnd;

	printf("������ͳ�ƵĿ�ʼʱ�䣨��-��-�գ���");
	(void)scanf("%u-%u-%u", &yearStart, &monthStart, &dayStart);
	if (IsLegal(yearStart, monthStart, dayStart) == 0)
	{
		printf("ͳ�ƵĿ�ʼʱ�䲻�Ϸ�\n");
		return;
	}
	printf("������ͳ�ƵĽ���ʱ�䣨��-��-�գ���");
	(void)scanf("%u-%u-%u", &yearEnd, &monthEnd, &dayEnd);
	if (IsLegal(yearEnd, monthEnd, dayEnd) == 0)
	{
		printf("ͳ�ƵĽ���ʱ�䲻�Ϸ�\n");
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
		printf("ͳ��ʱ�䲻�Ϸ�\n");
		return;
	}

	FILE* fp = NULL;
	if ((fp = fopen("card_tj.txt", "w")) == NULL)
		return;

	*(strchr(timeStart, ' ')) = '\0';
	*(strchr(timeEnd, ' ')) = '\0';

	fprintf(fp, "%s", "\t\t\t������ͳ�Ʊ���\n");
	fprintf(fp, "\t\t%s---%s\n", timeStart, timeEnd);
	fprintf(fp, "%s", "-----------------------------------------\n");
	fprintf(fp,"%s","����   \t����ʱ��   \t\t\t�����\n");

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
	fprintf(fp, "\t\t����������%d\n", cardCnt);

	fclose(fp);
	printf("\n������%d���¿������������ɣ�\n", cardCnt);

	return;
}

void logout(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };
	char aPwd[9] = { 0 };

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	printf("�������루1~8):");
	scanf("%8s", aPwd);
	while (getchar() != '\n');
	if (strlen(aPwd) > 8 || aPwd[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}

	int nResult = Logout(aName, aPwd, pCardNodeHead);
	if (nResult == FALSE)
		printf("ע��ʧ�ܣ�\n");
	if (nResult == TRUE)
		printf("ע���ɹ���\n");
}

void query(CardNode* pCardNodeHead)
{
	char aName[19] = { 0 };

	printf("�����뿨�ţ�1~18):");
	scanf("%18s", aName);
	while (getchar() != '\n');
	if (strlen(aName) > 18 || aName[0] == '\0')
	{
		printf("��������ݳ��ȴ���\n");
		return;
	}
	queryCard(aName, pCardNodeHead);
}