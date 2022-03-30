#pragma once
#include "global.h"
#include "CGraph.h"

//ҵ���߼���
class CGameLogic
{
	
public:
	CGameLogic(void);
	~CGameLogic(void);
public:
	void InitMap(CGraph &graph);

	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);

	void Clear(CGraph& graph, Vertex v1, Vertex v2);

	int GetVexPath(Vertex avPath[AVPATHNUM]);
	void UpdateArc(CGraph& graph, int nRow, int nCol);

	//�ж�ͼƬ�Ƿ����꣬����ʤ����
	bool IsAllBlank(CGraph& graph);

	//��ͼ��Ѱ��һ����ͨ��·��
	bool SearchValidPath(CGraph& graph);

	//
	void ResetGraph(CGraph& graph);

protected:

	//��ͨ��·�������㣩
	Vertex m_avPath[AVPATHNUM];	
	//·���Ķ�����
	int m_nVexNum;	
	//·���Ĺյ���
	int m_nCornerNum;			
	
	//�����������Ѱһ����Ч��ͨ·��
	bool SearchPath(CGraph& graph, int nV0, int nV1);

	//�ж�vi�����Ƿ��Ѿ���ӵ�·����
	bool IsExsit(int Vi);

	//�ж��Ƿ��ǹյ�
	bool IsCorner();

	void AddVertex(Vertex v);
	void PopVertex();
};

