#pragma once
#include "Cell.h"
#include "global.h"

//���Ʋ�&�߼���
class LifeGameControl
{
public:
	LifeGameControl();
	~LifeGameControl();

	//��ȡĳ����ϸ��������״̬
	bool GetCellStatus(int nRow, int nCol);		
	//����ĳ����ϸ��������״̬
	void SetCellStatus(int nRow, int nCol);
	//��Cells��״̬ȫ����Ϊfalse
	void Clear();
	//�������Cells��״̬
	void ChangeCellsRand();
	//ϸ��һ���ݻ�
	void CellEvolution();
protected:
	Cell** cells = new Cell * [MAX_ROW];
};

