#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int TBOARD_SIZE = 3;

class TicTacToeBoard : public GameBoard {

public:
	enum Player { EMPTY = 0, X = 1, O = -1 };

	// Default constructor initializes the board to its starting "new game" state
	TicTacToeBoard();

	virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

	virtual void ApplyMove(GameMove *move);

	virtual void UndoLastMove();

	virtual GameMove *CreateMove() const { return new TicTacToeMove; }

	inline static bool InBounds(int row, int col) { return row >= 0 && row < TBOARD_SIZE && col >= 0 && col < TBOARD_SIZE; }

	// Returns true if the game is finished.
	virtual bool IsFinished() const {
		if (mHistory.size() == 9)
			return true;
		else if(gameOver)
			return true;
		else return false;
	}

private:
	friend class TicTacToeView;
	bool gameOver;

	char mBoard[TBOARD_SIZE][TBOARD_SIZE];
};
#endif