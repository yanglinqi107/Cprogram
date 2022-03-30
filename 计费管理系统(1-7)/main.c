#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"model.h"
#include"menu.h"
#include"tool.h"
#include"service.h"
#include"global.h"

void outputmenu();

int main(void)
{
	CardNode* pCardNodeHead=NULL;
	BillingNode* pBillingNodeHead=NULL;

	if (readCard(&pCardNodeHead, CARDPATH) == 0)
	{
		printf("���ݴ���\n");
		return 0;
	}
	if (readBilling(&pBillingNodeHead, BILLINGPATH) == 0)
	{
		printf("���ݴ���\n");
		return 0;
	}
	int nselection;
	printf("\n��ӭ����Ʒѹ���ϵͳ\n\n");
	do {
		outputmenu();
		nselection = -1;
		scanf_s("%d", &nselection);
		while (getchar() != '\n');
		switch (nselection){
			case 1:
			{	
				add(&pCardNodeHead);
				break;
			}
			case 2:
			{
				query(pCardNodeHead);
				break;
			}
			case 3: 
			{
				shangji2(pCardNodeHead,&pBillingNodeHead);
				break;
			}
			case 4: 
			{
				xiaji2(pCardNodeHead,pBillingNodeHead);
				break;
			}
			case 5:
			{
				addMoney(pCardNodeHead);
				break;
			}
			case 6: 
			{
				returnMoney(pCardNodeHead);
				break;
			}
			case 7:
			{
				statNewCard(pCardNodeHead);
				break;
			}
			case 8:
			{
				logout(pCardNodeHead);
				break;
			}
			case 9:
			{
				displayCards(pCardNodeHead);
				break;
			}
			case 0:
			{
				releaseCard(pCardNodeHead);
				releaseBilling(pBillingNodeHead);
				printf("�˳�");	
				break;
			}
			default:
			{
				printf("����Ĳ˵�����Ŵ���\n");
			}
		}
	} while (nselection!=0);
	
	return 0;
}

void outputmenu()
{
	printf("\n--------�˵�--------\n");
	printf("1.��ӿ�\n");
	printf("2.���ҿ�\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("9.չʾ��\n");
	printf("0.�˳�\n");
	printf("��ѡ��˵����ţ�0-9����");
}
