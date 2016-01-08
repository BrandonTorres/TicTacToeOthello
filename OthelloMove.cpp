#include <iostream>
#include "OthelloMove.h"
#include <sstream>
#include <string>

int OthelloMove::mOutstanding = 0;

using namespace std;

OthelloMove::OthelloMove():mRow(-1),mCol(-1){}

OthelloMove::OthelloMove(int row, int col):mRow(row),mCol(col){}

GameMove& OthelloMove::operator=(const std::string& originalString) {
	if (isdigit(originalString[6])&&isdigit(originalString[8])){
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

OthelloMove::operator std::string() const{
	ostringstream o;
	o << "(" << this->mRow << "," << this->mCol << ")";
	return o.str();
}

bool OthelloMove::Equals(const GameMove &other) const{
	OthelloMove &move = (OthelloMove&)other;
	if (this->mRow == move.mRow && this->mCol == move.mCol)
		return true;
	else return false;

}
