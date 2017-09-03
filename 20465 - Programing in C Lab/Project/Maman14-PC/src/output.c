/*
 * output.c
 *
 *  Created on: Aug 30, 2017
 *      Author: alexz
 */

#include <math.h>
#include "output.h"
#include "malloc.h"
#define FILE_EX_LENGTH 4
#define INITIAL_ADDRESS 100
#define CONVERTED_VALUE_LENGTH 4
#define CONVERTED_ADDRESS_LENGTH 5




void create_obj_file(encoded_ptr encoded_list,String file_name, int IC, int DC){
	FILE * file;
	String full_name;
	encoded_ptr pointer;
	int i;

	full_name=allocate_mem_string(MAXMEM);
	strcpy(full_name,file_name);
	strcat(full_name,".ob");

	printf(BOLDBLUE"file name: %s\n",full_name);



	if (!(file = fopen(full_name,"w"))){
		fprintf(stderr, "unable to find file: %s\n",file_name);
		exit(1);
	}

	pointer=encoded_list;

	/*print file headlines*/
	printf("IC: %d, DC: %d\n",IC,DC);

	printf("IC: %s, DC:%s\n",convert_to_base4(IC,0),convert_to_base4(DC,0));
	fprintf(file,"%s \t %s\n\n",convert_to_base4(IC,0),convert_to_base4(DC,0));


	printf("pointer: %s\n",pointer);

	while(pointer!=NULL){
		String address_base4 = convert_to_base4(pointer->address + INITIAL_ADDRESS ,CONVERTED_VALUE_LENGTH);
		String value_base4 = convert_to_base4(pointer->value,CONVERTED_ADDRESS_LENGTH);

		fprintf(file,"%s \t %s\n",address_base4,value_base4);

		pointer=pointer->next;
	}


	printf("finished creating obj\n");
	fclose(file);
}


void create_entry_file(symbol_ptr symbols,String file_name){
	FILE * file=NULL;
	String full_name;
	symbol_ptr pointer;


	full_name=allocate_mem_string(MAXMEM);
	strcpy(full_name,file_name);
	strcat(full_name,".ent");

	printf("File name: %s\n",full_name);

	pointer=symbols;

	while (pointer != NULL){

		if((pointer->is_entry)==TRUE){
			if(file == NULL) {
				if (!(file = fopen(full_name,"w"))){
					fprintf(stderr, "unable to find file: %s\n",file_name);
					exit(1);
				}
			}
			fprintf(file,"%s \t %s\n",pointer->name,convert_to_base4((pointer->address)+INITIAL_ADDRESS,0));
		}
		pointer=pointer->next;
	}

	printf("finished creating ent\n");

	if(file!=NULL) {
		fclose(file);
	}
	NORMALCOLOR
}


void create_extern_file(symbol_ptr symbols,String file_name,external_labels_ptr external_labels_list){
	FILE * file=NULL;
	String full_name;
	external_labels_ptr list_pointer;


	if (external_labels_list != NULL){

		full_name=allocate_mem_string(strlen(file_name)+4);

		strcpy(full_name,file_name);
		strcat(full_name,".ext");


		printf("EXTERN: File opened-passed\n");

		list_pointer=external_labels_list;


		while( list_pointer != NULL){
			if(file == NULL) {
				if (!(file = fopen(full_name,"w"))){
					fprintf(stderr, "unable to find file: %s\n",file_name);
					exit(1);
				}
			}
			fprintf(file,"%s \t %s\n",list_pointer->value,convert_to_base4((list_pointer->address)+INITIAL_ADDRESS,0));
			list_pointer=list_pointer->next;
			}

	}


		printf("finished creating EXT\n");


		if(file!=NULL) {
			fclose(file);
		}

}

String convert_to_base4(unsigned int number, int length){
	int BASE = 4;
	int i,j,temp_n;
	char temp;
	char digits[] = {'a','b','c','d'};
	String result;

	/* encode */
	i = 0;

	/*if length==0, we don't need to add zeros*/
	if (length==0){
		temp_n=number;
		while (temp_n>0){

			temp_n/=4;
			length++;
		}
	}


	 result= allocate_mem_string(length);

	while (number > 0 && i< length) {
		result[i++] = digits[number % BASE];
		number/=4;
	}

	/* add leading zeros (or 'A's) */
	while(i<length) {
		result[i++] = digits[0];
	}

	result[i] = '\0';

	/* reverse array */
	i--;
	for(j=0; j<i; j++,i--) {
		temp = result[j];
		result[j]=result[i];
		result[i] = temp;
	}

	return result;
}

