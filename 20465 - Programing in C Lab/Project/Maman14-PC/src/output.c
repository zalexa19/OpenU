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
	fprintf(file,"%s \t %s\n\n",convert_to_base4(IC,0),convert_to_base4(DC,0));



	while(pointer!=NULL){
		String address_base4 = convert_to_base4(pointer->address + INITIAL_ADDRESS ,CONVERTED_VALUE_LENGTH);
		String value_base4 = convert_to_base4(pointer->value,CONVERTED_ADDRESS_LENGTH);

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
	int i,j,temp_n;
	char temp;
	char digits[] = {'A','B','C','D'};
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

/*String convert_to_base4_sums(unsigned int number){
	int BASE = 4;
	int i,j;
	char temp;
	int temp_n;

	char digits[] = {'A','B','C','D'};
	int n_digits;
	String result;

	calculate how binary size
	n_digits=0;
	temp_n=number;

	while (temp_n>0){
		temp_n/=4;
		n_digits++;
	}


	result=allocate_mem_string(n_digits);

	printf("binary size: %d, for number:%d ,",n_digits,number);
	 encode
	i = 0;
	while (number > 0 ) {
		result[i++] = digits[number % BASE];
		number/=4;
	}


	 reverse array
	i--;
	for(j=0; j<i; j++,i--) {
		temp = result[j];
		result[j]=result[i];
		result[i] = temp;
	}

	return result;
}*/

