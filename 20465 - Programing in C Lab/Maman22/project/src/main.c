/*
 ============================================================================
 Name        : main.c
 Author      : Alex Zablotsky 314494964
 Version     :
 Copyright   : Your copyright notice
 Description : Disclaimer -
 I'm sorry but I wasn't able to finish the parser in time.
 Therefore - main is not looping, input cannot be parsed and I didn't make any tests.

 My whole idea was:

 1. receive the user input and store it in an array
 2. clear  unwanted spaces and tabs
 3. create an array of strings, then split the input using strtok with delim (" ,"). Every token should be stored
 Separately in the matrix.
 This way i'd expect to have the commend in matrix[i], then the parameters in i+2..n;
 4. Validate the input using this matrix - for example, i'd expect to recieve 3 parameters (double, double, complex name) for read_comp
 5. compare the first cell (command) against a string array which holds the command names
 6. execute the relevant function.

 function create_substrings is not working. I think it has something to do with result[i] = token

 Will appreciate it if you could explain why my matrix is wrong.



Thanks in advance


 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#define MAXLINELENGTH 100
#define ROWS 20
#define COLS 20
typedef char * array;



void print_matrix(array *, int); /*Prints the matrix*/
void print_line(array); /*prints a simple array (char *) */
array fix_spaces(char []); /*removes spaces and tabs*/
array read_user_input(); /*saves user's command with the parameters as a string*/
int create_substrings(array ,array **); /*breaks the string to substrings*/
int get_command(array *); /*translates the command string*/




int main() {
	int close_indicator=0;
	array orig_line; /*Original User Input*/
	array trimmed_line; /*User input after removing irrelevant spaces*/
	array * matrix;/*Array of strings - each input substring is stored in a different cell*/
	int mat_size; /*stores matrix row size as recieved from create_substring*/
	int i;
	int command=-1;


	matrix = (array*)malloc(ROWS*sizeof(array));

	complex A,B, C,D,E,F;
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


	printf("Hello. please enter your command:\n ");
	orig_line=read_user_input();
	printf("Your input was: ");
	trimmed_line=fix_spaces(orig_line);
	print_line(trimmed_line);

	mat_size=create_substrings(trimmed_line,&matrix);
	printf("mat_size is %d\n",mat_size);








	printf("\n*** END ***\n");
	return 0;
}



/*
 *print a simple string array
 * recieves a char array
 */
void print_line(array line){

	printf("%s\n",line);

}

/*
 * Gets user input and saves it as a string.
 * returns the string as char *
 *
 */

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
				printf("trouble with memory allocation");
				exit(0);
			}
			else {
				input=tmp;
			}
		}
	}

	return input;
}

/*
 * removes irrelevant spaces and tabs.
 * Receives: the orig string
 * returns: a new string
 * at first, removes all spaces before the command (the first loop). then, it leaves only one space (between the command and the first
 * parameter) and deletes all other spaces/tabs. this is done by keeping track of the last character entered into the result array.
 *
 *
 */
array fix_spaces(array orig){

	int orig_size=strlen(orig);
	array result = (char *)malloc(orig_size);
	int i;
	int counter=0; /*keeps track of the result*/
	int allowed_space=0; /*turned on when the first spaces is added*/
	int t=0;
	char c; /*holds the character, for easier code reading*/

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


		else{
			result[counter]=c;
			counter++;
		}


	}

	return result;
}


/*
 * craetes substrings by using strtok.
 * recieves: user input (without spaces), pointer to the matrix
 * returns: void. i wanted it to update the matrix on the fly. didn't work :(
 * at first we make a copy of the line (so strtok could distort it)
 * then allocate memory to result;
 * using while (token != NULL), for each i, I allocate memory in the size of a token, then make result[i]=token.
 *
 * when function ends running, the matrix should consist of: matrix[0] = "command", matrix[1]="parameter", matrix[2]="parameter" and so on
 */


int create_substrings(array line, array ** matrix){
	array * result;
	int line_size;
	int i=0;
	array line_copy;
	array token;
	int length;

	printf("\n~entered create_substrings\n ");
	line_size=strlen(line);


	printf("~copied array\n");
	result=(array *)malloc (5*sizeof(array));

	token=strtok(line," ,");
	while (token != NULL){
		length=strlen(token);
		result[i]=(array)malloc(length*sizeof(char));
		result[i]=token;
		i++;
		printf("token should be: %s. ",token);

		token=strtok(NULL," ,");
		printf("entered - %s to %d\n",result[i],i);
	}

	printf("finished product: ");
	print_matrix(result,i+1);


	return -1;
}





/*
 * prints the matrix
 * recieves the matrix and number of rows to go over
 */

void print_matrix(array * matrix, int size){
	int i;

	for(i=0;i<size;i++){
		printf("%s\n",matrix[i]);

	}

	/*
	for (i=0;i<size;i++){
		int in_size=strlen(matrix[i]);
		int j;

		for (j=0;j<=in_size;j++){
			printf("%c", matrix[i][j]);
		}

		printf(" ");
	}

	printf("\n");
	*/
	printf("**Finished printing matrix");
}


/*
 * Supposed to compre the command in matrix[0], with funcs[], when funcs[] holds the names of the functions as strings.
 * didn't work for me, becuase of the matrix issue (i think)
 * returns an int which i wanted to use to invoke the required function later on (don't have that code yet)
 */
int get_command(array * input){
	int i=0;
	int result=-1;
	array funcs[9];
	funcs[0]="read_comp";
	funcs[1]="print_comp";
	funcs[2]="add_comp";
	funcs[3]="sub_comp";
	funcs[4]="mult_comp_real";
	funcs[5]="mult_comp_img";
	funcs[6]="mult_comp_comp";
	funcs[7]="abs_comp";
	funcs[8]="halt";


	printf("Checking the command\n");
	printf("%s\n",input[0]);
	for (i=0;i<9;i++){
		printf("");
		if ((strcmp(input[0],funcs[i]) == 0)){
			result=i;
		}
	}



return -1;

}

/*Thank you for readning this, although my assignment is not complete*/
