#pragma once

//���嶥��ṹ��
typedef struct tagVertex
{
	int row;	//��
	int col;	//��
	int info;	//��Ϣ��
}Vertex;

#define		BLANK				-1		//��ϷͼƬ����
#define		MAX_ROW				10		//��Ϸ��ͼ����
#define		MAX_COL				16		//��Ϸ��ͼ����
#define		MAX_VERTEX_NUM		160		//������
#define		MAX_PIC_NUM			10		//ͼƬ��ɫ
#define		REPEAT_NUM			16		//ÿ�ֻ�ɫͼƬ����
#define		MAP_TOP				50		//��Ϸ��ͼ���Ͻ�Y����
#define		MAP_LEFT			50		//��Ϸ��ͼ���Ͻ�X����
#define		PIC_WIDTH			40		//��ϷͼƬ���X
#define		PIC_HEIGHT			40		//��ϷͼƬ�߶�Y
#define     AVPATHNUM			100		//·����Ŀ
#define     PLAY_TIME_ID		1
#define		GAME_LOSE			-1		//ʧ��
#define		GAME_SUCCESS		0		//��ʤ
#define		GAME_PLAY			1		//��Ϸ���ڽ���
#define		MAX_TIME			300		//��Ϸ����ʱ