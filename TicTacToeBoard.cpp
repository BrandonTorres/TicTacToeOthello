#include <iostream>
#include "TicTacToeBoard.h"
#include <sstream>
#include <string>

TicTacToeBoard::TicTacToeBoard()
{
	for (int i = 0; i<TBOARD_SIZE; i++)
	for (int j = 0; j<TBOARD_SIZE; j++)
		mBoard[i][j] = 0;
	mValue = 0;
	gameOver = false;
}

void TicTacToeBoard::ApplyMove(GameMove *m){
	TicTacToeMove *move = (TicTacToeMove*)m;
	mBoard[move->mRow][move->mCol]=mNextPlayer;
	mNextPlayer = mNextPlayer * -1;
	mHistory.push_back(move);
	mValue = 0;
	for (int i = 0; i < TBOARD_SIZE; i++){
		if ((mBoard[i][0] == mBoard[i][1] && mBoard[i][0] == mBoard[i][2]) && mBoard[i][1] != 0){
			gameOver = true;
			mValue = mNextPlayer * -1;
		}
		else if (mBoard[0][i] == mBoard[1][i] && mBoard[0][i] == mBoard[2][i] && mBoard[1][i] != 0){
			gameOver = true;
			mValue = mNextPlayer * -1;
		}
		else if ((mBoard[0][0] == mBoard[1][1] && mBoard[0][0] == mBoard[2][2]) && mBoard[1][1] != 0){
			gameOver = true;
			mValue = mNextPlayer * -1;
		}
		else if ((mBoard[0][2] == mBoard[1][1] && mBoard[2][0] == mBoard[0][2]) && mBoard[1][1] != 0){
			gameOver = true;
			mValue = mNextPlayer * -1;
		}
	}	
}

void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const{
	for (int row = 0; row<TBOARD_SIZE; row++){
		for (int col = 0; col<TBOARD_SIZE; col++){
				if (mBoard[row][col] == 0){
					TicTacToeMove *move = (TicTacToeMove*)this->CreateMove();
					*move = TicTacToeMove(row, col);
					list->push_back(move);
				}
					
		}
	}
}

void TicTacToeBoard::UndoLastMove(){
	TicTacToeMove *undoMove = (TicTacToeMove*)mHistory.back();
	mHistory.pop_back();
	mBoard[undoMove->mRow][undoMove->mCol] = 0;
	mNextPlayer = mNextPlayer*-1;
	mValue = 0;
	for (int i = 0; i < TBOARD_SIZE; i++)
	for (int j = 0; j < TBOARD_SIZE; j++)
		mValue = mValue + mBoard[i][j];
	delete undoMove;


}