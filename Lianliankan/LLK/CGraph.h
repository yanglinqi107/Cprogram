#pragma once
#include "global.h"

//ͼ�ṹ
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

protected:

	Vertices m_Vertices;	//����һά����
	int m_nVertexNum;		//���������
	AdjMatrix m_AdjMatrix;	//�ߵĶ�ά����
	int m_nArcnum;			//�ߵ�����
	//��ʼ��ͼ�ṹ
	void InitGraph();

public:

	//������info��ӵ���������
	int AddVertex(int info);

	//��ȡ��������������ΪnIndex�Ķ���
	int GetVertex(int nIndex);

	//���nV1Index��nV2Index�Ĺ�ϵ
	void AddArc(int nV1Index, int nV2Index);

	//��ȡ���������ж�����
	int GetVexnum(void);

	//��ȡnV1Index��nV2Index�Ĺ�ϵ
	int GetArc(int nV1Index, int nV2Index);

	//���¶�����Ϣ
	void UpdateVertex(int nIndex, int nInfo);

	//�������ͼ�ṹ
	void ClearGraph();
};

