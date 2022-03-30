#include "pch.h"
#include "CGraph.h"

CGraph::CGraph(void)
{
	InitGraph();
}

CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		m_Vertices[i] = -1;
	}
	//初始化边
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
		{
			m_AdjMatrix[i][j] = false;
		}
	}
	m_nVertexNum = 0;
	m_nArcnum = MAX_VERTEX_NUM * MAX_VERTEX_NUM;
}

int CGraph::AddVertex(int info)
{
	if (m_nVertexNum >= MAX_VERTEX_NUM)
	{
		return 0;
	}
	m_Vertices[m_nVertexNum++] = info;
	return m_nVertexNum;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVexnum(void)
{
	return m_nVertexNum;
}

int CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

void CGraph::UpdateVertex(int nIndex, int nInfo)
{
	m_Vertices[nIndex] = nInfo;
}

void CGraph::ClearGraph()
{
	InitGraph();
}
