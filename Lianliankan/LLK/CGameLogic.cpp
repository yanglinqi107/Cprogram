#include "pch.h"
#include "CGameLogic.h"

CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
	m_nCornerNum = 0;
}

CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(CGraph &graph)
{
	//初始化顶点信息
	int anTemp[MAX_VERTEX_NUM];

	//生成固定地图
	for (int i = 0; i < MAX_PIC_NUM; ++i)
	{
		//重复数
		for (int j = 0; j < REPEAT_NUM; ++j)
		{
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}

	//设置种子
	srand((int)time(NULL));

	//随机交换地图两个数字，生成随机地图
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int temp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = temp;
	}

	//添加顶点，更新边信息
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			graph.AddVertex(anTemp[i * MAX_COL + j]);
			UpdateArc(graph, i, j);
		}
	}
	//for (int i = 0; i < MAX_ROW; ++i)
	//{
	//	for (int j = 0; j < MAX_COL; ++j)
	//	{
	//		//graph.AddVertex(anTemp[i * MAX_COL + j]);
	//		UpdateArc(graph, i, j);
	//	}
	//}
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;

	if (IsCorner())
	{
		++m_nCornerNum;
	}
}

void CGameLogic::PopVertex()
{
	if (IsCorner())
	{
		--m_nCornerNum;
	}
	--m_nVexNum;
}

int CGameLogic::GetVexPath(Vertex avPath[AVPATHNUM])
{
	for (int i = 0; i < m_nVexNum; ++i)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

//更新边
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;

	//与左边相邻的连通
	if (nCol > 0)
	{
		int nV2Index = nV1Index - 1;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	//与右边相邻的连通
	if (nCol < MAX_COL - 1)
	{
		int nV2Index = nV1Index + 1;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	//与上边相邻的连通
	if (nRow > 0)
	{
		int nV2Index = nV1Index - MAX_COL;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
	//与下边相邻的连通
	if (nRow < MAX_ROW -1)
	{
		int nV2Index = nV1Index + MAX_COL;
		int nV1Info = graph.GetVertex(nV1Index);
		int nV2Info = graph.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
}

bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	//获取在顶点数组中的索引号
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	AddVertex(v1);

	if (SearchPath(graph, nIndex1, nIndex2))
	{
		return true;
	}

	PopVertex();
	return false;
}

void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	//获取在顶点数组中的索引号
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	//更新顶点
	graph.UpdateVertex(nIndex1, BLANK);
	graph.UpdateVertex(nIndex2, BLANK);

	//更新边信息
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	//遍历图中nV0行，从0列到MAX_VERTEX_NUM列，值为true的点
	for (int nVi = 0; nVi < MAX_VERTEX_NUM; ++nVi)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			//添加vi到路径中，假设为有效顶点
			Vertex vi;
			vi.row = nVi / MAX_COL;
			vi.col = nVi % MAX_COL;
			AddVertex(vi);

			//拐点数大于2，则弹出vi
			if (m_nCornerNum > 2)
			{
				PopVertex();
				continue;
			}

			//当中间顶点不是nV1时，继续搜寻下一个相邻且连通的顶点
			if (nVi != nV1)
			{
				//当中间顶点不为空，该路径不通
				if (graph.GetVertex(nVi) != BLANK)
				{
					//弹出vi
					PopVertex();
					continue;
				}

				//如果nVi是一个消除的点，则判断nVi与nV1是否连通
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			//如果nVi==nV1,则已经找到一条连通路径
			else
			{
				return true;
			}
			//去除压入的vi，与AddVertex(vi)对应
			PopVertex();
		}
	}
	return false;
}

bool CGameLogic::IsExsit(int Vi)
{
	for (int i = 0; i < m_nVexNum; ++i)
	{
		if (m_avPath[i].row * MAX_COL + m_avPath[i].col == Vi)
			return true;
	}
	return false;
}


bool CGameLogic::IsCorner()
{
	if (m_nVexNum >= 3)
	{
		int v1 = m_avPath[m_nVexNum - 1].row * MAX_COL + m_avPath[m_nVexNum - 1].col;
		int v2 = m_avPath[m_nVexNum - 2].row * MAX_COL + m_avPath[m_nVexNum - 2].col;
		int v3 = m_avPath[m_nVexNum - 3].row * MAX_COL + m_avPath[m_nVexNum - 3].col;

		if (v1 + v3 != v2 * 2)
		{
			return true;
		}
	}
	return false;
}

bool CGameLogic::IsAllBlank(CGraph& graph)
{
	//获取顶点数量
	int nVertexNum = graph.GetVexnum();

	for (int i = 0; i < nVertexNum; ++i)
	{
		if (graph.GetVertex(i) != BLANK)
			return false;
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& graph)
{
	//获取顶点个数
	//int nVexNum = graph.GetVexnum();
	int v1 = 0; 
	int v2 = 0;
	int equalPicture = 0;
	Vertex vex1;

	//找到第一个不为空的点
	for (v1 = 0; v1 < MAX_VERTEX_NUM; ++v1)
	{
		if (graph.GetVertex(v1)!=BLANK)
		{
			//压入v1到avPath中
			vex1.row = v1 / MAX_COL;
			vex1.col = v1 % MAX_COL;
			AddVertex(vex1);
			equalPicture = graph.GetVertex(v1);
			//查找与第一个顶点图片相同的元素
			for (v2 = v1 + 1; v2 < MAX_VERTEX_NUM; ++v2)
			{
				if (equalPicture == graph.GetVertex(v2))
				{
					//判断v1和v2是否连通
					if (SearchPath(graph, v1, v2))
					{
						return true;
					}
				}
			}
			//弹出v1，与AddVertex(v1)对应
			PopVertex();
		}
	}
	return false;
}

void CGameLogic::ResetGraph(CGraph& graph)
{
	//随机交换顶点数组中两个顶点的值
	//设置种子
	srand((int)time(NULL));

	//随机交换地图两个数字，生成随机地图
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int v1 = graph.GetVertex(nIndex1);
		int v2 = graph.GetVertex(nIndex2);
		graph.UpdateVertex(nIndex1, v2);
		graph.UpdateVertex(nIndex2, v1);
	}
	//更新边信息
	//添加顶点，更新边信息
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			//graph.AddVertex(anTemp[i * MAX_COL + j]);
			UpdateArc(graph, i, j);
		}
	}
}

