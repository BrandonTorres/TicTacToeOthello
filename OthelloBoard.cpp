#include <iostream>
#include "OthelloBoard.h"
#include <sstream>
#include <string>

OthelloBoard::OthelloBoard()
{
	for (int i = 0; i<BOARD_SIZE; i++)
		for (int j = 0; j<BOARD_SIZE; j++)
			mBoard[i][j] = 0;
	mBoard[3][3] = WHITE;
	mBoard[4][4] = WHITE;
	mBoard[3][4] = BLACK;
	mBoard[4][3] = BLACK;
	mNextPlayer = BLACK;
	mValue = 0;
	mPassCount = 0;
}

void OthelloBoard::ApplyMove(GameMove *m){
	OthelloMove *move = (OthelloMove*)m;
	int flipCounter = 0;
	if (move->mCol == -1 && move->mRow==-1)
		mPassCount++;
	else{
		mPassCount = 0;
		mBoard[move->mRow][move->mCol] = mNextPlayer;
		for (int i = -1; i <= 1; i++){	
			int rcount = 0, ccount = 0;
			for (int j = -1; j <= 1; j++){
				flipCounter = 0;
				ccount = i;
				rcount = j;
				while (mBoard[move->mRow + rcount][move->mCol + ccount] == (mBoard[move->mRow][move->mCol] * -1)){
					flipCounter++;
					ccount = ccount + i;
					rcount = rcount + j;
					while (mBoard[move->mRow + rcount][move->mCol + ccount] == mBoard[move->mRow][move->mCol]){
						if (rcount == 0 && ccount == 0){
							move->flip.colDelta = i;
							move->flip.rowDelta = j;
							move->flip.switched = flipCounter;
							move->AddFlipSet(move->flip);
							break;
						}
						rcount = rcount - j;
						ccount = ccount - i;
						mBoard[move->mRow + rcount][move->mCol + ccount] = mNextPlayer;
					}
				}
			}
		}
	}
	mNextPlayer = mNextPlayer * -1;
	mHistory.push_back(move);
	mValue=0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			mValue = mValue + mBoard[i][j];
}

void OthelloBoard::GetPossibleMoves(std::vector<GameMove *> *list) const{
	bool pass=false;
	for(int row=0;row<8;row++){
		for(int col=0;col<8;col++){
			pass=false;
			for (int i = -1; i <= 1; i++){
				int rcount = 0, ccount = 0;
				for (int j = -1; j <= 1; j++){
					ccount = i;
					rcount = j;
					if(mBoard[row][col] != 0){
						break;
					}
					while (mBoard[row + rcount][col + ccount] == mNextPlayer*-1){
						ccount = ccount + i;
						rcount = rcount + j;
						if (mBoard[row + rcount][col + ccount] == mNextPlayer*1){
							if(list->size()!=0)
								if(OthelloMove(row,col)==*list->back()){
									pass=true;
									break;
								}
							OthelloMove *move= (OthelloMove*)this->CreateMove();
							*move=OthelloMove(row,col);
								list->push_back(move);
						}
					}
					if(pass)
						break;
				}
				if(pass)
					break;	
			}		
		}
	}
	if(list->size()==0){
		OthelloMove *move = (OthelloMove*)this->CreateMove();
		*move=OthelloMove(-1,-1);
		list->push_back(move);
	}
}

void OthelloBoard::UndoLastMove(){
	OthelloMove *undoMove = (OthelloMove*)mHistory.back();
	mHistory.pop_back();
	mBoard[undoMove->mRow][undoMove->mCol]=0;
	mNextPlayer=mNextPlayer*-1;
	for(int i=undoMove->mFlips.size(); i > 0 ; i--){
		OthelloMove::FlipSet undoFlip= undoMove->mFlips.back();
		undoMove->mFlips.pop_back();
		while(undoFlip.switched){
			if(mBoard[undoMove->mRow+undoFlip.switched*undoFlip.rowDelta][undoMove->mCol+undoFlip.switched*undoFlip.colDelta]==mNextPlayer)
			mBoard[undoMove->mRow+undoFlip.switched*undoFlip.rowDelta][undoMove->mCol+undoFlip.switched*undoFlip.colDelta]=
				mBoard[undoMove->mRow+undoFlip.switched*undoFlip.rowDelta][undoMove->mCol+undoFlip.switched*undoFlip.colDelta]*-1;
			undoFlip.switched--;
		}
	}
	if(undoMove->mRow==-1 && undoMove->mCol==-1)
		mPassCount--;
	mValue=0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			mValue = mValue + mBoard[i][j];
	delete undoMove;


}