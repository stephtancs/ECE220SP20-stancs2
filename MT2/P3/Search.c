#include <stdio.h>
#include "Search.h"

//Your implementation of this function must be recursive
//return 1 if item found in data; otherwise, return 0
int Search(int item, int data[ROW][COL], int start_row, int end_row, int start_col, int end_col){
    //Your code starts here
  if(start_row > end_row || start_col > end_col)
    return 0;

  for(int j = start_col; j <= end_col; j++){
    if(item < data[start_row][j])
      return Search(item, data, start_row, end_row, start_col, j-1);
    else if(item==data[start_row][j])
      return 1;
  }

  for(int i = start_row; i <= end_row; i++){
    if(item < data[i][start_col])
      return Search(item, data, start_row, i-1, start_col, end_col);
    else if(item==data[i][start_col])
      return 1;
  }

  for(int j = start_col; j <= end_col; j++){
    if(item > data[end_row][j])
      return Search(item, data, start_row, end_row, j+1, end_col);
    else if(item==data[end_row][j])
      return 1;
  }

  for(int i = start_row; i <= end_row; i++){
    if(item > data[i][end_col])
      return Search(item, data, start_row, i+1, start_col, end_col);
    else if(item==data[i][end_col])
      return 1;
  }

  return 0;

}


