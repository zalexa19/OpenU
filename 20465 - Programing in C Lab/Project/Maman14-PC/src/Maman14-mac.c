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
#include "first_scan.h"
#include "second_scan.h"

#define ARRAYSIZE 200


int main(void) {

	FILE * input_file;
	bodyArray parsed;
	int ic;
	int parsed_size=-1;
	int number_of_lines=0; /*number of lines, including comments and blanks*/
	symbol_ptr symbols=NULL;



	/*END OF DECLERATIONS*/
	ic=0;
	create_operation_info_array();

/*	operation_info op = get_operation_info("add");*/

	if (!(input_file = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}

	parsed=(bodyArray)parse_file(input_file, &parsed_size,&number_of_lines);
	fclose(input_file);

/*	printf("sizeof structs: %d\nnumber of lines: %d\n",parsed_size,number_of_lines);*/


	print_structs(parsed,parsed_size);

/*

	printf(BOLDRED "inside the  struct1, operand 1: <%s> \n",parsed[0].OPERAND1);
	printf(BOLDRED "inside the  struct1, operand 2: <%s> \n",parsed[0].OPERAND2);
	printf(BOLDRED "inside the  struct1, operand 3: <%s> \n",parsed[0].leftovers);

	printf(BOLDRED "inside the last struct, operand 1: <%s> \n",parsed[1].OPERAND1);
	printf(BOLDRED "inside the last struct, operand 2: <%s> \n",parsed[1].OPERAND2);
	printf(BOLDRED "inside the last struct, operand 3: <%s> \n",parsed[1].leftovers);

	printf(BOLDRED "inside the last struct4, operand 3: <%s> \n",parsed[3].leftovers);
*/



	NORMALCOLOR


	validate_file(parsed,parsed_size);
	printf("invoking first scan\n\n");
	if (!first_scan(parsed,parsed_size,&symbols,&ic)){
		fprintf(stderr,KBLUE "Error found in the first scan, skipping to the next file\n");
		NORMALCOLOR
	}
	else
	{
		/*update the addresses of the .mat, .string .data*/
		printf("current IC (main): %d\n",ic);

		update_data_addresses(&symbols,ic);




		printf(KGREEN "Entering second scan\n");
		NORMALCOLOR

		if (second_scan(parsed,parsed_size,&symbols,ic)==FALSE ){
			fprintf(stderr,KBLUE "Error found in the second scan, skipping to the next file\n");
			NORMALCOLOR
		}
		else {
			/*generate files*/
		}

	}

	print_symbol_list(symbols);

	printf("\n\n---===doei!===---\n");
	return EXIT_SUCCESS;
}


