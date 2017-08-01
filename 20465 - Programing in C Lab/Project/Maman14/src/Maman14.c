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
#define ARRAYSIZE 200

int main(void) {
	/*String name = allocate_mem_string(4);
	name="alex";
	printf("%s\n",name);
	*/

	FILE * fd;
	String buff;
	char character;
	int i=0;

	/*END OF DECLERATIONS*/
	puts("!!!Hello World!!!\n"); /* prints !!!Hello World!!! */


	/*Opens the file*/
	if (!(fd = fopen("assembly_input.txt","w"))){
		fprintf(stderr, "cannot create file\n");
		exit(0);
	}

	while ( !feof(fd)){

		fgets(buff,199,fd);
		puts(buff);
	}


	fclose(fd);
	return EXIT_SUCCESS;
}
