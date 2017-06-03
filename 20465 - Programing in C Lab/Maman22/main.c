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

/**/


int main() {

	double a,b,c,d; /*Test*/



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


	a=0.5666;
	b=1.5;
	read_comp(a,b,&A);
	print_comp(A);
	c=1.0;
	d=-2.5;
	printf("\nB=1.0+2.5i\n");
	read_comp(c,d,&B);
	print_comp(B);

	printf("\nA=10.5-3.9i\n");
	read_comp(10.5,-3.9,&A);
	print_comp(A);

	printf("Test#1: EXPECTED: (14 + 7.1i), RESULT: ");
	read_comp(10.4,4.2,&A);
	read_comp(3.6,2.9,&B);
	print_comp(	add_comp(A,B));
	printf("Test#2: EXPECTED: (-6.8+7.1i), RESULT: ");
	read_comp(-10.4,4.2,&A);
	read_comp(3.6,2.9,&B);
	print_comp(	add_comp(A,B));
	printf("Test#3: EXPECTED: (-6.8+1.3i), RESULT: ");
	read_comp(-10.4,4.2,&A);
	read_comp(3.6,-2.9,&B);
	print_comp(	add_comp(A,B));
	printf("Test#4: EXPECTED: (-14-7.1)i, RESULT: ");
	read_comp(-10.4,-4.2,&A);
	read_comp(-3.6,-2.9,&B);
	print_comp(	add_comp(A,B));


	return 0;
}

