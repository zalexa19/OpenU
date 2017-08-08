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

	fprintf(stderr,"---Memory allocated successfully, size: %d\n",size);
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

	i=0;
	printf("label\tinstruction\toperation\tpoer1\toper2\toper3\toper4\t\n");


	printf("printing the actual structs\n");
	/*printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n",array[i].label,array[i].instruction,array[i].operantion,array[i].openrand1,array[i].operand2,array[i].operand3,array[i].operand4);

*/
	if ((strcmp(array[i].label,"\0") ) !=0){
		printf("%s\t",array[i].label);
	}else printf("null\n");
}



