#include "pch.h"
#include "LifeGameControl.h"
#include "LifeGameLogic.h"

LifeGameControl::LifeGameControl()
{
	for (int i = 0; i < MAX_ROW; ++i)
	{
		cells[i] = new Cell[MAX_COL];
	}
}

LifeGameControl::~LifeGameControl()
{
	for (int i = 0; i < MAX_ROW; ++i)
	{
		if (!cells[i])
		{
			delete[] cells[i];
		}
	}
}

bool LifeGameControl::GetCellStatus(int nRow, int nCol)
{
	bool status = cells[nRow][nCol].IsLive();
	return status;
}

void LifeGameControl::SetCellStatus(int nRow, int nCol)
{
	cells[nRow][nCol].changeStatus();
}

void LifeGameControl::Clear()
{
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			cells[i][j].setStatus(false);
		}
	}
}

void LifeGameControl::ChangeCellsRand()
{
	//ÉèÖÃÖÖ×Ó
	srand((int)time(NULL));

	for (int i = 0; i < MAX_COL * MAX_ROW / 2; ++i)
	{
		int nRow = rand() % MAX_ROW;
		int nCol = rand() % MAX_COL;

		cells[nRow][nCol].changeStatus();
	}
}

void LifeGameControl::CellEvolution()
{
	LifeGameLogic LGameL;
	LGameL.CellEvolution(cells);
}



