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
	//��ʼ��������Ϣ
	int anTemp[MAX_VERTEX_NUM];

	//���ɹ̶���ͼ
	for (int i = 0; i < MAX_PIC_NUM; ++i)
	{
		//�ظ���
		for (int j = 0; j < REPEAT_NUM; ++j)
		{
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}

	//��������
	srand((int)time(NULL));

	//���������ͼ�������֣����������ͼ
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int temp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = temp;
	}

	//��Ӷ��㣬���±���Ϣ
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

//���±�
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;

	//��������ڵ���ͨ
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

	//���ұ����ڵ���ͨ
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

	//���ϱ����ڵ���ͨ
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
	//���±����ڵ���ͨ
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
	//��ȡ�ڶ��������е�������
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
	//��ȡ�ڶ��������е�������
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	//���¶���
	graph.UpdateVertex(nIndex1, BLANK);
	graph.UpdateVertex(nIndex2, BLANK);

	//���±���Ϣ
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	//����ͼ��nV0�У���0�е�MAX_VERTEX_NUM�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < MAX_VERTEX_NUM; ++nVi)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			//���vi��·���У�����Ϊ��Ч����
			Vertex vi;
			vi.row = nVi / MAX_COL;
			vi.col = nVi % MAX_COL;
			AddVertex(vi);

			//�յ�������2���򵯳�vi
			if (m_nCornerNum > 2)
			{
				PopVertex();
				continue;
			}

			//���м䶥�㲻��nV1ʱ��������Ѱ��һ����������ͨ�Ķ���
			if (nVi != nV1)
			{
				//���м䶥�㲻Ϊ�գ���·����ͨ
				if (graph.GetVertex(nVi) != BLANK)
				{
					//����vi
					PopVertex();
					continue;
				}

				//���nVi��һ�������ĵ㣬���ж�nVi��nV1�Ƿ���ͨ
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			//���nVi==nV1,���Ѿ��ҵ�һ����ͨ·��
			else
			{
				return true;
			}
			//ȥ��ѹ���vi����AddVertex(vi)��Ӧ
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
	//��ȡ��������
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
	//��ȡ�������
	//int nVexNum = graph.GetVexnum();
	int v1 = 0; 
	int v2 = 0;
	int equalPicture = 0;
	Vertex vex1;

	//�ҵ���һ����Ϊ�յĵ�
	for (v1 = 0; v1 < MAX_VERTEX_NUM; ++v1)
	{
		if (graph.GetVertex(v1)!=BLANK)
		{
			//ѹ��v1��avPath��
			vex1.row = v1 / MAX_COL;
			vex1.col = v1 % MAX_COL;
			AddVertex(vex1);
			equalPicture = graph.GetVertex(v1);
			//�������һ������ͼƬ��ͬ��Ԫ��
			for (v2 = v1 + 1; v2 < MAX_VERTEX_NUM; ++v2)
			{
				if (equalPicture == graph.GetVertex(v2))
				{
					//�ж�v1��v2�Ƿ���ͨ
					if (SearchPath(graph, v1, v2))
					{
						return true;
					}
				}
			}
			//����v1����AddVertex(v1)��Ӧ
			PopVertex();
		}
	}
	return false;
}

void CGameLogic::ResetGraph(CGraph& graph)
{
	//��������������������������ֵ
	//��������
	srand((int)time(NULL));

	//���������ͼ�������֣����������ͼ
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int v1 = graph.GetVertex(nIndex1);
		int v2 = graph.GetVertex(nIndex2);
		graph.UpdateVertex(nIndex1, v2);
		graph.UpdateVertex(nIndex2, v1);
	}
	//���±���Ϣ
	//��Ӷ��㣬���±���Ϣ
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			//graph.AddVertex(anTemp[i * MAX_COL + j]);
			UpdateArc(graph, i, j);
		}
	}
}

