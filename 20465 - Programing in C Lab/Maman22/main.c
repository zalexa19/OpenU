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

void print_line(char []);

int main() {
	int close_indicator=0;
	char line[MAXLINELENGTH];
	char new_char;
	int line_index=0;



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


	printf("Please enter the command:\n");

	while ((new_char=getchar()) !='\n'){
		line[line_index]=new_char;
		line_index++;
	}

	print_line(line);

	if (close_indicator==1){
		printf("You wished to stop the program. Byes!\n");
	}

	printf("\n*** END ***\n");
	return 0;
}

void print_line(char str[]){
	int i=0;
	while (str[i]!='\0'){
		printf("%c",str[i]);
		i++;
	}
	printf("\n");
}

