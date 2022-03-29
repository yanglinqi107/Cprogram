#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"model.h"
#include"menu.h"
#include"tool.h"

void outputmenu();
void readCard(Card cards[], int* pIndex);
void saveCard(Card cards[], int* pIndex);

int main(void)
{
	Card cards[100];
	int indexCard = 0;
	readCard(cards,&indexCard);
	int nselection;
	printf("欢迎进入计费管理系统\n\n");
	do {
		outputmenu();
		nselection = -1;
		scanf_s("%d", &nselection);
		while (getchar() != '\n');
		switch (nselection) {

		case 1: add(cards, &indexCard); break;

		case 2: displayCards(cards, &indexCard); break;

		case 3: printf("上机\n"); break;

		case 4: printf("下机\n"); break;

		case 5: printf("充值\n"); break;

		case 6: printf("退费\n"); break;

		case 7:printf("查询统计\n"); break;

		case 8: printf("注销卡\n"); break;

		case 0:saveCard(cards, &indexCard); printf("退出"); break;

		default:printf("输入的菜单项序号错误\n");
		}
	} while (nselection!=0);
	
	return 0;
}

void outputmenu()
{
	printf("--------菜单--------\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("0.退出\n");
	printf("请选择菜单项编号（0-8）：");

	}

void readCard(Card cards[], int *pIndex)
{
	*pIndex = 0;
	FILE *fp=NULL;
	if ((fp = fopen("card.dat", "rb")) == NULL) {
		return;
	}
	while (!feof(fp)) {
		if (fread(&cards[*pIndex],sizeof(Card),1,fp)!=0)
			(*pIndex)++;
	}
	fclose(fp);

}

void saveCard(Card cards[], int* pIndex)
{
	FILE *fp=NULL;
	if ((fp = fopen("card.dat", "wb+")) == NULL) {
		return;
	}
	for (int i = 0; i < *pIndex; i++) {
		fwrite(&cards[i], sizeof(Card), 1, fp);
	}
	fclose(fp);
}
