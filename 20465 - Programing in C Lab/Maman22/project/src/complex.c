/*
 ============================================================================
 Name        : complex.c
 Author      :Alex Zablotsky 314494964
 Version     :
 Copyright   : Your copyright notice
 Description :

functions are defined as described in the maman description
 ============================================================================
 */
#include <stdio.h>
#include <math.h>
#include "complex.h"

/*
 * 	Receives: 2 doubles and a reference to a complex struct
 * 	returns: void
 * 	This function simply takes the received doubles and puts them into the struct
 *
 */
void read_comp(double newA, double newB, complex * name ){
	name->a=newA;
	name->b=newB;
}

/*
 * this function prints the complex number by getting the doubles stored in the struct,
 * and then adding the "i"
 * recieves: a complex number
 */
void print_comp(complex comp){
	double a=comp.a; /*holds the first double*/
	double b=comp.b;/*holds the second double*/

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
 * receives: complex numbers
 * returns: a new complex number
 *
 */
complex add_comp(complex number, complex other_number){
	complex result;
	result.a=number.a+other_number.a;
	result.b=number.b+other_number.b;

	return result;
}

/*
 * This function subtructs to complex numbers
 * receives: complex numbers
 * returns: a new complex number
 *
 */

complex sub_comp(complex number ,complex other_number){
	complex result;

	result.a=number.a-other_number.a;
	result.b=number.b-other_number.b;

	return result;
}


/*
 * This function multiplies a complex number by a real number
 * receives: complex number and a double
 * returns: a new complex number
 */

complex mult_comp_real(double real_number,complex complex_number){
	complex result;

	result.a=real_number*complex_number.a;
	result.b=real_number*complex_number.b;


	return result;

}

/*
 * This function multiplies an imaginary number i by real and complex numbers
 * this method creates a new temporary complex 0+real_numberi and uses mult_comp_comp
 * for the calculation
 * receives: complex number and a double.
 * returns: a new complex number
 */

complex mult_comp_img(double real_number, complex complex_number){
	complex result;

	complex temp; /*new temp complex for creating (0+real_number)i*/
	temp.a=0;
	temp.b=real_number;

	result=mult_comp_comp(temp,complex_number);
	return result;
}

/*
 * This function multiplies two complex numbers.
 * As described in the maman
 * receives: complex number and a double.
 * returns: a new complex number
 */

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

/*
 * Calculates the absolute value
 * receives a complex number
 * returns a complex number
 */

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
