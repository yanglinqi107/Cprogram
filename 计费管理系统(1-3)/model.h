#pragma once
#include<time.h>
typedef struct Card {
	char aName[19];		//����
	char aPwd[9];		//����
	int  nStatus;		//��״̬��0-δʹ�ã�1-����ʹ�ã�2-��ע����3-ʧЧ��
	time_t tStart;		//����ʱ��
	time_t tEnd;		//���Ľ�ֹʱ��
	float  fTotalUse;	//�ۼƽ��
	time_t tLast;		//���ʹ��ʱ��
	int nUseCount;		//ʹ�ô���
	float fBalance;		//���
	int nDel;			//ɾ����ʶ��0-δɾ����1-ɾ����
}Card;