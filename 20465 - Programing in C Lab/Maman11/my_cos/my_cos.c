/*Alex Z, Maman11*/

/*This program calculates the cos of an angle received as a radian.
The program uses function my_cos() for the calculation.
In addition, the main function calculates the cos using the cos() function
from math.h.

Both results are printed by the main for comparison.
Assumptions: User input is a valid number.
*/
#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define STARTINDEX 2 /*constant that is used in the my_cos function for calculating the cosine*/
#define ACCURACY 6
double my_cos(double rad);

int main (){
	double radian=0; /*The radian received from the user for which we caculate the cosine*/
	double libResult=0; /*Cosine calculated using Math.h*/
	double myResult=0.0; /*Cosine calculated using my_cos*/


	printf("\n\nPlease insert a number in radians\n");
	scanf("%lf",&radian);

	if (radian>PI){
		radian=radian-2*PI;
	}
	else if (radian >PI/2){
		radian=PI-radian;
	}

	libResult=cos(radian);

	myResult=my_cos(radian);
	printf("cos calculated by fucntion: %f\n",myResult);
	printf("cos calculated by library: %f\n",libResult);


	printf(" \nEnd of Main\n");
	return 1;
}

/*Function receives a radian, and performs the calculation
using the cos formula. 
accuracy is 6 as was requested in the Maman.
The function returns the result of this calculation*/
double my_cos (double rad){
	long i;
	double result=1;

	for (i=STARTINDEX;i<=ACCURACY*STARTINDEX;i+=STARTINDEX){
		int devisor=1; /*The calculated factorial*/
		double power=rad;
		double member;

		/*Calculating the power for each member*/
		int k;
		for(k=1;k<i;k++){
			power=power*rad;
		}
		/*Calculating the devidor for each memeber*/
		for (k=STARTINDEX;k<=i;k++){
			devisor=devisor*k;
		}

		/*Calculating the memeber*/
		member=(power/(double)devisor);

		/*If the member is an odd number, it should be added to the final result
		Else, should be substruced (based on the fomula)
		*/
		if ((i/2)%2==0){
			/*member should be positive*/
			result=result+member;
		}
		else{
			result=result+(member*(-1));
		}
	}
	return result;
}
