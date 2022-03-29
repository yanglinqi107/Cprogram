#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"service.h"
#include"model.h"
#include"menu.h"
#include"tool.h"
#include"global.h"

int readCard(CardNode** ppCardNodeHead, char* pPath)
{
	CardNode* pCardNode = NULL, * pCardNodeTail = NULL;
	*ppCardNodeHead = NULL;
	FILE* fp = NULL;

	if ((fp = fopen(pPath, "ab+")) == NULL)
		return 0;

	while (!feof(fp))
	{
		pCardNode = (CardNode*)malloc(sizeof(CardNode));
		if (fread(&(pCardNode->data), sizeof(Card), 1, fp) != 0)
		{
			if (*ppCardNodeHead == NULL)
			{
				*ppCardNodeHead = pCardNode;
				pCardNodeTail = pCardNode;
				pCardNodeTail->next = NULL;
			}
			else
			{
				pCardNodeTail->next = pCardNode;
				pCardNodeTail = pCardNodeTail->next;
				pCardNodeTail->next = NULL;
			}
		}
	}
	fclose(fp);
	return 1;
}

int readBilling(BillingNode** ppBillingNodeHead, char* pPath)
{
	BillingNode* pBillingNode = NULL, * pBillingNodeTail = NULL;
	*ppBillingNodeHead = NULL;
	FILE* fp = NULL;

	if ((fp = fopen(pPath, "ab+")) == NULL)
		return 0;

	while (!feof(fp))
	{
		pBillingNode = (BillingNode*)malloc(sizeof(BillingNode));
		if (fread(&(pBillingNode->data), sizeof(Billing), 1, fp) != 0)
		{
			if (*ppBillingNodeHead == NULL)
			{
				*ppBillingNodeHead = pBillingNode;
				pBillingNodeTail = pBillingNode;
				pBillingNodeTail->next = NULL;
			}
			else
			{
				pBillingNodeTail->next = pBillingNode;
				pBillingNodeTail = pBillingNodeTail->next;
				pBillingNodeTail->next = NULL;
			}
		}
	}
	fclose(fp);
	return 1;
}

int saveCard(Card* pCard, char* pPath)
{
	FILE* fp = NULL;
	if ((fp = fopen(pPath, "ab+")) == NULL)
		return 0;
	fwrite(pCard, sizeof(Card), 1, fp);
	fclose(fp);
	return 1;
}

int saveBilling(Billing* pBilling, char* pPath)
{
	FILE* fp = NULL;
	if ((fp = fopen(pPath, "ab+")) == NULL) 
		return 0;
	fwrite(pBilling, sizeof(Billing), 1, fp);
	fclose(fp);
	return 1;
}

int saveMoney(Money* pMoney, char* pPath)
{
	FILE* fp = NULL;
	if ((fp = fopen(pPath, "ab+")) == NULL)
		return 0;
	fwrite(pMoney, sizeof(Money), 1, fp);
	fclose(fp);
	return 1;
}

void releaseCard(CardNode* pCardNodeHead)
{
	CardNode* pCardNode=pCardNodeHead;;
	
	while (pCardNodeHead != NULL)
	{
		pCardNode = pCardNodeHead;
		pCardNodeHead = pCardNodeHead->next;
		free(pCardNode);
	}
	pCardNodeHead = NULL;
}

void releaseBilling(BillingNode* pBillingNodeHead)
{
	BillingNode* pBillingNode = pBillingNodeHead;
	
	while (pBillingNodeHead != NULL)
	{
		pBillingNode = pBillingNodeHead;
		pBillingNodeHead = pBillingNode->next;
		free(pBillingNode);
	}
	pBillingNodeHead = NULL;
}

Card* cardIsExist(char* strNo, long* pCardIndex, CardNode* const pCardNodeHead)
{
	CardNode* pCardNode = pCardNodeHead;
	*pCardIndex = 0;
	while (pCardNode != NULL)
	{
		if (strcmp(pCardNode->data.aName, strNo) == 0)
			return &(pCardNode->data);
		pCardNode = pCardNode->next;
		(*pCardIndex)++;
	}
	return NULL;
}

Billing* billingIsExist(char* strNo, long* pBillingIndex, BillingNode* const pBillingNodeHead)
{
	BillingNode* pBillingNode = pBillingNodeHead;
	*pBillingIndex = 0;
	while (pBillingNode != NULL)
	{
		if (strcmp(pBillingNode->data.aCardName, strNo) == 0 && pBillingNode->data.nStatus==NOSETTLEMENT)
			return &(pBillingNode->data);
		pBillingNode = pBillingNode->next;
		(*pBillingIndex)++;
	}
	return NULL;
}

int updateCard(const Card* pCard, char* pPath, long nCardIndex)
{
	FILE* fp = NULL;
	if ((fp = fopen(pPath, "rb+")) == NULL)
		return 0;
	fseek(fp, nCardIndex * sizeof(Card), SEEK_SET);
	fwrite(pCard, sizeof(Card), 1, fp);
	fclose(fp);
	return 1;
}

int updateBilling(const Billing* pBilling, char* pPath, int nBillingIndex)
{
	FILE* fp = NULL;
	if ((fp = fopen(pPath, "rb+"))== NULL)
		return 0;
	fseek(fp, sizeof(Billing) * nBillingIndex, SEEK_SET);
	fwrite((char*)pBilling, sizeof(Billing), 1, fp);
	fclose(fp);
	return 1;
}

int logon(char* strNo, char* strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead, BillingNode** ppBillingNodeHead)
{
	Billing billing;
	long nCardIndex;
	Card* pCard = cardIsExist(strNo, &nCardIndex, pCardNodeHead);

	if (pCard == NULL)
		return NOFINDCARD;
	if (strcmp(pCard->aPwd, strPwd) != 0)
		return NOMATCH;
	if (pCard->nStatus == USING)
		return USING;
	if (pCard->nStatus == INVALID)
		return INVALID;
	if (pCard->fBalance <= 0)
		return ENOUGHMONEY;

	pCard->nStatus = USING;
	pCard->nUseCount++;
	pCard->tLast = time(NULL);

	updateCard(pCard, CARDPATH, nCardIndex);

	strcpy(billing.aCardName, strNo);
	billing.tStart = time(NULL);
	billing.tEnd = 0;
	billing.nStatus = NOSETTLEMENT;
	billing.fAmount = 0;

	saveBilling(&billing, BILLINGPATH);

	BillingNode* pBillingNode = malloc(sizeof(BillingNode));
	pBillingNode->data = billing;

	BillingNode* pBillingNodeTail = *ppBillingNodeHead;

	if (*ppBillingNodeHead == NULL)
	{
		*ppBillingNodeHead = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	else
	{
		while (pBillingNodeTail->next != NULL)
			pBillingNodeTail = pBillingNodeTail->next;
		pBillingNodeTail->next = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	pBillingNodeTail->next = NULL;
	strcpy(pInfo->aCardName, strNo);
	pInfo->fBalance = pCard->fBalance;
	pInfo->tLogon = billing.tStart;

	return SUCCESS;
}

int settle(char* strNo, char* strPwd, SettleInfo* pInfo, CardNode* pCardNodeHead, BillingNode* const pBillingNodeHead)
{
	int nCardIndex;
	Card* pCard = cardIsExist(strNo, &nCardIndex, pCardNodeHead);

	if (pCard == NULL)
		return NOFINDCARD;
	if (strcmp(pCard->aPwd, strPwd) != 0)
		return NOMATCH;
	if (pCard->nStatus != USING)
		return UNUSE;
	
	
	int nBillingIndex;
	Billing* pBilling = billingIsExist(strNo, &nBillingIndex, pBillingNodeHead);
	if (pBilling == NULL)
	{
		printf("\nδ�ҵ��Ʒ���Ϣ\n");
		return UNUSE;
	}
	double dbAmount = getAmount(pBilling->tStart);
	float fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance <= 0)
		return ENOUGHMONEY;

	pCard->fBalance = fBalance;
	pCard->nStatus = UNUSE;
	pCard->tLast = time(NULL);
	
	updateCard(pCard, CARDPATH, nCardIndex);
	
	pBilling->fAmount = (float)dbAmount;
	pBilling->nStatus = YESSETTLEMENT;
	pBilling->tEnd = time(NULL);
	
	updateBilling(pBilling, BILLINGPATH, nBillingIndex);

	strcpy(pInfo->aCardName, strNo);
	pInfo->fAmount = (float)dbAmount;
	pInfo->fBalance = fBalance;
	pInfo->tStart = pBilling->tStart;
	pInfo->tEnd = time(NULL);

	return SUCCESS;
}

double getAmount(time_t tStart)
{
	double dbAmount = 0;
	int nCount = 0;
	int nSec = 0;
	int nMinutes = 0;
	time_t tEnd = time(NULL);
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	if (nMinutes % UNIT == 0)
		nCount = nMinutes / UNIT;
	else
		nCount = nMinutes / UNIT+1;
	if (nCount == 0)
		nCount = 1;
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

int logon2(char* strNo, char* strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead, BillingNode** ppBillingNodeHead)
{
	Billing billing;
	long index = 0;

	Card* pCard = cardIsExist(strNo, &index, pCardNodeHead);	//�жϿ��Ƿ����

	if (pCard == NULL)											//�ж��Ƿ�����ϻ�����
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (strcmp(pCard->aPwd, strPwd) != 0)
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (pCard->nStatus == USING)
	{
		printf("\n�ÿ������ϻ��������ظ��ϻ���\n");
		return FALSE;
	}
	if (pCard->nStatus == INVALID)
	{
		printf("\n�ÿ���ע���������ϻ���\n");
		return FALSE;
	}
	if (pCard->fBalance <= 0)
	{
		printf("\n�����㣬�޷��ϻ���\n");
		return FALSE;
	}

	pCard->nStatus = USING;
	pCard->nUseCount++;
	pCard->tLast = time(NULL);

	updateCard(pCard, CARDPATH, index);			//���²����濨��Ϣ
	
	strcpy(billing.aCardName, strNo);
	billing.tStart = time(NULL);
	billing.tEnd = 0;
	billing.nStatus = NOSETTLEMENT;
	billing.fAmount = 0;

	saveBilling(&billing, BILLINGPATH);						//����Ʒ���Ϣ

	BillingNode* pBillingNode = malloc(sizeof(BillingNode));
	pBillingNode->data = billing;

	BillingNode* pBillingNodeTail = *ppBillingNodeHead;

	if (*ppBillingNodeHead == NULL)							//���Ʒ���Ϣ��������
	{
		*ppBillingNodeHead = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	else
	{
		while (pBillingNodeTail->next!= NULL)
			pBillingNodeTail = pBillingNodeTail->next;
		pBillingNodeTail->next = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	pBillingNodeTail->next = NULL;
	strcpy(pInfo->aCardName, strNo);
	pInfo->fBalance = pCard->fBalance;
	pInfo->tLogon = billing.tStart;

	return TRUE;
}

int settle2(char* strNo, char* strPwd, SettleInfo* pInfo, CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{	
	long indexCard = 0, indexBilling = 0;

	Card* pCard = cardIsExist(strNo, &indexCard, pCardNodeHead);	//�жϿ��Ƿ����

	if (pCard == NULL)											//�жϿ��Ƿ�����»�����
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (strcmp(pCard->aPwd, strPwd) != 0)
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (pCard->nStatus == UNUSE)
	{
		printf("\n�ÿ�δ�ϻ���\n");
		return FALSE;
	}
	if (pCard->nStatus == INVALID)
	{
		printf("\n�ÿ���ע����\n");
		return FALSE;
	}

	Billing* pBilling=billingIsExist(strNo, &indexBilling, pBillingNodeHead);	//�жϼƷ���Ϣ�Ƿ����
	
	if (pBilling == NULL)
	{
		printf("\nδ�ҵ��Ʒ���Ϣ\n");
		return FALSE;
	}
	
	double dbAmount = getAmount(pBilling->tStart);		//�����ϻ��������
	
	float fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance <= 0)
	{
		printf("\n�����㣬���ȳ�ֵ���»���\n");
		return FALSE;
	}

	pCard->fBalance = fBalance;
	pCard->nStatus = UNUSE;
	pCard->tLast = time(NULL);

	updateCard(pCard, CARDPATH, indexCard);				//���²����濨��Ϣ

	pBilling->fAmount = (float)dbAmount;
	pBilling->nStatus = YESSETTLEMENT;
	pBilling->tEnd = time(NULL);

	updateBilling(pBilling, BILLINGPATH, indexBilling);	//���²�����Ʒ���Ϣ

	strcpy(pInfo->aCardName, strNo);
	pInfo->fAmount = (float)dbAmount;
	pInfo->fBalance = fBalance;
	pInfo->tStart = pBilling->tStart;
	pInfo->tEnd = time(NULL);

	return	TRUE;
}

int AddMoney(char* strNo,char* strPwd, float fmoney, MoneyInfo* pInfo,CardNode* pCardNodeHead)
{
	Money pMoney ;
	long index = 0;

	Card* pCard = cardIsExist(strNo, &index, pCardNodeHead);	//�жϿ��Ƿ����

	if (pCard == NULL)											//�ж��Ƿ���ϳ�ֵ����
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (strcmp(pCard->aPwd, strPwd) != 0)
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (pCard->nStatus == INVALID)
	{
		printf("\n�ÿ���ע����\n");
		return FALSE;
	}

	pCard->fBalance = pCard->fBalance + fmoney;					//���¿���Ϣ������
	updateCard(pCard, CARDPATH, index);
	
	strcpy(pMoney.aCardName, strNo);							//��ӳ�ֵ��Ϣ
	pMoney.fMoney = fmoney;
	pMoney.tTime = time(NULL);
	pMoney.nDel = pCard->nDel;
	pMoney.nStatus = ADD;

	saveMoney(&pMoney, MONEYPATH);

	pInfo->fBalance = pCard->fBalance;
	return TRUE;
	
}

int ReturnMoney(char* strNo, char* strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead)
{
	long index = 0;

	Card* pCard = cardIsExist(strNo, &index, pCardNodeHead);	//�жϿ��Ƿ����

	if (pCard == NULL)										//�ж��Ƿ�����˷�����
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (strcmp(pCard->aPwd, strPwd) != 0)
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (pCard->nStatus == USING)
	{
		printf("\n�ÿ������ϻ��������»���\n");
		return FALSE;
	}
	if (pCard->nStatus == INVALID)
	{
		printf("\n�ÿ���ע����\n");
		return FALSE;
	}
	if (pCard->fBalance <= 0)
	{
		printf("\n�����㣡\n");
		return FALSE;
	}
	

	pInfo->fMoney = pCard->fBalance;
	pInfo->fBalance = 0.0;

	pCard->fBalance =0.0;								//���¿���Ϣ������
	updateCard(pCard, CARDPATH, index);

	Money pMoney;												//�����˷���Ϣ
	strcpy(pMoney.aCardName, strNo);
	pMoney.fMoney = pCard->fBalance;
	pMoney.tTime = time(NULL);
	pMoney.nDel = pCard->nDel;
	pMoney.nStatus = RETURN;
	
	saveMoney(&pMoney, MONEYPATH);

	return TRUE;
}

int IsLegal(int year, int mon, int day)
{
	//31:1 3 5 7 8 10 12
	//30:4 6 9 11
	//28��29:2
	if (year < 0 || mon <= 0 || mon>12 || day <= 0 || day > 31)
		return 0;
	if (1 == mon || 3 == mon || 5 == mon || 7 == mon || 8 == mon || 10 == mon || 12 == mon)
	{
		return 1;
	}
	if (IsLeapYear(year))
	{
		if (2 == mon && (28 == day || 30 == day || 31 == day))
			return 0;
		return 1;
	}
	else
	{
		if (2 == mon && (29 == day || 30 == day || 31 == day))
			return 0;
		return 1;
	}
}

int IsLeapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0))|| (year % 400 == 0))
		return 1;
	return 0;
}

int Logout(char* strNo, char* strPwd, CardNode* pCardNodeHead)
{
	long index = 0;

	Card* pCard = cardIsExist(strNo, &index, pCardNodeHead);	//�жϿ��Ƿ����

	if (pCard == NULL)											//�ж��Ƿ����ע������
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (strcmp(pCard->aPwd, strPwd) != 0)
	{
		printf("\n���Ż��������\n");
		return FALSE;
	}
	if (pCard->nStatus == USING)
	{
		printf("\n�ÿ������ϻ��������»���\n");
		return FALSE;
	}
	if (pCard->fBalance > 0)
	{
		printf("\n��������0�������˷ѣ�\n");
		return FALSE;
	}

	pCard->nStatus = INVALID;									//���²����濨��Ϣ
	updateCard(pCard, CARDPATH, index);

	return TRUE;
}

void queryCard(char* strNo, CardNode* pCardNodeHead)
{
	int i = 0, index = 0;
	char aStartTime[20] = { 0 };
	CardNode* pCardNode = pCardNodeHead;
	while (pCardNode != NULL)
	{
		while (*(strNo + i) != '\0')
		{
			if (*(strNo + i) != pCardNode->data.aName[i])
				break;
			i++;
		}
		if (*(strNo + i) == '\0')
		{
			printf("\n���ţ�\t%s\n", pCardNode->data.aName);
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
			index++;
		}
		i = 0;
		pCardNode = pCardNode->next;
	}
	if (index == 0)
		printf("\nδ���ҵ���\n");
}



