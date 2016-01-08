#include <iostream>
#include "TicTacToeMove.h"
#include <sstream>
#include <string>

int TicTacToeMove::mOutstanding = 0;

using namespace std;

TicTacToeMove::TicTacToeMove() :mRow(-1), mCol(-1){}

TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col){}

GameMove& TicTacToeMove::operator=(const std::string& originalString) {
	if (isdigit(originalString[6]) && isdigit(originalString[8])){
		this->mRow = originalString[6] - '0';
		this->mCol = originalString[8] - '0';
	}
	else if (originalString == "move pass"){
		this->mRow = -1;
		this->mCol = -1;
	}
	else{
		this->mRow = -2;
		this->mCol = -2;
	}
	return *this;
}

TicTacToeMove::operator std::string() const{
	ostringstream o;
	o << "(" << this->mRow << "," << this->mCol << ")";
	return o.str();
}

bool TicTacToeMove::Equals(const GameMove &other) const{
	TicTacToeMove &move = (TicTacToeMove&)other;
	if (this->mRow == move.mRow && this->mCol == move.mCol)
		return true;
	else return false;

}
