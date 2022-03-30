#pragma once
#include "global.h"

//图结构
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

protected:

	Vertices m_Vertices;	//顶点一维数组
	int m_nVertexNum;		//顶点的数量
	AdjMatrix m_AdjMatrix;	//边的二维数组
	int m_nArcnum;			//边的数量
	//初始化图结构
	void InitGraph();

public:

	//将顶点info添加到顶点数组
	int AddVertex(int info);

	//获取顶点数组中索引为nIndex的顶点
	int GetVertex(int nIndex);

	//添加nV1Index和nV2Index的关系
	void AddArc(int nV1Index, int nV2Index);

	//获取顶点数组中顶点数
	int GetVexnum(void);

	//获取nV1Index和nV2Index的关系
	int GetArc(int nV1Index, int nV2Index);

	//更新顶点信息
	void UpdateVertex(int nIndex, int nInfo);

	//清空重置图结构
	void ClearGraph();
};

