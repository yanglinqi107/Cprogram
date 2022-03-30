#include "pch.h"
#include "CGameControl.h"
#include "CGameLogic.h"

CGameControl::CGameControl(void)
{
}

CGameControl::~CGameControl(void)
{
}

void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[AVPATHNUM],int &nVexNum)
{
	//m_ptSelFirst和m_ptSelSec是否连通
	//判断是否为同一张图片
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//判断图片是否相同
	if (m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col) != m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col))
	{
		return false;
	}

	//判断是否连通
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec))
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);

		//返回路径顶点
		nVexNum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

BOOL CGameControl::IsWin(int nTime)
{
	CGameLogic logic;

	//判断游戏时间
	if (nTime <= 0)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	if (logic.IsAllBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[AVPATHNUM], int& nVexnum)
{
	CGameLogic logic;

	//判断图是否为空
	if (m_graph.GetVexnum() == 0)
	{
		return false;
	}
	//不为空，则调用SearchValidPath

	if (logic.SearchValidPath(m_graph))
	{
		nVexnum = logic.GetVexPath(avPath);
		return true;
	}
	return false;
}

void CGameControl::ResetGraph()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}

