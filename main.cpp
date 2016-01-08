#include "GameExceptions.h"
#include "GameBoard.h"
#include "GameView.h"
#include "GameMove.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OThelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board; // the state of the game board
   GameView *v; // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   string gameSelection;
   vector<GameMove *> possMoves; // a holder for possible moves
   bool validMove = false;
   bool gameSelected = false;
   int undoAmount = 0;
   board = new TicTacToeBoard();
   v = new TicTacToeView(board);
   while (!gameSelected){
	   cout << "Would you like to play othello or tictactoe"<<endl;
	   getline(cin, gameSelection);
	   if (gameSelection == "othello"){
		   board = new OthelloBoard();
		   v = new OthelloView(board);
		   gameSelected = true;
	   }
	   if (gameSelection == "tictactoe"){
		   board = new TicTacToeBoard();
		   v = new TicTacToeView(board);
		   gameSelected = true;
	   }
		  
   }

   // Main loop
   do {
	  // Print the game board using the OthelloView object

      // Print all possible moves

      // Ask to input a command
	       cout << *v;
		   board->GetPossibleMoves(&possMoves);
		   for(int i=0;i<possMoves.size();i++){
				cout<<(string)*possMoves.at(i)<<" ";
				if(i==15)
					cout<<endl;
		   }
		   cout << endl;
		   
		   cout << "Please enter a command " << endl
		   << "1. move (r,c)" << endl
		   << "2. undo n" << endl
		   << "3. showValue" << endl
		   << "4. showHistory" << endl
		   << "5. quit" << endl;
		   getline(cin, userInput);
	       
		   if  (userInput== "quit")
			   break;
		   else if (userInput.substr(0, 5) == "undo "){
			   undoAmount=userInput.at(5)-'0';
			   if(undoAmount>board->GetMoveCount())
				   cout<<"Undo amount is larger than moves made"<<endl;
			   while(undoAmount && undoAmount<=board->GetMoveCount() ){
					undoAmount--;
					board->UndoLastMove();
			   }
		   }
		   else if (userInput == "showValue")
			   cout<<board->GetValue()<<endl;
		   else if (userInput == "showHistory"){
			   const vector<GameMove *> *history=board->GetMoveHistory();
			   for(int i=0;i<board->GetMoveCount();i++)
			   if (gameSelection == "othello"){
				   if (i % 2 == 1)
					   cout << "White Move: " << (string)*history->at(i) << endl;
				   else
					   cout << "Black Move: " << (string)*history->at(i) << endl;
			   }
			   else{
				   if (i % 2 == 1)
					   cout << "O Move: " << (string)*history->at(i) << endl;
				   else
					   cout << "X Move: " << (string)*history->at(i) << endl;
			   }
		   }
		   else if (userInput.substr(0, 5) == "move ")
		   {
			   GameMove *currentMove = board->CreateMove();
			   try{
				   *currentMove = userInput;
				   for (int i = 0; i < possMoves.size(); i++)
					 if (*possMoves.at(i) == *currentMove)
					 validMove = true;
				   if(!validMove)
					   throw OthelloException("Not a valid move");
				   board->ApplyMove(currentMove);
			   
			   }
			   catch(OthelloException &err){
				   delete currentMove;
				   cout<<err.GetMessage();
				}
		   }
		   else
			   cout << "Please enter a valid command"<<endl;
	  
      // Command loop:
         // move (r,c)
         // undo n
         // showValue
         // showHistory
         // quit
		   for (int i = 0; i < possMoves.size(); i++)
				   delete possMoves.at(i);  
		   possMoves.clear();
		   cout<<endl;
		   validMove = false;
   } while (!board->IsFinished()); 
   if (gameSelection == "tictactoe"){
	   if (board->GetNextPlayer() == -1)
		   cout << "X ";
	   else
		   cout << "O ";
	   cout << "is the winner!!";
   }
	   

}