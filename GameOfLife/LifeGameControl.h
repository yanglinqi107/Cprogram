#pragma once
#include "Cell.h"
#include "global.h"

//控制层&逻辑层
class LifeGameControl
{
public:
	LifeGameControl();
	~LifeGameControl();

	//获取某行列细胞的生命状态
	bool GetCellStatus(int nRow, int nCol);		
	//设置某行列细胞的生命状态
	void SetCellStatus(int nRow, int nCol);
	//将Cells的状态全部改为false
	void Clear();
	//随机更改Cells的状态
	void ChangeCellsRand();
	//细胞一次演化
	void CellEvolution();
protected:
	Cell** cells = new Cell * [MAX_ROW];
};

