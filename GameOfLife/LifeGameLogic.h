#pragma once
#include "Cell.h"
#include "global.h"

class LifeGameLogic
{
private:
	//����ĳϸ����Χ�Ļ�ϸ������
	int CanculateLivingCell(Cell** cells, int nRow, int nCol);

	//���ݸ�ϸ����Χ��ϸ���������жϸ�ϸ���������ݻ�
	bool JudgeCellStatus(int count, bool statusNow);

public:
	//ϸ���ݻ�һ�κ�����
	void CellEvolution(Cell** cells);
};
