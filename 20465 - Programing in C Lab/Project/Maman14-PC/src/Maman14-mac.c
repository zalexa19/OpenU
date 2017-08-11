/*
 ============================================================================
 Name        : Maman14.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "utils.h"
#include "parser.h"
#define ARRAYSIZE 200


int main(void) {

	FILE * input_file;
	bodyArray parsed;
	int parsed_size=-1;
	int number_of_lines=0; /*number of lines, including comments and blanks*/
	int ** matrix;
	int i,j,n;

	/*END OF DECLERATIONS*/

	puts("!!!Starting tests!!!\n"); /* prints !!!Hello World!!! */

	if (!(input_file = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}

	parsed=(bodyArray)parse_file(input_file, &parsed_size,&number_of_lines);
	fclose(input_file);

/*	printf("sizeof structs: %d\nnumber of lines: %d\n",parsed_size,number_of_lines);*/


	print_structs(parsed,parsed_size);

	printf("starting to validate file:\n");
	printf("_____________________________________\n");

	validate_file(parsed,parsed_size);

	printf("TESTING MATRIX:\n");
	printf("_____________________________________\n");

	matrix=(int**)malloc(3*sizeof(int*));
	for (i=0;i<3;i++){
		matrix[i]=(int*)malloc(4*sizeof(int));
	}

	n=0;
	for (i=0;i<3;i++){
		n++;
		for (j=0;j<4;j++){
			matrix[i][j]=n;
			n++;
		}
	}




	printf("\n\n---===doei!===---\n");
	return EXIT_SUCCESS;
}


