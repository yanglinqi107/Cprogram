#pragma once
#include "global.h"
#include "CGraph.h"

//业务逻辑层
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

	//判断图片是否消完，即获胜条件
	bool IsAllBlank(CGraph& graph);

	//在图中寻找一条连通的路径
	bool SearchValidPath(CGraph& graph);

	//
	void ResetGraph(CGraph& graph);

protected:

	//连通的路径（顶点）
	Vertex m_avPath[AVPATHNUM];	
	//路径的顶点数
	int m_nVexNum;	
	//路径的拐点数
	int m_nCornerNum;			
	
	//深度搜索法搜寻一条有效连通路径
	bool SearchPath(CGraph& graph, int nV0, int nV1);

	//判断vi顶点是否已经添加到路径中
	bool IsExsit(int Vi);

	//判断是否是拐点
	bool IsCorner();

	void AddVertex(Vertex v);
	void PopVertex();
};

