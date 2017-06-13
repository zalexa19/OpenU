/*
 ============================================================================
 Name        : lists-Dynamic array
 Author      : Alex Z
 Version     :
 Copyright   : Your copyright notice
 Description : Question #1.

 In this implementation, characters are saved one by one in a dynamic array.
 At first, I allocate memory for 5 integers using malloc.
 If more than 5 chars are received, I expand the memory using realloc.
 The new memory size is twice bigger than the previous. This way, the complexity of the algorithm
 is improved.
 After receiving the chars, I print them one by one.
 After printing them, I free the space using free() on the first array cell.

 main:
 1. Receives the chars as long as EOF is not reached
 2. Sends that char to addSpace()
 3. Calls for printData()
 4. Releases the memory once printing is done

 addSpace()
 Receives: pointer to the array, index of the next free cell, the new character, current size of the array
 1. Checks if there is enough space in the array by comparing index and arrSize.
 if arrSize is bigger than index, then there is enough space so we add the newChar using the index received.
 2. Extends the array:
 When index > arrSize, it means that additional space is required. Using a temporary pointer temp,
 we extend current size using realloc. The new size of the array, is arrSize*2;
 If memory allocation was successful, we add newChar to temp[index], and then set temp as
 our extended array (data).

 function return the array size - original as received/new array size after extension.
 if memory allocation failed, function returns -1, main catches it and the program is closed.

  printData:
  receives a pointer to the first array cell, and the index;
  Prints each cell starting from the first one.
  returns nothing

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define INITIALARRAYSIZE 5 /*Initial array size*/

int addSpace(int **,int, int, int);
void printData(int *, int);


int main(void) {
	int * data; /*The array*/
	int characterInput;
	int arraySize=INITIALARRAYSIZE; /*Tracks the memory allocation for the array*/
	int dataIndex=0; /*Tracks number of characters received*/


	data=(int *)malloc( INITIALARRAYSIZE* sizeof(int));
	if (!data){
		printf("Memory allocation failed (malloc)");
		exit(0);
	}

	printf("Please enter you input, stopping at EOF:\n");

	while ((characterInput=getchar()) != EOF){
		arraySize=addSpace(&data,dataIndex,characterInput, arraySize);

		if (arraySize==-1){
			printf("Memory allocation failed by realloc");
			exit(0);
		}
		dataIndex++;
	}

	printf("Input received. You entered:\n");
	printData(data,dataIndex);

	free(data);
	return 0;
}

int addSpace(int ** data, int index, int newChar, int arrSize){
	int * temp;/*Used for realloc*/

	if (index < arrSize){
		temp=*data;
		temp[index]=newChar;
	}

	else {
		arrSize=arrSize*2;
		temp=(int *)realloc(*data,arrSize*sizeof(int));

		if (!temp){
			return -1;
		}

		temp[index]=newChar;
		*data=temp;
	}

	return arrSize;
}

void printData(int * cell, int counter){
	int i;
	for (i=0; i<counter;i++){
		printf("%c",cell[i]);
	}

	printf("\n***END***\n");

}
