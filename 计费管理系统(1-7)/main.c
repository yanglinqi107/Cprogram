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
		printf("数据错误\n");
		return 0;
	}
	if (readBilling(&pBillingNodeHead, BILLINGPATH) == 0)
	{
		printf("数据错误\n");
		return 0;
	}
	int nselection;
	printf("\n欢迎进入计费管理系统\n\n");
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
				printf("退出");	
				break;
			}
			default:
			{
				printf("输入的菜单项序号错误\n");
			}
		}
	} while (nselection!=0);
	
	return 0;
}

void outputmenu()
{
	printf("\n--------菜单--------\n");
	printf("1.添加卡\n");
	printf("2.查找卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("9.展示卡\n");
	printf("0.退出\n");
	printf("请选择菜单项编号（0-9）：");
}
