/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  //location -> #ofcols*row+col
  int liveNeighbors = 0,i,j;

  //loop through every section of 3 elements and report live neighbors within the area
  for(i = row-1; i<=row+1; i++){
    for(j = col-1; j<=col+1; j++){
      if(i>=0 && j>=0 && i<boardRowSize  && j<boardColSize)
	if(board[i*boardColSize+j]==1)
	  liveNeighbors++;
    }
  }
  if(board[row*boardColSize+col]==1)
    liveNeighbors--;
  return liveNeighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  //initialize all variables and a temporary board
  int boardSize = boardRowSize*boardColSize;
  int tempBoard[boardSize];
  int i,j,copy,liveNeighbors;

  //loops through every element, counts each elements live neighbors
  //if an element is equal to 0 and has 3 live neighbors, it is now 1
  //if an element is equal to 1 and has less than 2 or more than 3 live neighbors, it is now 0
  for(i=0; i<boardRowSize; i++){
    for(j=0; j<boardColSize; j++){
      liveNeighbors = countLiveNeighbor(board,boardRowSize,boardColSize,i,j);
      if(board[i*boardColSize+j]==0){
	if(liveNeighbors==3)
	  tempBoard[i*boardColSize+j]=1;
	else
	  tempBoard[i*boardColSize+j]=0;
      }
      if(board[i*boardColSize+j]==1){
	if(liveNeighbors<2||liveNeighbors>3)
	  tempBoard[i*boardColSize+j]=0;
	else
	  tempBoard[i*boardColSize+j]=1;
      }
    }
  }
  for(copy=0; copy<boardSize; copy++)
    board[copy]=tempBoard[copy];
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  //initialize all variables and temporary array
  int boardSize = boardRowSize*boardColSize;
  int tempBoard[boardSize];
  int copy, update;

  //copy all elements into a temporary board and use this to update the game board
  for(copy=0; copy<boardSize; copy++){
    tempBoard[copy]=board[copy];
  }
  
  updateBoard(tempBoard, boardRowSize, boardColSize);

  //if there is a change in the value of the cells, return 0, else return 1
  for(update=0; update<boardSize; update++){
    if(tempBoard[update]!=board[update])
       return 0;
  }
  
  return 1;
  
}

				
				
			

