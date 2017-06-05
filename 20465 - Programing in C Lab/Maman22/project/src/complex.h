#include <math.h>

typedef struct {
	double a;
	double b;
}complex;



void read_comp(double newA, double newB, complex * name );
void print_comp(complex comp);
complex add_comp(complex number, complex other_number);
complex sub_comp(complex number ,complex other_number);
complex mult_comp_real(double real_number,complex complex_number);
complex mult_comp_img(double real_number, complex complex_number);
complex mult_comp_comp(complex number,complex other_number);
complex abs_comp(complex complex_number);
