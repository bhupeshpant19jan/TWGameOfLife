#include "stdafx.h"
#include "GameOfLife.h"
#include "iostream"
#include "stdlib.h"
using namespace std;

CGameOfLife::CGameOfLife():MAX_SIZE(10), m_ROW_SIZE(0),m_COLUMN_SIZE(0)
{
	for(auto row = 0; row < MAX_SIZE ; ++row)
		for(auto column = 0; column < MAX_SIZE; ++column)
			m_PatternArray[row][column] = -1;
}

int CGameOfLife::Start()
{
	TakeInputPattern();
	//TakeDummyInputPattern();
	DisplayPattern();
	AnalyseAndGenerateNextLifePattern();
	return 0;		
}

void CGameOfLife::TakeDummyInputPattern()
{
	m_ROW_SIZE = 4;
	m_COLUMN_SIZE = 4;
	int tempArray[4][4] = {{0,0,1,0},{0,0,1,1},{0,0,0,0},{1,1,0,0}};
	for(auto row = 0; row < 4; ++row)
	{
		for(auto column = 0; column < 4; ++column)
		{
			m_PatternArray[row][column] = tempArray[row][column];
		}
	}
}
void CGameOfLife::DisplayPattern()
{
	system("cls");
	for(auto row = 0; row < m_ROW_SIZE; ++row)
	{
		for(auto column = 0; column < m_COLUMN_SIZE; ++column)
		{
			if (1 == m_PatternArray[row][column])
				cout<<"X";
			else
				cout<<"-";
			cout<<"\t";
		}
		cout<<endl;
	}
}

bool CGameOfLife::validateInput(int &p_iInputVal)
{
	static short s_sRetryCount = 0;
	//if (p_iInputVal != 120 || p_iInputVal != 88 ||p_iInputVal != 45 )
	if (p_iInputVal != 0 && p_iInputVal != 1)
	{
		++s_sRetryCount;
		if (s_sRetryCount > 3)
		{
			cout<<"All attempts wasted. Default value as '0' will be considered as input."<<endl;
			p_iInputVal = 0;
			return true;
		}
		cout<<"Please provide the proper input in '0' or '1' format only. Enter again <Retry attempt = "<<s_sRetryCount<<">"<<endl;
		//p_iInputVal =  getchar();
		cin>>p_iInputVal;
		validateInput(p_iInputVal);
	}
	return true;
}
int CGameOfLife::TakeInputPattern()
{
	cout<<"Give the details of pattern size."<<endl;
	cout<<"Size of row = ";
	cin>>m_ROW_SIZE;
	cout<<"Size of Column = ";
	cin>>m_COLUMN_SIZE;
	cout<<"Enter the pattern in one input per line. It should be in (0/1), for(-/X) form only."<<endl;
	//Here we will write the code for dynamic array
	for(auto row = 0; row < m_ROW_SIZE; ++row)
	{
		for(auto column = 0; column < m_COLUMN_SIZE; ++column)
		{
			//int l_cInputUnit =  getchar();
			//string inputArray;
			auto l_cInputUnit = 0;
			static int input = 0;
			cout<<"Input "<<++input<<" = ";
			cin>>l_cInputUnit;
			if (validateInput(l_cInputUnit))
			{		
				m_PatternArray[row][column] = l_cInputUnit;
				//if(0 == strcmp("X", &l_cInputUnit) || 0 == strcmp("x", &l_cInputUnit))

				/*if (l_cInputUnit == 45)
				{
				m_PatternArray[row][column] = 0;
				}
				else
				{
				m_PatternArray[row][column] = 1;
				}*/
			}
		}
	}
	return 1;
}

int CGameOfLife::AnalyseAndGenerateNextLifePattern()
{
	auto l_iAdjacentAliveCellsCount = 0;
	for(auto row = 0; row < m_ROW_SIZE; ++row)
	{
		for(auto column = 0; column < m_COLUMN_SIZE; ++column)
		{
			l_iAdjacentAliveCellsCount = GetAliveNeighbourCount(row, column);
			
			if (GetCellNextLifeState(m_PatternArray[row][column] , l_iAdjacentAliveCellsCount))
			{
				cout<<"X";
			}
			else
			{
				cout<<"-";
			}
			cout<<"\t";
		}
		cout<<endl;
	}
	return 1;
}

int CGameOfLife::GetCellNextLifeState(int p_iCurrentState, int p_iAdjacentAliveCellsCount)
{
	//if(p_iAdjacentAliveCellsCount == 2 || p_iAdjacentAliveCellsCount ==)
	return 1;

}
int CGameOfLife::GetAliveNeighbourCount(int p_pRowIndex, int p_pColumnIndex)
{
	auto l_bRowDecrement    = false;
	auto l_bRowIncrement    = false;
	auto l_bCoulmnDecrement = false;
	auto l_bColumnIncrement = false;
	auto l_iAliveNeighbourCount = 0;

	if(p_pRowIndex - 1 > -1) l_bRowDecrement = true;
	if(p_pRowIndex + 1 < m_ROW_SIZE) l_bRowIncrement = true;

	if(p_pColumnIndex - 1 > -1) l_bCoulmnDecrement = true;
	if(p_pColumnIndex + 1 < m_COLUMN_SIZE) l_bColumnIncrement = true;

	//Checking middle row.
	//l_iAliveNeighbourCount += m_PatternArray[p_pRowIndex][p_pColumnIndex];

	if(l_bRowDecrement)
		l_iAliveNeighbourCount += m_PatternArray[p_pRowIndex - 1][p_pColumnIndex];

	if(l_bRowIncrement)
		l_iAliveNeighbourCount += m_PatternArray[p_pRowIndex + 1][p_pColumnIndex];

	//Checking previous row
	if(l_bCoulmnDecrement)
	{
		l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex][p_pColumnIndex - 1];

		if(l_bRowDecrement)
			l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex - 1][p_pColumnIndex - 1];

		if(l_bRowIncrement)
			l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex + 1][p_pColumnIndex - 1];
	}

	//Checking next row
	if(l_bColumnIncrement)
	{
		l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex][p_pColumnIndex + 1];

		if(l_bRowDecrement)
			l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex - 1][p_pColumnIndex + 1];

		if(l_bRowIncrement)
			l_iAliveNeighbourCount +=  m_PatternArray[p_pRowIndex + 1][p_pColumnIndex + 1];
	}

	return l_iAliveNeighbourCount;
}