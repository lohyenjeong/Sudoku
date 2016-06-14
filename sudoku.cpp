#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h" 
#include <time.h> 

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}


/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}


/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}


/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* Boolean function to check whether all cells in the given board are occupied by digits.
   Returns true only if all positions are occupied by digits.  */  
bool is_complete(const char board[9][9]) {
  int row = 0;  
  while(row < 9) {
    for(int column = 0; column < 9; column++){
      if(!isdigit(board[row][column]))
	return false;
    } 
    row++;
  }
  return true; 
}


/* Boolean function that checks whether an input digit has 
   repeating digits in the corresponding row and column.
   Returns true if there is no repeating digit. */
bool verify_row_column(const char board[9][9], int row, int column, char digit){
  for(int i = 0; i <9; i++) {
    if(board[row][i] == digit)
      return false;
      }
  for(int i = 0; i <9; i++) {
    if(board[i][column] == digit)
      return false;
  }
  return true; 
}


/* Boolean function that checks whether an input digit has 
   repeating digits in the corresponding 3*3 sub-square.
   Returns true if there is no repeating digit. */
bool verify_sub_square(const char board [9][9], int row, int column, char digit){ 
  int sub_square_r = row/3;
  int sub_square_c = column/ 3; 

  for(int j=sub_square_r*3; j < (sub_square_r*3 + 3); j++){
    for(int i=sub_square_c*3; i < (sub_square_c*3 + 3) ; i++){
	if(board[j][i] == digit)
	  return false;
      }
    }
  return true;
}


/* Boolean function to put a digit in a given position in the matrix.
   Returns false and leave the board unaltered if move is invalid.
   Returns true and updates board if position is valid. */
bool make_move(char position[2], char digit, char board[9][9]) {
  int row = 0, column = 0;
  row = (int)position[0] - 'A';  
  column = position[1] - '0' - 1;
 
  if((!isdigit(board[row][column])) && 
     verify_row_column(board, row, column, digit) && 
     verify_sub_square(board, row, column, digit)){
    board[row][column] = digit;   
    return true;
  }
  else {
    return false;
  }
}


/*Boolean function which outputs a two dimensional chacrter board to a file.
  Returns true only if the file was successfully written. */
bool save_board(const char *filename, char board[9][9]){
  ofstream out(filename);
  if(!out){
    cout << "Failed to create file" << endl; 
    assert(out);
  }
 else{
    for(int j = 0; j < 9; j++){
      for(int i = 0; i < 9; i++){
	out.put(board[j][i]);
      }
      out.put('\n');
    }
   if(!out)
	cout <<"Failed to write file." << endl;    
    out.close();
    return true;
  }
  return false; 
}


/*Serves two functions: 
  1) Skip over the digits and test only the blanks.
  2) Works as the base case. Returns true when there are no blanks left. */
bool find_unsolved_spaces(char board[9][9], int &row, int &column){
  for(row = 0; row < 9; row ++){
    for(column = 0; column < 9; column++){
      if(board[row][column] == '.')
	 return true;
    }
  }
  return false;
}


/*Recursive boolean function which solves the sudoku puzzle.
  Returns true and populates the board if a solution is found.
  Otherwise, returns false and leaves the board unaltered.*/
bool solve_board(char board[9][9]){
  int row, column;
  
  /* Skips over solved spaces and acts as a base case. */
  if(!find_unsolved_spaces(board, row, column))
    return true;
  
  /*Iterate test_no from 1 to 9 for each cell and test for a solution recursively. */
  for(char test_no = '1'; test_no <= '9'; test_no++){
    if((verify_row_column(board, row, column, test_no)) &&
       (verify_sub_square(board, row, column, test_no))){
      board[row][column] = test_no;
      if(solve_board(board))
	 return true;
      board[row][column] = '.';
    }
  }
  return false;
}


/* Bool recursive function that overloads the solve_board function 
   to count the number of iterations required to solve a board. 
   Returns the number through the int reference count. */
bool solve_board(char board[9][9], int &count){
  int row, column;  
  ++count;

  /* Skips over solved spaces and acts as a base case. */
  if(!find_unsolved_spaces(board, row, column))
    return true;

  /*Iterate test_no from 1 to 9 for each cell and test for a solution recursively. */
  for(char test_no = '1'; test_no <= '9'; test_no++){
    if((verify_row_column(board, row, column, test_no)) &&
       (verify_sub_square(board, row, column, test_no))){  
      board[row][column] = test_no;
      if(solve_board(board, count)){
	 return true;
      }
      board[row][column] = '.';
    }
  }
  return false;
}


/*Function that initiates a helper function to count the number of iterations 
  involved in solving a sudoku. 
  Prints the number of iterations to the output screen.*/
void counter(char board[9][9]){
  int count = 0;
  if(solve_board(board, count)){
    cout << "The number of iterations it takes to solve the puzzle is: " << count  << ".\n" <<endl; 
  }
  else
    cout <<"The board is not solvable. \n" <<endl;
}
