#ifndef SUDOKU_H
#define SUDOKU_H

/* Function to load a board from an input stream */ 
void load_board(const char *filename, char board[9][9]);

/*Function to display a sudoku board to the screen */
void display_board(const char board[9][9]);

/* Boolean function to check whether all cells are occupied by digits.
   Returns true only if all cells are occupied by digits.  */
bool is_complete(const char board[9][9]);

/*Boolean function to put a digit in a given cell in the matrix.
  Returns false and leaves board unaltered if move is invalid.
  Returns true and updates board if position i svalid. */
bool make_move(char position[3], char digit, char board[9][9]);

/*Boolean function which outputs a two dimensional character array to a file.
  Returns true only if the file was successfully written. */
bool save_board(const char *filename, char board[9][9]);

/*Recursive boolean function which solves the sudoku puzzle.
  Returns true and populates the board if a solution is found.                                                      
  Otherwise, returns false and leaves the board unaltered.*/
bool solve_board(char board[9][9]);

/* Function that counts the number of iterations required to complete a given sudoku. 
   Used to measure the difficulty level of the sudoku.*/
void counter(char board[9][9]);

#endif
