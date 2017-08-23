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
#include "operation_dictionary.h"

#define ARRAYSIZE 200


int main(void) {

	FILE * input_file;
	bodyArray parsed;
	int parsed_size=-1;
	int number_of_lines=0; /*number of lines, including comments and blanks*/

	/*END OF DECLERATIONS*/

	create_operation_info_array();

	operation_info op = get_operation_info("add");
	printf("%s: %d",op.name, op.num_of_operands);

	if (!(input_file = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}

	parsed=(bodyArray)parse_file(input_file, &parsed_size,&number_of_lines);
	fclose(input_file);

/*	printf("sizeof structs: %d\nnumber of lines: %d\n",parsed_size,number_of_lines);*/


	print_structs(parsed,parsed_size);


	printf("\n\nstarting to validate file:\n");

	validate_file(parsed,parsed_size);





	printf("\n\n---===doei!===---\n");
	return EXIT_SUCCESS;
}


