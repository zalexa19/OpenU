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




/*
 * This function creates the ob file.
 * it recieve the file name and adds the extension.
 * then it scans the encoded_list and prints it into a file
 * if there's an issue with file, function stops and we continue to the next one
 */
Bool create_obj_file(encoded_ptr encoded_list,String file_name, int IC, int DC){
	FILE * file;
	String full_name;
	encoded_ptr pointer;
	String address_base4,value_base4;
	int file_name_length=((strlen(file_name)+(strlen(OBJ_FILE_NAME)))+1);

	full_name=allocate_mem_string(file_name_length);
	strcpy(full_name,file_name);
	strcat(full_name,OBJ_FILE_NAME);


	if (!(file = fopen(full_name,"w"))){
		fprintf(stderr, "unable to find file: %s\n",file_name);
		return FALSE;
	}

	pointer=encoded_list;

	fprintf(file,"%s \t %s\n",convert_to_base4(IC,0),convert_to_base4(DC,0));

	while(pointer!=NULL){
		address_base4 = convert_to_base4(pointer->address ,CONVERTED_VALUE_LENGTH);
		value_base4 = convert_to_base4(pointer->value,CONVERTED_ADDRESS_LENGTH);
		fprintf(file,"%s \t %s\n",address_base4,value_base4);
		pointer=pointer->next;
	}
	free(full_name);
	fclose(file);

	return TRUE;
}


/*
 * function prints from the symbols list into the file only label which have is_entry=TRUE;
 * it was set in a previous stage
 * function return false if there is an issue with creating a file.
 */

Bool create_entry_file(symbol_ptr symbols,String file_name){
	FILE * file=NULL;
	String full_name;
	symbol_ptr pointer;


	full_name=allocate_mem_string(MAXMEM);
	strcpy(full_name,file_name);
	strcat(full_name,ENT_FILE_NAME);

	pointer=symbols;

	while (pointer != NULL){

		if((pointer->is_entry)==TRUE){
			if(file == NULL) {
				if (!(file = fopen(full_name,"w"))){
					fprintf(stderr, "unable to find file: %s\n",file_name);
					return FALSE;
				}
			}
			fprintf(file,"%s \t %s\n",pointer->name,convert_to_base4((pointer->address)+INITIAL_ADDRESS,0));
		}
		pointer=pointer->next;
	}

	if(file!=NULL) {
		fclose(file);
	}

	return TRUE;
}

/*
 * function prints from the external_labels_list list into the extern file;
 * it was set in a previous stage
 * function return false if there is an issue with creating a file.
 */

Bool create_extern_file(symbol_ptr symbols,String file_name,external_labels_ptr external_labels_list){
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
					return FALSE;
				}
			}
			fprintf(file,"%s \t %s\n",list_pointer->value,convert_to_base4((list_pointer->address),0));
			list_pointer=list_pointer->next;
			}

	}

		if(file!=NULL) {
			fclose(file);
		}
		free(full_name);
		return TRUE;
}

/*
 * function receives a number, and converts it into a strange base 4.
 * length specifies the format of the result. if the result length is less then received, zeros are added.
 * function return a string of the convert result
 */
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

	 result= allocate_mem_string(length+1);


	while (number > 0 && i< length) {
		result[i++] = digits[number % BASE];
		number/=4;
	}

	while(i<length) {
		result[i++] = digits[0];
	}

	result[i] = '\0';

	i--;
	for(j=0; j<i; j++,i--) {
		temp = result[j];
		result[j]=result[i];
		result[i] = temp;
	}


	return result;
}

