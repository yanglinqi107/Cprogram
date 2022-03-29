#pragma once
#include<time.h>
typedef struct Card {
	char aName[19];		//����
	char aPwd[9];		//����
	int  nStatus;		//��״̬��UNUSE-δʹ�ã�USING-����ʹ�ã�INVALID-��ע����
	time_t tStart;		//����ʱ��
	time_t tEnd;		//���Ľ�ֹʱ��
	float  fTotalUse;	//�������
	time_t tLast;		//���ʹ��ʱ��
	int nUseCount;		//ʹ�ô���
	float fBalance;		//���
	int nDel;			//ɾ����ʶ��0-δɾ����1-ɾ����
}Card;
typedef struct CardNode {
	Card data;
	struct CardNode* next;
}CardNode;

typedef struct Billing	//�Ʒ���Ϣ�ṹ��
{
	char aCardName[19];	//����
	time_t tStart;		//�ϻ�ʱ��
	time_t tEnd;		//�»�ʱ��
	float fAmount;		//���ѽ��
	int nStatus;		//����״̬��0δ���㣬1�ѽ���
	int nDel;			//ɾ����ǣ�0δɾ����1��ɾ��
}Billing;
typedef struct BillingNode
{
	Billing data;
	struct BillingNode* next;
}BillingNode;

typedef struct LogonInfo	//�ϻ���Ϣ�ṹ��
{
	char aCardName[19];		//����
	time_t tLogon;			//�ϻ�ʱ��
	float fBalance;			//�ϻ�ʱ�����
}LogonInfo;

typedef struct SettleInfo	//�»���Ϣ�ṹ��
{
	char aCardName[19];		//����
	time_t tStart;			//�ϻ�ʱ��
	time_t tEnd;			//�»�ʱ��
	float fAmount;			//���ѽ��
	float fBalance;			//���
}SettleInfo;

typedef struct Money		
{
	char aCardName[19];		//����
	time_t tTime;			//��ֵ�˷�ʱ��
	int nStatus;			//״̬��0-��ֵ��1-�˷�
	float fMoney;			//��ֵ�˷ѽ��
	int nDel;				//ɾ����ʶ��0-δɾ����1-��ɾ��
}Money;

typedef struct MoneyInfo
{
	char aCardName[19];		//����
	float fMoney;			//��ֵ�˷ѽ��
	float fBalance;			//���
}MoneyInfo;