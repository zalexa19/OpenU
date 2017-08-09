/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */



#include "parser.h"
#include "utils.h"
#define INITIAL_SARRAY_SIZE 8000
/*
 * This macro helps calculating which parts of the array need to be copied
 */
#define CALCSIZE(array_start, index)\
	(index-array_start)*sizeof(char);

/*
 * This macro is used when I want to reresent a string as empty.
 * It allocates 1 memory and inserts \0 as the string value.
 *
 */
#define RETURN_NULL(result) \
	result=allocate_mem_string(1); \
	strcpy(result,"\0");


bodyArray  parse_file (FILE * file){
	String line;
	bodyArray result;
	int cell_counter;

	line=allocate_mem_string(MAXMEM);
	result=allocate_mem_struct(INITIAL_SARRAY_SIZE);

	cell_counter=0;


	fgets(line,MAXMEM,file);


	result[0] = parse_line(line);
	cell_counter = cell_counter +1;

	return result;

}

body  parse_line (String str){
	body result;
	int result_size;
	char * extracted_value;
	char * current_pointer;
	int size;
	int n_skipped_spaces;
	Bool label_exists = FALSE;
	Bool instr_exists = FALSE;
	Bool oper_exists = FALSE;

	extracted_value=allocate_mem_string(MAXMEM);
	current_pointer=str;
	n_skipped_spaces=count_spaces(str);
	current_pointer += n_skipped_spaces;


	printf("|---current pointer: [%s\n\n",current_pointer);

	/*extract label*/
	strcpy(extracted_value,extract_label(current_pointer));
	result_size=strlen(extracted_value)+1;
	result.label=allocate_mem_string(result_size);
	strcpy(result.label,extracted_value);
	if ((strcmp(extracted_value,"\0")) != 0){
		label_exists=TRUE;
	}

	/*extract instruction*/
	strcpy(extracted_value,extract_instruction(current_pointer));
	result_size=strlen(extracted_value)+1;
	result.instruction=allocate_mem_string(result_size);
	strcpy(result.instruction,extracted_value);
	if ((strcmp(extracted_value,"\0")) != 0){
		instr_exists=TRUE;
		printf("++instr_exists=TRUE\n");


	}

	printf("--------After instructing instruction:'%s' \n",current_pointer);

	/*pointers skips the label if exists*/
	if (label_exists==TRUE){
		current_pointer+=strlen(result.label) +1;
		printf("++label exists = TRUE\n");
		/*printf("--------After skipping label:'%s' \n",current_pointer);*/

	}


	n_skipped_spaces=count_spaces(current_pointer);
	current_pointer+=n_skipped_spaces;
	/*	printf("--------After removing spaces and copying to copy:'%s \n",current_pointer);*/


	/*if instruction wasn't receive, we extract the operational*/
	if (instr_exists == FALSE){
		printf("++instr_exists == FALSE\n");
		/*Extract operation*/
		strcpy(extracted_value,extract_operation(current_pointer));
		result_size=strlen(extracted_value)+1;
		printf("extracted value:%s, size: %d\n",extracted_value,result_size);

		memcpy(result.operantion,extracted_value,result_size);
		current_pointer+=result_size-1;

		if ( strcmp(extracted_value,"\0") != 0 ){
			oper_exists=TRUE;
		}
	}
	else {
		/*advance the pointer to the next space after the instruction*/
		printf("++ENTERED ELSE\n");
		size=strlen(result.instruction)+1;
		current_pointer+=size;
		printf("--------After skipping instruction:'%s \n",current_pointer);

		result.operantion=allocate_mem_string(1);
		strcpy(result.operantion,"\0");
		printf("op: %s", result.operantion);

	}

	free(extracted_value);
	fprintf(stderr,"---End of parse line\n");

	return result;

}


String extract_label (String line){
	char * result;
	char * found_char;
	char * array_start;
	int size;

/*	fprintf(stderr,"---Extract_lable: started\n");*/

	found_char = strchr(line,':');
	if (!found_char){
		RETURN_NULL(result)
		return result;

	}
	array_start=line;
	/*size = (found_char-array_start) * sizeof(char);*/
	size = CALCSIZE(array_start,found_char);
/*	fprintf(stderr,"---label length: %d\n",size);*/
	result = allocate_mem_string(size+1);

	strncpy(result,line,size);
/*	printf(" in result:%s\n",result);*/
/*	fprintf(stderr,"---Extract_lable: Finished\n");*/
	memset(result+size,'\0',1);
	return result;

}


char * extract_instruction(char * str){
	String result;
	char * found_char;
	char * array_start;
	char * inspection_start;
	char * inspection_end;
	int size;

	result=allocate_mem_string(strlen(str)+1);

	array_start=str;

/*	fprintf(stderr,"---Extract_instruction: started\n");*/
/*	fprintf(stderr,"---Extracting: dot \n");*/

	found_char = strchr(str,'.');
	if (!found_char){
		RETURN_NULL(result)
		return result;
	}

	/*In which position the dot appears. 1 is added because we care about what's after the dot*/
	/*size = ((found_char - array_start) * sizeof(char))+1;*/
	size=CALCSIZE(array_start,found_char);
	size++;

/*	fprintf(stderr,"---Calculated dot position:%d\n",size);*/
	inspection_start=str+size;
/*	strcpy(copy,inspection_start); Now copy holds everything after the dot*/

/*	fprintf(stderr,"---Extracting: space \n");*/
	inspection_end = strchr(inspection_start,' ');
	if (!inspection_end){
		size=strlen(inspection_start);
		inspection_end=inspection_start+size; /*point to the last cell of the array*/
	}

	size=CALCSIZE(inspection_start, inspection_end);
	strncpy(result,inspection_start,size);
	/*strncpy(result,copy,size);*/
/*		printf("in result: %s\n",result);*/
	fprintf(stderr,"---Extraction_instruction: Completed.\n");

	return result;
}

/*This function runs from the first cell until the first non-blank char and removes the blanks*/
String remove_first_spaces(String str){
	int new_size;
	int counter=0;
	int i=0;
	String result;


	while ( str[i]=='\t' ||  str[i]==' '){
		counter++;
		i++;
	}

	if (counter == 0){
		return str;
	}
	new_size=(strlen(str))-counter;
	result=allocate_mem_string(new_size);
	strcpy(result,str+counter);

	return result;

}

/*counts how many blank chars there are for advancing the pointer*/
int count_spaces (String str){
	int n=0;
	int i=0;

	while ( str[i]=='\t' ||  str[i]==' '){
		n++;
		i++;
	}

	return n;
}

String extract_operation(String str){

	int n_spaces;
	int size;
	String result;
	char * ptr;

	fprintf(stderr,"---Starting extract_operation\n");
	n_spaces= count_spaces(str);
	str +=n_spaces;
	/*printf("--------remove spaces again: '%s \n",str);*/


	ptr=strchr(str,' ');
	printf("ptr: %s\n\n",ptr);
	size=CALCSIZE(str,ptr);

	printf("str: %ssize: %d\n",str,size);

	result=allocate_mem_string(size+1);
	memcpy(result,str,size);
	fprintf(stderr,"---Extract_operation: completed\n");

	return result;
}
