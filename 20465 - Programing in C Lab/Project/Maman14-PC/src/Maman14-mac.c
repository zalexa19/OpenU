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
#include "output.h"


int main(void) {

	FILE * input_file;
	bodyArray parsed;
	int ic,array_size,i;
	int parsed_size=-1;
	int number_of_lines=0; /*number of lines, including comments and blanks*/
	symbol_ptr symbols=NULL;
	int* binary_result;
	encoded_ptr encoded_list_head;
	String obj_file_name;



	/*END OF DECLERATIONS*/
	ic=0;
	create_operation_info_array();


	if (!(input_file = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}


	parsed=(bodyArray)parse_file(input_file, &parsed_size,&number_of_lines);
	fclose(input_file);



	print_structs(parsed,parsed_size);
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
		print_symbol_list(symbols);




		printf(KGREEN "Entering second scan\n");
		NORMALCOLOR

		if (second_scan(parsed,parsed_size,&symbols,ic,&encoded_list_head,&array_size)==FALSE ){
			fprintf(stderr,KBLUE "Error found in the second scan, skipping to the next file\n");
			NORMALCOLOR
		}
		else {
			/*generate files*/
			/*printf("result in main:\n");
			print_binary_array(binary_result,array_size);*/


			/*prints the coded array*/

/*			print_encoded_struct(encoded_list_head);*/
/*			print_binary_array(binary_result,array_size);*/



			/*Create obj file*/
			printf("starting to write to file\n");
			obj_file_name=allocate_mem_string(5);
			obj_file_name="alex";
			create_obj_file(encoded_list_head,obj_file_name);

		}

	}


	printf("\n\n---===doei!===---\n");
	return EXIT_SUCCESS;
}


