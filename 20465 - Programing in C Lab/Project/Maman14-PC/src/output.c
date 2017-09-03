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
#define CONVERTED_VALUE_LENGTH 4
#define CONVERTED_ADDRESS_LENGTH 5
#define OBJ_FILE_NAME ".ob"
#define EXT_FILE_NAME ".ext"
#define ENT_FILE_NAME ".ent"




void create_obj_file(encoded_ptr encoded_list,String file_name, int IC, int DC){
	FILE * file;
	String full_name;
	encoded_ptr pointer;
	String address_base4,value_base4;
	int i;
	int file_name_length=((strlen(file_name)+(strlen(OBJ_FILE_NAME)))+1);

	full_name=allocate_mem_string(file_name_length);
	strcpy(full_name,file_name);
	strcat(full_name,OBJ_FILE_NAME);

	printf(BOLDBLUE"file name: %s\n",full_name);



	if (!(file = fopen(full_name,"w"))){
		fprintf(stderr, "unable to find file: %s\n",file_name);
		exit(1);
	}

	pointer=encoded_list;

	/*print file headlines*/
/*	printf("current pointer: %d\n",pointer->address);*/
/*	printf("converted IC and DC and printing to file: \n");*/
	printf("IC: %s, DC:%s\n",convert_to_base4(IC,0),convert_to_base4(DC,0));
	fprintf(file,"%s \t %s\n",convert_to_base4(IC,0),convert_to_base4(DC,0));
/*	printf("DONE\n");
	printf("encoding now\n");*/

	while(pointer!=NULL){
		address_base4 = convert_to_base4(pointer->address ,CONVERTED_VALUE_LENGTH);
		value_base4 = convert_to_base4(pointer->value,CONVERTED_ADDRESS_LENGTH);
		fprintf(file,"%s \t %s\n",address_base4,value_base4);
		pointer=pointer->next;
	}
	free(full_name);
	fclose(file);

	printf("finished creating obj\n");

}


void create_entry_file(symbol_ptr symbols,String file_name){
	FILE * file=NULL;
	String full_name;
	symbol_ptr pointer;


	full_name=allocate_mem_string(MAXMEM);
	strcpy(full_name,file_name);
	strcat(full_name,ENT_FILE_NAME);

NORMALCOLOR

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

	printf("finished creating ENT\n");

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

		full_name=allocate_mem_string(strlen(file_name)+strlen(EXT_FILE_NAME)+1);

		strcpy(full_name,file_name);
		strcat(full_name,EXT_FILE_NAME);


		list_pointer=external_labels_list;


		while( list_pointer != NULL){
			if(file == NULL) {
				if (!(file = fopen(full_name,"w"))){
					fprintf(stderr, "unable to find file: %s\n",file_name);
					exit(1);
				}
			}
			fprintf(file,"%s \t %s\n",list_pointer->value,convert_to_base4((list_pointer->address),0));
			list_pointer=list_pointer->next;
			}

	}


		printf("finished creating EXT\n");


		if(file!=NULL) {
			fclose(file);
		}
		free(full_name);
}

String convert_to_base4(unsigned int number, int length){
	int BASE = 4;
	int i,j,temp_n;
	char temp;
	char digits[] = {'a','b','c','d'};
	String result;

/*
	printf(KGREEN"--Started convert to base 4\n");
	printf("number: %d, length: %d\n",number,length);
*/

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

/*	printf("1\n");*/

	 result= allocate_mem_string(length+1);

/*	 printf("2\n");*/
	while (number > 0 && i< length) {
		result[i++] = digits[number % BASE];
		number/=4;
	}
/*	printf("3\n");*/
	/* add leading zeros (or 'A's) */
	while(i<length) {
		result[i++] = digits[0];
	}
/*	printf("4\n");*/
	result[i] = '\0';
/*	printf("5\n");*/
	/* reverse array */
	i--;
	for(j=0; j<i; j++,i--) {
		temp = result[j];
		result[j]=result[i];
		result[i] = temp;
	}
/*	printf("6\n");
	printf(KGREEN"finished convert to base 4\n\n");*/
	NORMALCOLOR
	return result;
}

