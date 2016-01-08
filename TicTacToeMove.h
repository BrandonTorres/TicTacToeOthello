#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>
/*
An OthelloMove encapsulates a single potential move on an OthelloBoard. It
is represented internally by a row and column, both 0-based.
*/
class TicTacToeMove : public GameMove {
private:
	int mRow, mCol;

	friend class TicTacToeBoard;

	TicTacToeMove();
	
	TicTacToeMove(int row, int col);

	static int mOutstanding;


public:
	/*
	static void* operator new(std::size_t sz) {
	mOutstanding++;
	std::cout << "operator new: " << mOutstanding << " moves outstanding" << std::endl;
	return ::operator new(sz);
	}

	static void operator delete(void* ptr, std::size_t sz) {
	mOutstanding--;
	std::cout << "operator delete: " << mOutstanding << " moves oustanding" << std::endl;
	::operator delete(ptr);
	}*/
	virtual ~TicTacToeMove() {}


	virtual GameMove& operator=(const std::string &);

	virtual bool Equals(const GameMove &other) const;

	operator std::string() const;

	inline bool IsPass() const { return mRow == -1 && mCol == -1; }

	virtual GameMove *Clone() const {
		return new TicTacToeMove(*this);
	}
};

//int OthelloMove::mOutstanding = 0;
#endif