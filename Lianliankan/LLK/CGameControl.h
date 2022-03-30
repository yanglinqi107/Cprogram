#pragma once
#include "global.h"
#include "CGraph.h"

//���Ʋ�
class CGameControl
{
public: 
	CGameControl(void);
	~CGameControl(void);

	//��ʼ��Ϸ
	void StartGame();

	//�õ�ĳ��Ԫ��
	int GetElement(int nRow, int nCol);

	//���õ�һ������
	void SetFirstPoint(int nRow, int nCol);

	//���õڶ�������
	void SetSecPoint(int nRow, int nCol);

	//�����жϣ��Ƿ���ͨ
	bool Link(Vertex avPath[AVPATHNUM], int& nVexNum);

	//�Ƿ�ʤ��
	BOOL IsWin(int nTime);

	//��ʾ
	bool Help(Vertex avPath[AVPATHNUM], int& nVexnum);

	//
	void ResetGraph();

protected:
	CGraph m_graph;
	Vertex m_ptSelFirst;	//��һ��ѡ�е�
	Vertex m_ptSelSec;		//�ڶ���ѡ�е�
};

