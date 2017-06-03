/*
 ============================================================================
 Name        : complex.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <math.h>
#include "complex.h"


void read_comp(double newA, double newB, complex * name ){
	name->a=newA;
	name->b=newB;
}

void print_comp(complex comp){
	double a=comp.a;
	double b=comp.b;

	printf("%g",a);

	if (b<0){
		printf("%g",b);
	}
	else {
		printf("+%g",b);
	}
	printf("i\n");


}


void printI(){
	printf("This is my i");
}
