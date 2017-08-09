/*
 * utils.c
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#include "utils.h"


int structs_array_size;

String allocate_mem_string (int size){
	String	str = (char*)malloc (size * sizeof(char));
	if (!str){
		fprintf(stderr,"---Unable to allocate memory\n");
	}

/*	fprintf(stderr,"---Memory allocated successfully, size: %d\n",size);*/
	return str;
}



bodyArray allocate_mem_struct (int size){
	bodyArray array=(bodyArray) malloc(sizeof(body)*size);

	if (!array){
		fprintf(stderr,"---Unable to allocate memory to structs-array");
		exit(0);

	}
	return array;

}

int increase_mem_struct (int size,bodyArray array){
	size=size*2;
	bodyArray tmp = (bodyArray)realloc(array,sizeof(body)*size);
	if (!tmp){
		fprintf(stderr,"unable to increase memory to structs-array");
		exit (0);
	}

	array=tmp;
	return size;

}





void print_structs(bodyArray array){
	int i;
	char tmp[15];
	char null[]="null           ";

	i=0;
	printf("-----------------------------------------------------------------------------\n");
	printf("                       STRUCT PRINT:\n");
	printf("-----------------------------------------------------------------------------\n");
	printf("\n");
	printf("LABEL        |");
	printf("INSTRUCTION  |");
	printf("OPERATION    |");
	printf("OPERAND1     |");
	printf("OPERAND2     |");
	printf("OPERAND3     |");
	printf("\n");



	if ((strcmp(array[i].label,"\0") ) !=0){
		strcpy(tmp,array[i].label);
		add_spaces_print(tmp);
		printf("%s",tmp);
	}else printf("%s",null);

	if ((strcmp(array[i].instruction,"\0") ) !=0){
		strcpy(tmp,array[i].instruction);
		add_spaces_print(tmp);
		printf("%s",tmp);

	}else printf("%s",null);

	if ((strcmp(array[i].operantion,"\0") ) !=0){
/*		printf("%s\t",array[i].operantion);*/
		strcpy(tmp,array[i].operantion);
		add_spaces_print(tmp);
		printf("%s",tmp);
	}else printf("%s",null);

	if ((strcmp(array[i].operand1,"\0") ) !=0){
	/*		printf("%s\t",array[i].operantion);*/
			strcpy(tmp,array[i].operand1);
			add_spaces_print(tmp);
			printf("%s",tmp);
		}else printf("%s",null);

	if ((strcmp(array[i].operand2,"\0") ) !=0){
	/*		printf("%s\t",array[i].operantion);*/
			strcpy(tmp,array[i].operand2);
			add_spaces_print(tmp);
			printf("%s",tmp);
		}else printf("%s",null);

	if ((strcmp(array[i].operand3,"\0") ) !=0){
	/*		printf("%s\t",array[i].operantion);*/
			strcpy(tmp,array[i].operand3);
			add_spaces_print(tmp);
			printf("%s",tmp);
		}else printf("%s",null);
}


void add_spaces_print (String  array){
	int length;
	int i=0;

	length=strlen(array);
	while (array[i] != ' '){
		i++;
	}

	i=length;
	for (i=length; i<14; i++){
		array[i]=' ';
	}

}


