#include "pch.h"
#include "LifeGameLogic.h"


void LifeGameLogic::CellEvolution(Cell** cells)
{
	Cell** cellNow = new Cell * [MAX_ROW];
	for (int i = 0; i < MAX_ROW; ++i)
	{
		cellNow[i] = new Cell[MAX_COL];
	}
	//Cell cellNow[MAX_ROW][MAX_COL];
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			bool status = cells[i][j].IsLive();
			cellNow[i][j].setStatus(status);
		}
	}
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			//MessageBox(NULL, _T("ÑÝ»¯º¯Êý"), _T("´íÎó"), NULL);
			bool statusNow = cellNow[i][j].IsLive();
			int count = CanculateLivingCell(cellNow, i, j);
			bool statusNext = JudgeCellStatus(count, statusNow);
			cells[i][j].setStatus(statusNext);			
		}
	}
	
	for (int i = 0; i < MAX_ROW; ++i)
	{
		if (!cellNow[i])
		{
			delete[] cellNow[i];
		}
	}
}

int LifeGameLogic::CanculateLivingCell(Cell** cells, int nRow, int nCol)
{
	int count = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			int row = (nRow + i) % MAX_ROW;
			int col = (nCol + j) % MAX_COL;
			if (row < 0)
			{
				row += MAX_ROW;
			}
			if (col < 0)
			{
				col += MAX_COL;
			}
			//MessageBox(NULL, _T("¼ÆËãº¯Êý"), _T("´íÎó"), NULL);
			bool status = cells[row][col].IsLive();
			if (status)
			{
				++count;
			}
		}
	}
	return count;
}

bool LifeGameLogic::JudgeCellStatus(int count, bool statusNow)
{
	/*switch (count)
	{
	case 1: return false;
	case 2:return statusNow;
	case 3:return true;
	case 4:
	}*/
	if (count == 2)
	{
		return statusNow;
	}
	if (count == 3)
	{
		return true;
	}
	return false;
}


