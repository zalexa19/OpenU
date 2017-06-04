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


	printf("\nadd_comp\n");
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

	printf("\nsub_comp\n");
	printf("Test#1: EXPECTED: (6.8+7.1i), RESULT: ");
	read_comp(10.4,4.2,&A);
	read_comp(3.6,2.9,&B);
	print_comp(sub_comp(A,B));
	printf("Test#2: EXPECTED: (6.8 + 7.1)i, RESULT: ");
	read_comp(10.4,4.2,&A);
	read_comp(3.6,-2.9,&B);
	print_comp(sub_comp(A,B));

	printf("Test#3: EXPECTED: (14 - 7.1)i, RESULT: ");
	read_comp(10.4,-4.2,&A);
	read_comp(-3.6,2.9,&B);
	print_comp(sub_comp(A,B));

	printf("\nmult_comp_real\n");
	printf("Test#1: EXPECTED: (11+20.6)i, RESULT: ");
	read_comp(5.5,10.3,&C);
	print_comp(mult_comp_real(2.0,C));
	printf("Test#2: EXPECTED: (13.75+25.75)i, RESULT: ");
	read_comp(5.5,10.3,&C);
	print_comp(mult_comp_real(2.5,C));
	printf("Test#3: EXPECTED: (-13.75+25.75)i, RESULT: ");
	read_comp(-5.5,10.3,&C);
	print_comp(mult_comp_real(2.5,C));

	printf("\nmult_comp_img\n");
	printf("Test#1: EXPECTED: (-56.65 + 30.25)i, RESULT: ");
	read_comp(5.5,10.3,&C);
	print_comp(mult_comp_real(5.5,C));
	return 0;
}

