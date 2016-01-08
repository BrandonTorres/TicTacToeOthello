#include <iostream>
#include "TicTacToeView.h"

void TicTacToeView::PrintBoard(std::ostream &s)const {
	int rows = TBOARD_SIZE;
	int columns = TBOARD_SIZE;
	s << "  0  1  2 ";
	for (int bRow = 0; bRow<rows; bRow++)
	{
		s << std::endl;
		s << bRow;
		for (int bCol = 0; bCol < columns; bCol++)
		{
			if (mTicTacToeBoard->mBoard[bRow][bCol] == TicTacToeBoard::X)
				s << " X ";
			else if (mTicTacToeBoard->mBoard[bRow][bCol] == TicTacToeBoard::O)
				s << " O ";
			else
				s << " . ";
		}
	}
	s << std::endl;
	if (mTicTacToeBoard->GetNextPlayer() == -1)
		s << "O Move:" << std::endl;
	else
		s << "X Move:" << std::endl;

	return;
}