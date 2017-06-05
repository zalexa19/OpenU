/*
 ============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#define MAXLINELENGTH 100
typedef char * array;

void print_line(array);
array removeBlanks(char []);
array read_user_input();

int main() {
	int close_indicator=0;
	array orig_line;
	array trimmed_line;

	complex A,B,C,D,E,F;
	A.a=0;
	A.b=0;
	B.a=0;
	B.b=0;
	C.a=0;
	C.b=0;
	D.a=0;
	D.b=0;
	E.a=0;
	E.b=0;
	F.a=0;
	F.b=0;

	printf("\nTrimming spaces tests\n");
	printf("Test#1\n");
	orig_line=read_user_input();
	print_line(orig_line);
	trimmed_line=removeBlanks(orig_line);
	printf(trimmed_line);

	printf("\n\nTest#2\n");
	orig_line=read_user_input();
	print_line(orig_line);
	trimmed_line=removeBlanks(orig_line);
	print_line(trimmed_line);


	printf("\n\nTest#3\n");
	orig_line=read_user_input();
	print_line(orig_line);
	trimmed_line=removeBlanks(orig_line);
	print_line(trimmed_line);















	if (close_indicator==1){
		printf("You wished to stop the program. Byes!\n");
	}

	printf("\n*** END ***\n");
	return 0;
}

void print_line(array line){
	int i=0;
	int tmp=strlen(line);

	for ( i=0; i<=tmp; i++){

		printf("%c",line[i]);
	}
	printf("\n");
}

array read_user_input(){
	array input;
	char new_char;
	int line_index=0;


	input= (char *)malloc(sizeof(char)*MAXLINELENGTH);
	if (!input){
		printf("trouble with memory allocation.");
		exit(0);
	}

	while ((new_char=getchar()) !='\n'){
		if (line_index < MAXLINELENGTH){
			input[line_index]=new_char;
			line_index++;
		}
		else{
			array tmp = (char*)realloc(input,sizeof(MAXLINELENGTH)*2);
			if (!tmp){
				printf("issue with memo");
				exit(0);
			}
			else {
				input=tmp;
			}
		}
	}

	return input;
}


array removeBlanks(array orig){
	int orig_size=strlen(orig);
	array result = (char *)malloc(orig_size);
	int i;
	int counter=0;

	/*printf("Line size is:%d\n",orig_size);*/

	for (i=0;i<orig_size;i++){
		char c=orig[i];

		if (c ==' '){
			if ( (counter != 0) && (result[counter-1] != ' ') ){
				result[counter]=c;
				counter++;
			}
		}

		else if (c =='\t'){
			if ( (i != 0) && (result[counter-1] != ' ') ){
				result[counter]=' ';
				counter++;
			}


		}

		else if (c=='\n'){
			result[counter]='\0';

		}

		else{
			result[counter]=c;
			counter++;
		}


	}

	return result;
}

