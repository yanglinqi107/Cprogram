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
	printf("��ӭ����Ʒѹ���ϵͳ\n\n");
	do {
		outputmenu();
		nselection = -1;
		scanf_s("%d", &nselection);
		while (getchar() != '\n');
		switch (nselection) {

		case 1: add(cards, &indexCard); break;

		case 2: displayCards(cards, &indexCard); break;

		case 3: printf("�ϻ�\n"); break;

		case 4: printf("�»�\n"); break;

		case 5: printf("��ֵ\n"); break;

		case 6: printf("�˷�\n"); break;

		case 7:printf("��ѯͳ��\n"); break;

		case 8: printf("ע����\n"); break;

		case 0:saveCard(cards, &indexCard); printf("�˳�"); break;

		default:printf("����Ĳ˵�����Ŵ���\n");
		}
	} while (nselection!=0);
	
	return 0;
}

void outputmenu()
{
	printf("--------�˵�--------\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("0.�˳�\n");
	printf("��ѡ��˵����ţ�0-8����");

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
