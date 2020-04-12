/*
In createmaze, we read through the input file containing the unsolved maze, and the dimensions of the maze. We then create allocate memory for the maze and all its cells. Then we replicate the maze for the solvemazedfs to work. Main.c feeds the starting point into the solvemazedfs function, which then checks base cases, and uses dfs to search for valid solution. We do this by traversing in each direction and mark path as visited or part of solution until endpoint is reached. Then we print the inital given maze and the solution maze out to the screen, then we free memory used to contain the data for the maze.
partners: anudeep2, stancs2, asanag2
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.

    FILE *filePointer; //create file pointer fp
    filePointer = fopen(fileName,"r"); //read mode
    maze_t *maze = malloc(sizeof(maze_t)); //allocate memory for maze using mallow
    int i, j, nwidth, nheight; //to use for loops and associating the maze dimensions
    char a; //use with the file maze contents

    fscanf(filePointer,"%d %d", &nwidth, &nheight); //read the dimensions of maze
    maze->width = nwidth; //set maze width from file infor
    maze->height = nheight; //set maze height from file info

    //allocate memory for the lookup table aka the address of each row using given height in file
    maze->cells = (char **)malloc(nheight * sizeof(char *)); //allocate enough for char pointer times height, for lookup table
    for(i=0;i<nheight;i++){
        maze->cells[i] = (char *)malloc(nwidth * sizeof(char)); //now for each row, allocate memory for all cells to the size of a char and cast to char pointer
    }
    //time to recreate/replicate the unsolved maze in the given file
    fscanf(filePointer,"%c",&a);
    for(i=0;i<nheight;i++){//for each row
        for(j=0;j<nwidth;j++){//and each cell within row
            fscanf(filePointer,"%c",&a);//scan char
            if(a == START){//if char is 'S' then mark the startrow and col
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(a == END){//if char is 'E' then mark the endrow and endcol
                maze->endRow = i;
                maze->endColumn = j;
            }
            //else
            maze->cells[i][j] = a;//set char to cell
        }
        fscanf(filePointer,"%c",&a);//do not use \n character before exiting loop to next row
    }
    fclose(filePointer);//IMPORTANT close file
    return maze;//return newly created maze
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    //lab notes: free every cell using loop, free cells, free maze like vector functions in vector.c
    int i;
    for(i = 0; i < maze->height; i++){//for all rows
        free(maze->cells[i]);//free cells row content memory first
    }
    free(maze->cells);//free cells memory
    free(maze);//free maze memory (parent free)
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    //print dimensions, new line, then each row followed by a new line like the output format on wiki
    //printf("%d %d\n", maze->width, maze->height);//print dimensions ------ maze1gold.txt did not have it so removed.
    int i, j;
    for(i=0;i< maze->height; i++){//each row
        for(j=0; j< maze->width;j++){//each col
            printf("%c", maze->cells[i][j]);//print cell
        }
        printf("\n");//new line before new row to print
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here.
    //1:
    if(row<0 || col<0 || row >= maze->height || col >= maze->width){
        return 0;//if out of bounds return false
    }
    //2:
    //   return 0;//check if empty cell, if not return false
    if(maze->cells[row][col] != START && maze->cells[row][col] != END){
        if(maze->cells[row][col] != EMPTY){//check empty
            return 0;
        }
    }
    //3:
    if(maze->cells[row][col] == END){
        maze->cells[maze->startRow][maze->startColumn] = START;
        return 1;//return true
    }
    //4:
    maze->cells[row][col] = PATH;//set col, row as part of solution path in the maze
    //5:
    if(solveMazeDFS(maze,col-1,row)==1){return 1;}//test left of given cell, return 1 if true
    //6:
    if(solveMazeDFS(maze,col+1,row)==1){return 1;}//test right of given cell, return 1 if true
    //7:
    if(solveMazeDFS(maze,col,row+1)==1){return 1;}//test up of given cell, return 1 if true
    //8:
    if(solveMazeDFS(maze,col,row-1)==1){return 1;}//test down of given cell, return 1 if true
    //9:
    maze->cells[row][col] = VISITED;//if nothing is solution, then rewrite cell as visited
    //10:
    return 0;//then exit with false to search for new path
}
