#include <stdio.h>
#include "slope.h"


// Return index of the first row that is not a slope; otherwise return -1

//loops throuh entire array and sets variables for 3 values in the row in order to test them against each other to prove the correct ordering of the row
int find_nonslope_row(int array[6][6]) {
  for(int i = 0; i < 6; i++){
    for(int j = 1; j < 5; j++){
      int before = array[i][j-1];
      int current = array[i][j];
      int after = array[i][j+1];
      if((before>current && after>=current)||(before==current||current==after)||(before<current && after<current)){
	return i;
      }
    }
  }
  
  return -1;
}

//opens file, reads it, puts it into an array, closes file
int read_array(char* filename, int array[6][6]){
  // Your code starts here
  FILE *filePointer;
  filePointer = fopen(filename, "r");

  if(filePointer==NULL)
    return 0;
  
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      fscanf(filePointer, "%d", &array[i][j]);
    }
  }
  
  fclose(filePointer);
  return 1;
}

