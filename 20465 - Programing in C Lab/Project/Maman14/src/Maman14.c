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
	FILE * temp_file;
	String buff;

	buff=allocate_mem_string(100);
	/*END OF DECLERATIONS*/
	puts("!!!Starting tests!!!\n"); /* prints !!!Hello World!!! */


	/*Opens the file*/

	temp_file = fopen("test.txt","w");


	if (!(fd = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "cannot create file\n");
		exit(0);
	}
	buff="empty array";

	fputs(buff,temp_file);


	while ( !feof(fd)){
		fgets(buff,199,fd);
		puts(buff);
	}


	fclose(fd);
	return EXIT_SUCCESS;
}
