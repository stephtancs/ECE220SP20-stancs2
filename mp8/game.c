/*This program creates and plays an instance of the 2048, a game whose peak popularity was in 2012. Each move function indicates a slide in the board in a particular direction.
 *
 * partners: stancs2, asanag2, anudeep2
 */

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	mygame->rows = rows;
	mygame->cols = cols;
	mygame->score = 0;
	
	// initializes cells to -1
	for(int i = 0; i < rows * cols; i++)
	{
		*(mygame->cells + i) = -1;
	}
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

	//reassigns pointers to new sizes
	(*_cur_game_ptr)->rows = new_rows;
	(*_cur_game_ptr)->cols = new_cols;
	(*_cur_game_ptr)->score = 0;
	
	// initializes all cells to -1
	for(int i = 0; i < new_rows * new_cols; i++)
	{
		*((*_cur_game_ptr)->cells + i) = -1;
	}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	
	// rn+c
	if(row >= 0 && row <= cur_game->rows && col >= 0 && col <= cur_game->cols)
	{
		return cur_game->cells + (row * cur_game->cols) + col;	
	}
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
	int row, col, targetRow;
	int returnValue = 0;
	
	for(col = 0; col < cur_game->cols; col++)
	{
		targetRow = 0;
		for(row = 0; row < cur_game->rows; row++)
		{
			// checks if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				
				// find first empty row
				while(*(get_cell(cur_game, targetRow, col)) != -1 && targetRow < row)
				{
					targetRow++;
				}
				
				// shift tiles if empty row is before current row
				if(targetRow < row)
				{
					*get_cell(cur_game, targetRow, col) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	for(col = 0; col < cur_game->cols; col++)
	{
		// from first to second-to-last row
		for(row = 0; row < cur_game->rows - 1; row++)
		{
			// check if cell is empty
			if(*get_cell(cur_game, row, col) != -1)
			{
				// merge if cell below current cell is the same value
				if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row + 1, col))
				{
					*get_cell(cur_game, row, col) *= 2;
					*get_cell(cur_game, row + 1, col) = -1;
					cur_game->score += *get_cell(cur_game, row, col);
					returnValue = 1;
				}
			}
		}
	}
	for(col = 0; col < cur_game->cols; col++)
	{
		targetRow = 0;
		for(row = 0; row < cur_game->rows; row++)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first empty row
				while(*(get_cell(cur_game, targetRow, col)) != -1 && targetRow < row)
				{
					targetRow++;
				}
				// shift if the empty row is before the current row
				if(targetRow < row)
				{
					*get_cell(cur_game, targetRow, col) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	// check if w is an invalid move by checking for positive return
	if(returnValue == 0)
	{
		return 0;
	}
    return 1;
};

int move_s(game * cur_game) //move down
{
    //YOUR CODE STARTS HERE
	int row, col, targetRow;
	int returnValue = 0;
	
	for(col = 0; col < cur_game->cols; col++)
	{
		targetRow = cur_game->rows - 1;
		
		for(row = cur_game->rows - 1; row >= 0; row--)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first empty row
				while(*(get_cell(cur_game, targetRow, col)) != -1 && targetRow > row)
				{
					targetRow--;
				}
				// shift if the empty row is before the current row
				if(targetRow > row)
				{
					*get_cell(cur_game, targetRow, col) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	for(col = 0; col < cur_game->cols; col++)
	{
		for(row = cur_game->rows - 1; row > 0; row--)
		{
			// check if cell is empty
			if(*get_cell(cur_game, row, col) != -1)
			{
				// merge if the cell above is the same value
				if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row - 1, col))
				{
					*get_cell(cur_game, row, col) *= 2;
					*get_cell(cur_game, row - 1, col) = -1;
					cur_game->score += *get_cell(cur_game, row, col);
					returnValue = 1;
				}
			}
		}
	}
	for(col = 0; col < cur_game->cols; col++)
	{
		targetRow = cur_game->rows - 1;
		for(row = cur_game->rows - 1; row >= 0; row--)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first possible empty row
				while(*(get_cell(cur_game, targetRow, col)) != -1 && targetRow > row)
				{
					targetRow--;
				}
				// shift if empty row is before current row
				if(targetRow > row)
				{
					*get_cell(cur_game, targetRow, col) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	// check if s is valid
	if(returnValue == 0)
	{
		return 0;
	}
    return 1;
};

int move_a(game * cur_game) //move left
{
    //YOUR CODE STARTS HERE
	int row, col, targetCol;
	int returnValue = 0;
	
	for(row = 0; row < cur_game->rows; row++)
	{
		targetCol = 0;
		
		for(col = 0; col < cur_game->cols; col++)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first empty column
				while(*(get_cell(cur_game, row, targetCol)) != -1 && targetCol < col)
				{
					targetCol++;
				}
				// shift if the empty column is before the current column
				if(targetCol < col)
				{
					*get_cell(cur_game, row, targetCol) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	
	for(row = 0; row < cur_game->rows; row++)
	{
		// from first to second-to-last column
		for(col = 0; col < cur_game->cols - 1; col++)
		{
			// check if cell is empty
			if(*get_cell(cur_game, row, col) != -1)
			{
				// merge if right cell is same value
				if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row, col + 1))
				{
					*get_cell(cur_game, row, col) *= 2;
					*get_cell(cur_game, row, col + 1) = -1;
					cur_game->score += *get_cell(cur_game, row, col);
					returnValue = 1;
				}
			}
		}
	}
	// iterate through each row
	for(row = 0; row < cur_game->rows; row++)
	{
		targetCol = 0;
		// iterate through each column
		for(col = 0; col < cur_game->cols; col++)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first possible empty column
				while(*(get_cell(cur_game, row, targetCol)) != -1 && targetCol < col)
				{
					targetCol++;
				}
				// shift if empty column is before current column
				if(targetCol < col)
				{
					*get_cell(cur_game, row, targetCol) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	// check if a is valid
	if(returnValue == 0)
	{
		return 0;
	}
    return 1;
};

int move_d(game * cur_game){ //move right
    //YOUR CODE STARTS HERE
	int row, col, targetCol;
	int returnValue = 0;
	
	for(row = 0; row < cur_game->rows; row++)
	{
		targetCol = cur_game->cols - 1;
		
		for(col = cur_game->cols - 1; col >= 0; col--)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first possible empty column
				while(*(get_cell(cur_game, row, targetCol)) != -1 && targetCol > col)
				{
					targetCol--;
				}
				// shift if empty column is before current column
				if(targetCol > col)
				{
					*get_cell(cur_game, row, targetCol) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	for(row = 0; row < cur_game->rows; row++)
	{
		for(col = cur_game->cols - 1; col > 0; col--)
		{
			// check if cell is empty
			if(*get_cell(cur_game, row, col) != -1)
			{
				// merge if left cell has same value
				if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row, col - 1))
				{
					*get_cell(cur_game, row, col) *= 2;
					*get_cell(cur_game, row, col - 1) = -1;
					cur_game->score += *get_cell(cur_game, row, col);
					returnValue = 1;
				}
			}
		}
	}
	
	for(row = 0; row < cur_game->rows; row++)
	{
		targetCol = cur_game->cols - 1;

		for(col = cur_game->cols - 1; col >= 0; col--)
		{
			// check if cell is empty
			if(*(get_cell(cur_game, row, col)) != -1)
			{
				// find first empty column
				while(*(get_cell(cur_game, row, targetCol)) != -1 && targetCol > col)
				{
					targetCol--;
				}
				// shift if empty column is before current column
				if(targetCol > col)
				{
					*get_cell(cur_game, row, targetCol) = *get_cell(cur_game, row, col);
					*get_cell(cur_game, row, col) = -1;
					returnValue = 1;
				}
			}
		}
	}
	// check if d is valid
	if(returnValue == 0)
	{
		return 0;
	}
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int returnVal = 0;
	
	for(int row = 0; row < cur_game->rows; row++)
	{
		for(int col = 0; col < cur_game->cols; col++)
		{
			// legal move exists if empty cell
			if(*get_cell(cur_game, row, col) == -1)
			{
				returnVal = 1;
			}
			// check if cell is empty
			if(*get_cell(cur_game, row, col) != -1)
			{
				// legal move exists if above cell = current
				if(row-1 >= 0)
				{
					if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row-1, col))
					{
						returnVal = 1;
					}
				}
				// legal move exists if below cell = current
				if(row+1 < cur_game->rows)
				{
					if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row+1, col))
					{
						returnVal = 1;
					}
				}
				// legal move exists if left cell = current
				if(col-1 >= 0)
				{
					if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row, col-1))
					{
						returnVal = 1;
					}
				}
				// legal move exists if right cell = current
				if(col+1 < cur_game->cols)
				{
					if(*get_cell(cur_game, row, col) == *get_cell(cur_game, row, col+1))
					{
						returnVal = 1;
					}
				}
			}
		}
	}
	// check legality
	if(returnVal == 0)
	{
		return 0;
	}
    return 1;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
