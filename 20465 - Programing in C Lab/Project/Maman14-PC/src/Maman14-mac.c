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

int main(int argc, char** argv) {

	FILE * input_file;
	String file_name;
	bodyArray parsed;
	int IC,DC,j;
	int number_of_lines;; /*number of lines, including comments and blanks*/
	encoded_ptr encoded_list_head;
	external_labels_ptr external_labels_list;

	int parsed_size=-1;




	/*END OF DECLERATIONS*/

	DC=IC=0;
	create_operation_info_array();




	if (argc==1){
		fprintf(stderr, "File name was not received.\nUsage: [./application <file1> <file2> ...]\n");
	}


	for (j=1;j<argc;j++){

		file_name=allocate_mem_string(strlen(argv[j])+3);
		number_of_lines=0;
		strcpy(file_name,argv[j]);
		strcat(file_name,AS);
		encoded_list_head=NULL;
		symbol_ptr symbols=NULL;
		external_labels_list=NULL;


		if (!(input_file = fopen(file_name,"r"))){
			fprintf(stderr, "unable to find assembly file");
			exit(1);
		}


		parsed=parse_file(input_file, &parsed_size,&number_of_lines);
		fclose(input_file);



		if (validate_file(parsed,parsed_size)==FALSE){
			fprintf(stderr, "Error found in file %s, skipping to the next file\n",file_name);

		}
		else
		{
			print_structs(parsed,parsed_size);
			if (first_scan(parsed,parsed_size,&symbols,&IC,&DC,&external_labels_list)==FALSE){
				fprintf(stderr,KBLUE "Error found in the first scan, skipping to the next file\n");
				NORMALCOLOR
			}
			else
			{
				print_symbol_list(symbols);

				/*update the addresses of the .mat, .string .data*/
				update_data_addresses(&symbols,IC);

				printf(KGREEN "Entering second scan\n");
				NORMALCOLOR

				if (second_scan(parsed,parsed_size,&symbols,IC,&encoded_list_head,DC,&external_labels_list)==FALSE ){
					fprintf(stderr,KBLUE "Error found in the second scan, skipping to the next file\n");
					NORMALCOLOR
				}
				else {
					external_labels_ptr p;

					p=external_labels_list;
					while (p !=NULL){
						p=p->next;
					}
					/*Create obj file*/
					create_obj_file(encoded_list_head,argv[j],IC,DC);
					create_entry_file(symbols,argv[j]);
					create_extern_file(symbols,argv[j],external_labels_list);

				}

			}
		}


	}
	NORMALCOLOR





	free(encoded_list_head);
	free(file_name);
	printf("\n\n---===doei!===---\n");

	return 0;
}


