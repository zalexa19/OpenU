/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 *
 *
 *
 *      The whole purpose of this file is to parse the assembly file.
 *      It receives the file which needs to be parsed, and pointers to two ints:
 *      1) one that counts how many lines are in the file (including comments)
 *      2) the other counts how many lines were parsed. (excluding comments)
 *
 *      each line read from the file is "converted" to a struct, so when the whole file is parse_file function returns an array of these structs.
 *      label: extracted by searching ":"
 *      command: extracted by searching ".". if found, then it's an instruction (.string,.data), else - it's an operational command
 *      operands are extracted depending on the command received.
 *
 */


#include "parser.h"
#include "utils.h"

#define INITIAL_SARRAY_SIZE 8000 /*size of the result structs array*/
#define MAX_BRACKETS 2


/*
 * This macro is used when I want to represent a string as empty.
 * It allocates  memory in the size of 1 and inserts \0 as the string value.
 *
 */
#define RETURN_NULL(result) \
	result=allocate_mem_string(1); \
	strcpy(result,"\0");

/*
 * Frees the "extract_value" that receives from the function
 * Allocates new memory
 */
#define REALLOCATE_EXTRACTED_VALUE\
	free(extracted_value);\
	extracted_value=allocate_mem_string(strlen(current_pointer));


/*
 * This macro counts how many values were received for .data or .mat
 */
#define COUNT_DATA_STRINGS_SIZE\
		i=0;\
		while(current_pointer[i]!='\0'){\
			if(current_pointer[i]==','){\
				data_array_size++;\
			}\
			i++;\
		}\
		if (data_array_size>0 || i>0){\
			data_array_size++;\
		}



parsed_item_ptr  parse_file (FILE * file, int* parsed_size, int * n_lines){
	String line;
	parsed_item_ptr parsed_file;
	int cell_counter;

	line=allocate_mem_string(MAXMEM);
	parsed_file=allocate_mem_struct(INITIAL_SARRAY_SIZE);
	cell_counter=0;

	while (  (fgets(line,MAXMEM,file)) != NULL){
		*n_lines+=1;

		/*parses lines that are not empty, nor comments */
		if (check_empty_line(line)==FALSE && line[0]!=';'){
			parsed_file[cell_counter] = parse_line(line,*n_lines);
			cell_counter++;
		}

	}

	/*updates outside integers with the correct size*/
	if (cell_counter>0){
		*parsed_size=cell_counter;
	}else{
		*parsed_size=0;
	}

	free(line);
	return parsed_file;
}

/*
 * This function creates that struct that represents a line
 * it receives an str which is the line itself.
 * I use a pointer to keep track of which part of the line I'm working on, and "extracted_value" is a temporary char * that stores
 * the derived value before copying it into the struct itself.
 */

parsed_item parse_line(String str, int line_number){
	parsed_item result;
	int i;
	int extracted_value_length;
	char * extracted_value;
	char * current_pointer;
	int spaces; /*holds the number of spaces until the next char*/
	int data_array_size=0; /*stores the number of values received for .mat or .data*/
	int received_line_length; /*stores the length of current line*/

	result.line_number=line_number;
	result.op1_type=type_unrecognized;
	result.op2_type=type_unrecognized;
	result.valid=TRUE;


	/*replaces \n received in the file with \0*/
	received_line_length=strlen(str);
	str[received_line_length-1]='\0'; /*replaces \n with \0*/
	/*gets rid of unwanted spaces*/
	spaces=count_spaces(str);
	str+=spaces;
	current_pointer=str;


	/*Extract label*/
	/*
	 * If ':' exists, we extract the label
	 */

	if (strchr(current_pointer,':')!= NULL){
		extracted_value=extract_label(current_pointer);
		extracted_value_length=strlen(extracted_value)+1;

		result.label=allocate_mem_string(extracted_value_length);
		strcpy(result.label,extracted_value);
		current_pointer+=extracted_value_length;/* Advance current_pointer to point to after ':'*/
		REALLOCATE_EXTRACTED_VALUE
	}
	else {/*if label was not received, I put \0 inside the struct*/
		result.label=allocate_mem_string(1);
		strcpy(result.label,"\0");
	}


	/*extract instruction*/
	if (strchr(current_pointer,'.')!= NULL){
		/*Instruction exists:
		result.Instruction should be updated
		current pointer should be advanced
		operation should be updated with \0
		*/
		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;

		extracted_value=extract_instruction(current_pointer);
		extracted_value_length=strlen(extracted_value)+1;

		result.instruction=allocate_mem_string(extracted_value_length);
		strcpy(result.instruction,extracted_value);

		current_pointer+=extracted_value_length;
		REALLOCATE_EXTRACTED_VALUE;

		result.operantion=allocate_mem_string(1);
		strcpy(result.operantion,"\0");

		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;


	}
	else {
		/*
		 * Need to extract operation.
		 */
		result.instruction=allocate_mem_string(1);
		strcpy(result.instruction,"\0");

		extracted_value=extract_operation(current_pointer);
		extracted_value_length=strlen(extracted_value)+1;

		result.operantion=allocate_mem_string(extracted_value_length);
		strcpy(result.operantion,extracted_value);
		current_pointer+=extracted_value_length;

		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;
		REALLOCATE_EXTRACTED_VALUE;

		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;
		}


	/*PARSING OPERANDS*/

	if (strcmp(result.instruction,DATA)==0){
		/*Counting number of operands*/
		COUNT_DATA_STRINGS_SIZE

		result.data_values_number=data_array_size;
		result.data_string_array =(String*)allocate_mem_general(data_array_size,sizeof(String));


		if (result.data_string_array != NULL){
			result.data_string_array=extract_data_strings(current_pointer,data_array_size);
		}else {
			fprintf(stderr,"Unable to allocate memory to a matrix\nMoving on..\n");
		}

		current_pointer+=(i+data_array_size);

		extracted_value_length=strlen(current_pointer);
		result.leftovers=allocate_mem_string(extracted_value_length);
		strcpy(result.leftovers,current_pointer);

	}
	else if (strcmp(result.instruction,MAT)==0){
		extracted_value=parse_mat_size(current_pointer);
		extracted_value_length=strlen(extracted_value)+1;



		/*EXTRACT OPERAND1*/
		result.operand1=allocate_mem_string(extracted_value_length);
		strcpy(result.operand1,extracted_value);
		current_pointer+=extracted_value_length;

		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;
		REALLOCATE_EXTRACTED_VALUE;


		/*EXTRACT OPERAND2*/
		COUNT_DATA_STRINGS_SIZE

		result.data_values_number=data_array_size;
		result.data_string_array=(String*)allocate_mem_general(data_array_size+1,sizeof(String));

		result.data_string_array=extract_data_strings(current_pointer,data_array_size);

		current_pointer+=(data_array_size+i);


		extracted_value_length=strlen(current_pointer);
		result.leftovers=allocate_mem_string(extracted_value_length);
		strcpy(result.leftovers,current_pointer);


	}

	else {
		if (strlen(current_pointer)>0){
			/*Extracting OPERAND1*/

			if (strcmp(result.instruction,STR)==0){
				result.operand1=allocate_mem_string(strlen(current_pointer)+1);
				strcpy(result.operand1,current_pointer);
				RETURN_NULL(result.operand2)
				RETURN_NULL(result.leftovers)

			}

			else {
				extracted_value=extract_operand(current_pointer);
				extracted_value_length=strlen(extracted_value);

				result.operand1=allocate_mem_string(extracted_value_length+1);
				strcpy(result.operand1,extracted_value);


				current_pointer+=extracted_value_length;
				if (extracted_value_length>0){
					current_pointer+=1;/*skip the first ','*/
				}
				REALLOCATE_EXTRACTED_VALUE


				if (strcmp(result.instruction,STR)!=0){

					/*Extracting OPERAND2*/
					spaces=count_spaces(current_pointer);
					current_pointer+=spaces;

					extracted_value=extract_operand(current_pointer);
					extracted_value_length=strlen(extracted_value);
					result.operand2=allocate_mem_string(extracted_value_length+1);
					strcpy(result.operand2,extracted_value);

					if (extracted_value_length>0){
						current_pointer+=extracted_value_length;
					}

					REALLOCATE_EXTRACTED_VALUE

					/*Extract Leftovers*/
					spaces=count_spaces(current_pointer);
					current_pointer+=spaces;

					extracted_value=extract_operand(current_pointer);
					extracted_value_length=strlen(extracted_value);
					result.leftovers=allocate_mem_string(extracted_value_length+1);
					strcpy(result.leftovers,extracted_value);

				}
				else {
					/*clear garbage from operand2, when we use STR*/
					RETURN_NULL(result.operand2)
					RETURN_NULL(result.leftovers)
				}
			}
		}
		else {
			RETURN_NULL(result.operand1)
			RETURN_NULL(result.operand2)
			RETURN_NULL(result.leftovers)

		}

	}

	free(extracted_value);
	return result;

}


/*
 * Receives a substring
 * Counts how many operands there are by counting ','
 * move with a pointer - count each operand, allocate memory in required size and split
 */
String extract_operand (String str){
	int operand_size;
	int count=0;
	int i;
	int n_spaces;
	String ptr;
	String result;

	n_spaces=count_spaces(str);
	str+=n_spaces;

	ptr=strchr(str,',');

	i=0;
	if (!ptr){
		/*',' was not found so we could be the last operand*/
		/*Counting how many chars are in the sting*/

		while (str[i] != '\0'){
			count++;
			i++;
		}
		ptr=str+count;

	}

	operand_size=CALCSIZE(str,ptr);
	n_spaces=reverse_count_spaces(str,ptr);
	operand_size=operand_size-n_spaces;
	result=allocate_mem_string(operand_size+1);
	strncy_safe(result,str,operand_size);
	return result;

}


/*
 * This function receives a string, and derives the following: '[][]'
 * This function counts how many chars are not spaces, then copies them to a new array.
 * Function returns the extracted value [][]
 * - assuming that for .mat, the value will always be in format [x][x]
 */
String parse_mat_size (String str){
	String result;
	int op_length;

	op_length=0;
	op_length=count_non_spaces(str);

	result=allocate_mem_string(op_length+1);
	strncy_safe(result,str,op_length);

	return result;
}

/*
 * label is extracted by searching for the first ':' found
 * Then, I calculate the size of the substring from beginning of line, until the :
 * I copy this number of chars into the result array, and return it
 * in allocatate_mem_string, I always add 1 to save spaces for the '\0'
 */

String extract_label (String line){
	char * result;
	char * found_char;
	char * array_start;
	int size;


	found_char = strchr(line,':');
	if (!found_char){
		RETURN_NULL(result)
		return result;

	}
	array_start=line;
	size = CALCSIZE(array_start,found_char);
	result = allocate_mem_string(size+1);

	strncpy(result,line,size);
	memset(result+size,'\0',1);
	return result;

}


/*
 * Extraction of instruction is done by searching the first '.'
 * the instruction command itself will be all the chars from . to the first spaces or \t
 */

char * extract_instruction(char * str){
	String result;
	char * found_char;
	char * array_start;
	char * inspection_start;
	char * inspection_end;
	int size;

	result=allocate_mem_string(strlen(str)+1);
	array_start=str;

	found_char = strchr(str,'.');
	if (!found_char){
		RETURN_NULL(result)
		return result;
	}

	/*In which position the dot appears. 1 is added to exclude the dot from the calulations*/
	size=CALCSIZE(array_start,found_char);
	size++;

	inspection_start=str+size;
	inspection_end = str+(count_non_spaces(str));


	size=CALCSIZE(inspection_start, inspection_end);
	strncy_safe(result,inspection_start,size);

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

	while ( (str[i]=='\t' ||  str[i]==' ') && i<strlen(str)){
		n++;
		i++;
	}

	return n;
}


/*
 * Counts the spaces backwords
 */
int reverse_count_spaces (String start, String end){
	int size,i,n;
	i=0;
	size=CALCSIZE(start,end);

	while (i<size && start[i]!=' ' && start[i]!='\t'){
		i++;
	}

	n=size-i;

	return n;
}


/*
 * extracts the param to be used as operation
 * copy the value starting from current pointer (excluding spaces) and until the next space we find
 * this is copied into the result
 */

String extract_operation(String str){
	int n_spaces;
	int size=0;
	String result;
	int i;
	char c;

	n_spaces= count_spaces(str);
	str +=n_spaces;

	i=0;
	c=str[i];
	while (c != ' ' && c!='\t' && c!='\n'){
		size++;
		i++;
		c=str[i];
	}

	result=allocate_mem_string(size+1);

	strncy_safe(result,str,size);
	return result;
}

/*
 * Checks if the str consists only of spaces by going over each character
 */
Bool check_empty_line(String str){
	int i;
	int size;
	Bool empty = TRUE;
	size=strlen(str);

	i=0;
	while (i<size && empty==TRUE){
		if (str[i]!='\t' && str[i]!='\n' && str[i]!=' '){
			empty=FALSE;

		}
		i++;
	}

	return empty;
}

/*
 * This function extracts the parameters received for data.
 * It creates a separated string for each section devided by ','
 *
 * Input: a pointer to a string, which holds all the values as one chunk
 * Output: an array of char*, where each parameter stored in a separated cell
 */
String* extract_data_strings(char* str, int array_size){
	String* final_array;
	char* pointer;
	int size;
	int i;
	int cell=0;
	int n_spaces;

	final_array=(String*)allocate_mem_general(array_size+1,sizeof(String));


	if (strcmp(str,"\0")==0){
		final_array[0]="\0";
		return final_array;
	}


	for (i=0;i<array_size; i++){
			/*skip spaces at the start of str*/
			n_spaces=count_spaces(str);
			str+=n_spaces;

			/*find ','*/
			pointer=strchr(str,',');

		if (pointer != NULL){
			size=CALCSIZE(str,pointer);
			n_spaces=reverse_count_spaces(str,pointer);
			size-=n_spaces;

			final_array[cell]=allocate_mem_string(size+1);

			strncy_safe(final_array[cell],str,size);
			str=pointer+1;
			cell++;
		} else {
			n_spaces=count_spaces(str);
			str+=n_spaces;

			/*count how many chars until next spaces*/
			final_array[cell]=allocate_mem_string((count_non_spaces(str))+1);
			strncy_safe(final_array[cell],str,(count_non_spaces(str)));
			cell++;

			final_array[cell]=allocate_mem_string(1);
			final_array[cell]='\0';


		}

	}

	return final_array;
}

/*
 * counts chars that are not tabs and spaces that appear in a row
 * receives a string to count in, return the number
 */

int count_non_spaces(String str){
	int i;
	char c;
	Bool found_space=FALSE;

	i=0;
	while (i<strlen(str) && found_space==FALSE){
		c=str[i];

		if (c!=' ' && c!='\t'){
			i++;

		}else{
			found_space=TRUE;
		}

	}

	return i;

}


