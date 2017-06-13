/*
 ============================================================================
 Name        : Void.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Generic solution*/
void swap (void *, void *, int);
void swap2 (void *, void *, int);
void swap3 (void *, void *, int);


int main() {
	int x1, x2;
	double y1,y2;

	x1 = 8;
	x2=5;
	y1 = 10.5;
	y2=15.5;


	printf("Before: x1=%d,int2=%d\n",x1,x2);
	swap(&x1,&x2,sizeof(int));
	printf("After: x1=%d,int2=%d\n",x1,x2);

	printf("Before: y1=%lf,y2=%lf\n",y1,y2);
	swap(&y1,&y2,sizeof(double));
	printf("After: y1=%lf,y2=%lf\n",y1,y2);

	return 0;
}

/*the int type represents the bit size of the pointers. in this way we can know the type*/

void swap (void *p1, void *p2, int type){
	char * temp = (char *)malloc(type);
	char * q1=(char *)p1;
	char * q2=(char *)p2;
	int i;

	for (i=0;i<type;i++){
		temp[i]=q1[i];
		q1[i]=q2[i];
		q2[i]=temp[i];
	}

	free(temp);

}






