#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  
  cout << "====================== Question 1 ======================" << endl << endl;
  /*Test to check the function is_complete with a incomplete board*/
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  /*Test to check the function is_complete with a complete board. */
  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  
  cout << "====================== Question 2 ======================" << endl << endl;
  /*Tests on the make_move function.*/
  load_board("easy.dat", board);

  /* Positive test: 
     No repeating digit in the same row or column and the current space is not occupied. */
  cout << "Putting '8' into I8 is ";
  if (!make_move("I8", '8', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  /* Negative test: 
     Current space is occupied. */
  cout << "Putting '8' into B5 is ";
  if (!make_move("B5", '8', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);	

  /* Negative test: 
     Current space is not occupied but there is a repeating digit in the same row. */
  cout << "Putting '2' into B6 is ";
  if (!make_move("B6", '2', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  /* Negative test: 
     Current space is not occupied but there is a repeating digit in the same column. */
  cout << "Putting '3' into C7 is ";
  if (!make_move("C7", '3', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  /* Negative test: 
     Current space is not occupied but there is a repeating digit in the same square. */
  cout << "Putting '6' into F3 is ";
  if (!make_move("F3", '6', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  char boardcopy[9][9];
  if (save_board("easy-copy.dat", board)){
    cout << "Save board to 'easy-copy.dat' successful." << endl;
    load_board("easy-copy.dat", boardcopy);
    display_board(boardcopy);
  }
  else
    cout << "Save board failed." << endl;
  cout << endl;
  
  
  cout << "====================== Question 4 ======================" << endl << endl;
  /*Test for the load_board function using the easy board.*/
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  /*Test for the load_board function using the medium difficulty board. */
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;



  cout << "====================== Question 5 ======================" << endl << endl;

  /*Test whether the input boards can be solved and
    find out the number of iterations taken to solve Mystery 1, 2 and 3 boards.*/
  load_board("mystery1.dat", board);
  counter(board);
  load_board("mystery2.dat", board);
  counter(board);
  load_board("mystery3.dat", board);
  counter(board);
  
  return 0;
}
