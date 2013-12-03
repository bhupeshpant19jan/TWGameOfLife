#include "stdafx.h"

class CGameOfLife
{
	//int *m_pPatterArray; 
	const int MAX_SIZE;
	int m_PatternArray[10][10];
	int m_ROW_SIZE;
	int m_COLUMN_SIZE;
public:
	CGameOfLife();
	int Start();
private:
	void DisplayPattern();	
	int TakeInputPattern();
	int AnalyseAndGenerateNextLifePattern();
	int GetAliveNeighbourCount(int p_pRowIndex, int p_pColumnIndex);
	bool validateInput(int &p_iInputVal);
	void TakeDummyInputPattern();
	int GetCellNextLifeState(int p_iCurrentState, int p_iAdjacentAliveCellsCount);
};
