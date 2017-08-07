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
#define MAXMEM 100

int main(void) {
	/*String name = allocate_mem_string(4);
	name="alex";
	printf("%s\n",name);
	*/

	FILE * file_dir;
	FILE * temp_file;
	String buff;

	buff=allocate_mem_string(100);




	/*END OF DECLERATIONS*/
	puts("!!!Starting tests!!!\n"); /* prints !!!Hello World!!! */

	/*Opens the file*/
	if (!(temp_file = fopen("src/test.txt","w"))){
		fprintf(stderr,"cannot create temp");
		exit(0);
	}


	fclose(temp_file);

	/*Open the second file*/
	if (!(file_dir = fopen("assembly_input.txt","r"))){
		fprintf(stderr, "unable to find assembly file");
		exit(0);
	}


	while ((fgets(buff,MAXMEM,file_dir)) != NULL){

		puts(buff);

	}

	fclose(file_dir);


/*
	while ( !feof(fd)){
		fgets(buff,199,fd);
		puts(buff);
	}

*/
	return EXIT_SUCCESS;
}
