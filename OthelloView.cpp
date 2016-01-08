#include <iostream>
#include "OthelloView.h"

void OthelloView:: PrintBoard(std::ostream &s)const {
	int rows=BOARD_SIZE;
	int columns=BOARD_SIZE;
	s << "  0  1  2  3  4  5  6  7 ";
	for (int bRow = 0; bRow<rows; bRow++)
    {
		s << std::endl;
		s << bRow;
		for (int bCol = 0; bCol < columns; bCol++)
		{
			if (mOthelloBoard->mBoard[bRow][bCol] == OthelloBoard::BLACK)
				s << " B ";
			else if (mOthelloBoard->mBoard[bRow][bCol] == OthelloBoard::WHITE)
				s << " W ";
			else
				s << " . ";
		}  
	} 
	s << std::endl;
	if (mOthelloBoard->GetNextPlayer() == -1)
		s << "White Moves:"<<std::endl;
	else
		s << "Black:" << std::endl;
	return;
}



