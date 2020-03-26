#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// mp7: this function solves a pre-started sudoku table accurately.
// partners: stancs2, asanag2, anudeep2
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  //loop through by keeping row constant and varying column index to check entire row
  for(int col = 0; col<9; col++){
    if(val==sudoku[i][col])
      return 1;
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  //loop through by keeping column constant and varying row index to check entire column
  for(int row=0; row<9; row++){
    if(val==sudoku[row][j])
      return 1;
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  
  //define 3*3 portions of the puzzle
  int rowDivider = i/3, colDivider = j/3;
  
  //loop through every value
  for(int col = 0; col < 3; col++){
    for(int row = 0; row < 3; row++){
      if (val==sudoku[row+rowDivider*3][col+colDivider*3])
	return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  //checks validity based on whether or not the number exists in the three possible locations
  int theBoxByRoddyRich = is_val_in_3x3_zone(val, i, j, sudoku);
  int row = is_val_in_row(val, i, sudoku);
  int column = is_val_in_col(val, j, sudoku);

  if(theBoxByRoddyRich || row || column)
    return 0;
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

  //loops through and finds empty space
  //loops through possible values for the space and tests them
  //uses this method recursively until every space is full and valid
  for(int row = 0; row < 9; row++){
    for(int col = 0; col < 9; col++){
      if(sudoku[row][col]==0){
	for(int num = 1; num<=9; num++){
	  if(is_val_valid(num, row, col, sudoku)==1){
	    sudoku[row][col]=num;
	    if(solve_sudoku(sudoku)){
	      return 1;
	    }
	    sudoku[row][col]=0;
	  }
	}
	return 0;
      }
    }
  }
  return 1;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





