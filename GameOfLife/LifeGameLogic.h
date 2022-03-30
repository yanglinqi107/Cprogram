#pragma once
#include "Cell.h"
#include "global.h"

class LifeGameLogic
{
private:
	//计算某细胞周围的活细胞数量
	int CanculateLivingCell(Cell** cells, int nRow, int nCol);

	//根据该细胞周围活细胞的数量判断该细胞的生命演化
	bool JudgeCellStatus(int count, bool statusNow);

public:
	//细胞演化一次后的情况
	void CellEvolution(Cell** cells);
};
