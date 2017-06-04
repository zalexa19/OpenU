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


/*
 * This method prints the complex number
 */

void print_comp(complex comp){
	double a=comp.a;
	double b=comp.b;

	printf("(%g ",a);

	if (b<0){
		printf("%g",b);
	}
	else {
		printf("+ %g",b);
	}
	printf(")i\n");

}
/*
 * This function adds to complex numbers
 */
complex add_comp(complex number, complex other_number){
	complex result;
	result.a=number.a+other_number.a;
	result.b=number.b+other_number.b;

	return result;
}

/*
 * This function subtracts complex numbers
 */

complex sub_comp(complex number ,complex other_number){
	complex result;

	result.a=number.a-other_number.a;
	result.b=number.b-other_number.b;

	return result;
}


/*
 * This function multiplies a complex number by a real number
 */

complex mult_comp_real(double real_number,complex complex_number){
	complex result;

	result.a=real_number*complex_number.a;
	result.b=real_number*complex_number.b;


	return result;

}

/*
 * This function multiplies an imaginary number i by real and complex numbers
 */

complex mult_comp_img(double real_number, complex complex_number){
	complex result;

	complex temp;
	temp.a=0;
	temp.b=real_number;

	result=mult_comp_comp(temp,complex_number);
	return result;
}

complex mult_comp_comp(complex number,complex other_number){
	complex result;

	double a=number.a;
	double b=number.b;
	double c=other_number.a;
	double d=other_number.b;

	result.a= (a*c)-(b*d);
	result.b= (a*d)+(b*c);

	return result;

}

complex abs_comp(complex complex_number){
	complex result;
	double a=complex_number.a;
	double b=complex_number.b;
	double real_number;
	a=pow(a,2.0);
	b=pow(b,2.0);
	real_number=sqrt(a+b);

	result.a=real_number;
	result.b=0;
	return result;
}
