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
#define FILE_EXTENT_LENGTH 3

/*
 * This program is devided into several parts:
 * 1. Parser
 * 2. Input validator
 * 3. first scan
 * 4. second scan
 * 5. output file generator
 * 
 * 
 * This main is responsible for invoking each module.
 * 
 * the main receives file names, and for each file name, opens the file.
 * 
 * 
 * 
 */




int main(int argc, char** argv) {
	FILE * input_file; 
	String file_name;
	parsed_item_ptr parsed;
	int ic,dc,j;
	symbol_ptr symbols;
	int number_of_lines; /*counts the number of lines in the input file, including comments and blanks*/
	encoded_ptr encoded_list_head; /*list of encoded line, ready to be printed. relevant for second scan*/
	external_labels_ptr external_labels_list; /*list of all lines that include an external label as an operand. updated in the second scan*/

	int parsed_size=-1;
	/*END OF DECLERATIONS*/



	/*this creates an array with info about operational commands. This is required for the validation stage.
	 * For example, which operand types are allowed for a command
	 *
	 */
	create_operation_info_array();


	if (argc==1){
		fprintf(stderr, "File name was not received.\nUsage: [./assembler <file1> <file2> ...]\n");
		exit(1);
	}


	for (j=1;j<argc;j++){
		dc=ic=0;

		file_name=allocate_mem_string(strlen(argv[j])+FILE_EXTENT_LENGTH);
		number_of_lines=0;
		strcpy(file_name,argv[j]);
		strcat(file_name,AS);
		encoded_list_head=NULL;
		symbols=NULL; /*this list includes info about the symbols - address, if external, if instruction, etc.*/
		external_labels_list=NULL;

		printf("\nworking on %s\n\n",file_name);

		if (!(input_file = fopen(file_name,"r"))){
			fprintf(stderr, "Unable to find assembly file\n");
			exit(1);
		}

		/*parse input file*/
		parsed=parse_file(input_file, &parsed_size,&number_of_lines);
		fclose(input_file);



		if (validate_file(parsed,parsed_size)==FALSE){
			fprintf(stderr, "Validation stage failed for file %s, skipping to the next file\n",file_name);

		}
		else
		{
			if (first_scan(parsed,parsed_size,&symbols,&ic,&dc)==FALSE){
				fprintf(stderr, "First scan failed for file %s, skipping to the next file\n",file_name);
			}
			else
			{
				/*update the addresses of the .mat, .string .data*/
				update_data_addresses(&symbols,ic);

				if (second_scan(parsed,parsed_size,&symbols,ic,&encoded_list_head,dc,&external_labels_list)==FALSE ){
					fprintf(stderr, "Second scan failed for file %s, skipping to the next file\n",file_name);
				}
				else {
					/*Create obj file*/
					create_obj_file(encoded_list_head,argv[j],ic,dc);
					create_entry_file(symbols,argv[j]);
					create_extern_file(symbols,argv[j],external_labels_list);

				}

			}
		}

	}

	free(encoded_list_head);
	free(file_name);
	free(external_labels_list);
	free(encoded_list_head);

	printf("\n\n---===GOODBYE!===---\n");

	return 0;
}


