/*
 * output.c
 *
 *  Created on: Aug 30, 2017
 *      Author: alexz
 */

#include "output.h"
#define FILE_EX_LENGTH 4
#define INITIAL_ADDRESS 100






void create_obj_file(encoded_ptr encoded_list,String file_name){
	FILE * file;
	String full_name;
	encoded_ptr pointer;
	int i;

	full_name=allocate_mem_string(MAXMEM);
	strcpy(full_name,file_name);

	strcat(full_name,".txt");
	printf(BOLDBLUE"file name: %s\n",full_name);

	/*fix this*/

	if (!(file = fopen(full_name,"w"))){
		fprintf(stderr, "unable to find file: %s\n",file_name);
		exit(1);
	}

	pointer=encoded_list;
	while(pointer!=NULL){
		String address_base4 = convert_to_base4(pointer->address + INITIAL_ADDRESS ,4);
		String value_base4 = convert_to_base4(pointer->value,5);

		fprintf(file,"%s \t %s\n",address_base4,value_base4);

		pointer=pointer->next;
	}




}


void_create_entry_file(encoded_ptr symbols){

}

void create_extern_file(encoded_ptr symbols){

}

String convert_to_base4(unsigned int number, int length){
	int BASE = 4;
	int i,j;
	char temp;
	char digits[] = {'A','B','C','D'};
	String result = allocate_mem_string(length);

	/* encode */
	i = 0;
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
