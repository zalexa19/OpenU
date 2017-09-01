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
	int external_labels_size;
	String file_name;
	bodyArray parsed;
	int IC,DC,array_size,i,j;
	int parsed_size=-1;
	int number_of_lines=0; /*number of lines, including comments and blanks*/
	symbol_ptr symbols=NULL;
	int* binary_result;
	encoded_ptr encoded_list_head;
	String obj_file_name;
	external_labels_ptr external_labels_list;
	String * external_labels;



	/*END OF DECLERATIONS*/

	DC=IC=0;
	create_operation_info_array();
	external_labels=(String*)allocate_mem_general(MAXMEM,sizeof(String));
	external_labels_size=0;
	external_labels_list=NULL;
	if (argc==1){
		fprintf(stderr, "File name was not received.\n");
	}


	for (j=1;j<argc;j++){

		file_name=allocate_mem_string(strlen(argv[j]+3));
		file_name=argv[j];
		strcpy(file_name,argv[j]);
		strcat(file_name,AS);



		obj_file_name=allocate_mem_string(strlen(argv[j]));
		strcpy(obj_file_name,file_name);


		if (!(input_file = fopen(file_name,"r"))){
			fprintf(stderr, "unable to find assembly file");
			exit(0);
		}


		parsed=(bodyArray)parse_file(input_file, &parsed_size,&number_of_lines);
		fclose(input_file);



		print_structs(parsed,parsed_size);
		NORMALCOLOR


		validate_file(parsed,parsed_size);
		printf("invoking first scan\n\n");
		if (!first_scan(parsed,parsed_size,&symbols,&IC,&DC,&external_labels_list,&external_labels_size)){
			fprintf(stderr,KBLUE "Error found in the first scan, skipping to the next file\n");
			NORMALCOLOR
		}
		else
		{
			/*update the addresses of the .mat, .string .data*/


			update_data_addresses(&symbols,IC);
			print_symbol_list(symbols);

/*			test
			printf(BOLDRED"External labels array:\n");
			print_mat(external_labels,external_labels_size);
			NORMALCOLOR*/

			printf(KGREEN "Entering second scan\n");
			NORMALCOLOR

			if (second_scan(parsed,parsed_size,&symbols,IC,&encoded_list_head,&array_size,&external_labels_list)==FALSE ){
				fprintf(stderr,KBLUE "Error found in the second scan, skipping to the next file\n");
				NORMALCOLOR
			}
			else {
				int k;
				external_labels_ptr p;


				printf("printing external list:\n");
				p=external_labels_list;
				while (p !=NULL){
					printf("value: %s\n",external_labels_list->value);
					p=p->next;
				}
				/*Create obj file*/
				printf("starting to write to file\n");

				create_obj_file(encoded_list_head,obj_file_name,IC,DC);
/*				create_entry_file(symbols,obj_file_name);*/



				create_extern_file(symbols,obj_file_name,external_labels_list,external_labels_size);

			}

		}
	}

	printf("\n\n---===doei!===---\n");
	return 0;
}


