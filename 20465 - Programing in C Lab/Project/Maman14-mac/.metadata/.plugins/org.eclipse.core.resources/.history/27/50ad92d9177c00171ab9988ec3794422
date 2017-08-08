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

	/*END OF DECLERATIONS*/

	puts("!!!Starting tests!!!\n"); /* prints !!!Hello World!!! */

	if (!(input_file = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}

	parsed=(bodyArray)parse_file(input_file);
	//printf("bbb %s",parsed[0].label);
	fclose(input_file);



	print_structs(parsed);



	printf("doei!\n");
	return EXIT_SUCCESS;
}


