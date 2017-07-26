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

int main(void) {
	puts("!!!Hello World!!!\n"); /* prints !!!Hello World!!! */

	String name = allocate_mem_string(4);
	name="alex";
	printf("%s\n",name);

	return EXIT_SUCCESS;
}
