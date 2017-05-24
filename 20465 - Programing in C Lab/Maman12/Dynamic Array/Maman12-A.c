/*
 ============================================================================
 Name        : lists-Dynamic array
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int addSpace(int **,int, int);
void printData(int *, int);


int main(void) {
	int * data;
	int characterInput;
	int successResponse;
	int dataIndex=0;



	data=(int *)malloc( sizeof(int));
	if (!data){
		printf("Memory allocation failed (malloc)");
		exit(0);
	}

	printf("Please enter you chars:\n");

	while ((characterInput=getchar()) != ']'){
		successResponse=addSpace(&data,dataIndex,characterInput);

		if (successResponse==0){
			printf("Memory allocation failed by realloc");
			exit(0);
		}

		dataIndex++;
	}


	printData(data,dataIndex);

	free(data);
	return 0;
}

int addSpace(int ** data, int index, int newChar){
	int currentSize=(sizeof(int)*(index+1));
	int * temp;

	temp=(int *)realloc(*data,currentSize+sizeof(int));
	temp[index]=newChar;

	if (!temp){
		return 0;
	}

	*data=temp;


	return 1;
}

void printData(int * cell, int counter){
	int i;
	for (i=0; i<counter;i++){
		printf("%c",cell[i]);
	}

	printf("\n***END***\n");

}
