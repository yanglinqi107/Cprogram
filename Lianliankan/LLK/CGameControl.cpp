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
	//m_ptSelFirst��m_ptSelSec�Ƿ���ͨ
	//�ж��Ƿ�Ϊͬһ��ͼƬ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ
	if (m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col) != m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col))
	{
		return false;
	}

	//�ж��Ƿ���ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec))
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);

		//����·������
		nVexNum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

BOOL CGameControl::IsWin(int nTime)
{
	CGameLogic logic;

	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
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

	//�ж�ͼ�Ƿ�Ϊ��
	if (m_graph.GetVexnum() == 0)
	{
		return false;
	}
	//��Ϊ�գ������SearchValidPath

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

