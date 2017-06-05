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
#define INITIALMATRIXSIZE 4
typedef char * array;


void print_matrix(array *, int);
void print_line(array);
array fix_spaces(char []);
array read_user_input();
array * create_substrings(array);
array copy_sub_string(char src[], int point1, int point2);




int main() {
	int close_indicator=0;
	array orig_line;
	array trimmed_line;
	array * matrix;

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
	trimmed_line=fix_spaces(orig_line);
	print_line(trimmed_line);
/*
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

	printf("\n\nTest#4\n");
	orig_line=read_user_input();
	print_line(orig_line);
	trimmed_line=removeBlanks(orig_line);
	print_line(trimmed_line);

	printf("\n\nTest#5\n");
	orig_line=read_user_input();
	print_line(orig_line);
	trimmed_line=removeBlanks(orig_line);
	print_line(trimmed_line);
*/
	printf("\n\nTesting Split\n");
	matrix = create_substrings(trimmed_line);
	print_matrix(matrix,INITIALMATRIXSIZE);















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


array fix_spaces(array orig){

	int orig_size=strlen(orig);
	array result = (char *)malloc(orig_size);
	int i;
	int counter=0;
	int allowed_space=0;
	int t=0;
	char c;

	c=orig[t];
	while ((c == ' ') ||(c == '\t')){
		t++;
		c=orig[t];
	}

	/*t holds a new char*/

	for (i=t;i<orig_size;i++){
		char c=orig[i];

		if (c ==' '){
			if ( (counter != 0) && (result[counter-1] != ' ') && (allowed_space==0) ){
				result[counter]=c;
				counter++;
				allowed_space=1;
			}
		}

		else if (c =='\t'){
			if ( (i != 0) && (result[counter-1] != ' ') && allowed_space==0 ){
				result[counter]=' ';
				counter++;
			}


		}

		else if (c=='\n'){
			result[counter]='\0';

		}

		/*else if (c==','){
			result[counter]= ' ';
			counter++;
		}*/

		else{
			result[counter]=c;
			counter++;
		}


	}

	return result;
}


/*Split the line into substrings*/

/*
array * create_substrings(array line){
	int i;
	array * matrix;
	int mat_size=4;
	int size=strlen(line);
	array sub;
	int point1=0;
	int point2=0;
	char c;
	int mat_counter=0;
	matrix=(array *) malloc(mat_size* sizeof(array));

	for(i=0;i<=size;i++){
		c=line[i];
		if (c==' '){
			point2=i;

			sub=(array)malloc(point2*sizeof(char));
			memmove(sub,line,point2);
			matrix[mat_counter]=sub;
			mat_counter++;

			point1=point2;
		}


		if (c==','){
			point2=i;
			sub=copy_sub_string(line,point1,point2);
		}

	}

	return matrix;
}

*/



array * create_substrings(array line){
	int line_size=strlen(line); /*Line length for creation of a regular array*/
	int n; /*Used as an index for a loop*/
	array * matrix; /*Final array*/
	int i=0; /*Used as an index in the matrix*/
	array token; /*used for splitting*/
	int token_size; /*used for calculating size when allocating memory for substrings*/
	char line_copy[line_size+1]; /*Temporary array for strtok*/

	/*Making a copy of the array*/
	for (n=0;n<line_size;n++){
		line_copy[n]=line[n];
	}



	matrix=(array*)malloc (INITIALMATRIXSIZE*sizeof(array));
	printf("%s\n",line_copy);

	token=strtok(line_copy," ,");
	while (token != NULL){
		token_size=strlen(token);
		matrix[i]=(array)malloc(sizeof(char)*token_size);
		matrix[i]=token;
		i++;
		token=strtok(NULL, " ,");
	}


	return matrix;

}







void print_matrix(array * matrix, int size){
	int i;

	for (i=0;i<size;i++){
		int in_size=strlen(matrix[i]);
		int j;

		for (j=0;j<=in_size;j++){
			printf("%c", matrix[i][j]);
		}

	}


}

array copy_sub_string(char src[], int point1, int point2){
	int size=(point2-point1)+2;
	int i;

	array result=(array)malloc(size*sizeof(char));
	if (!result){
		printf("issue with memory\n");
		exit(0);
	}

	for (i=0;i<size;i++){
		result[i]=src[i];
	}

	result[i]='\0';
	return result;
}
