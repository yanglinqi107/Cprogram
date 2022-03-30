#pragma once
#include "global.h"
#include "CGraph.h"

//控制层
class CGameControl
{
public: 
	CGameControl(void);
	~CGameControl(void);

	//开始游戏
	void StartGame();

	//得到某个元素
	int GetElement(int nRow, int nCol);

	//设置第一个顶点
	void SetFirstPoint(int nRow, int nCol);

	//设置第二个顶点
	void SetSecPoint(int nRow, int nCol);

	//消子判断，是否连通
	bool Link(Vertex avPath[AVPATHNUM], int& nVexNum);

	//是否胜利
	BOOL IsWin(int nTime);

	//提示
	bool Help(Vertex avPath[AVPATHNUM], int& nVexnum);

	//
	void ResetGraph();

protected:
	CGraph m_graph;
	Vertex m_ptSelFirst;	//第一次选中点
	Vertex m_ptSelSec;		//第二次选中点
};

