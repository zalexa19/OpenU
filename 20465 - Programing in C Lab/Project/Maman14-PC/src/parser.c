/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */



#include "parser.h"
#include "utils.h"

#define INITIAL_SARRAY_SIZE 8000
#define ADDEDSIZE 1
#define MAXBRACKETS 2


/*
 * This macro is used when I want to reresent a string as empty.
 * It allocates 1 memory and inserts \0 as the string value.
 *
 */
#define RETURN_NULL(result) \
	result=allocate_mem_string(1); \
	strcpy(result,"\0");

/*
 * Frees the extract_value that receives from the function
 * Allocates new memory
 */
#define REALLOCATE_EXTRACTED_VALUE\
	free(extracted_value);\
	extracted_value=allocate_mem_string(strlen(current_pointer));


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

bodyArray  parse_file (FILE * file, int* parsed_size, int * n_lines){
	String line;
	bodyArray parsed_file;
	int cell_counter;

	line=allocate_mem_string(MAXMEM);
	parsed_file=allocate_mem_struct(INITIAL_SARRAY_SIZE);
	cell_counter=0;

	NORMALCOLOR
	while (  (fgets(line,MAXMEM,file)) != NULL){
		*n_lines+=1;

		if (check_empty_line(line)==FALSE && line[0]!=';'){

			parsed_file[cell_counter] = parse_line(line,*n_lines);
			cell_counter++;
		}

	}

	if (cell_counter>0){
		*parsed_size=cell_counter;
	}else{
		*parsed_size=0;
	}

	free(line);
	return parsed_file;
}


body parse_line(String str, int line_number){
	body result;
	int i,num_commas;
	int extracted_value_length;
	char * extracted_value;
	char * current_pointer;
	int spaces;
	int data_array_size=0;
	int received_line_length;

	result.line_number=line_number;
	result.op1_type=type_unrecognized;
	result.op2_type=type_unrecognized;

	result.valid=TRUE;





	received_line_length=strlen(str);
	str[received_line_length-1]='\0'; /*replaces \n with \0*/

	spaces=count_spaces(str);
	str+=spaces; /*gets rid of unwanted spaces*/
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
	}else {
		result.label=allocate_mem_string(1);
		strcpy(result.label,"\0");
	}


	/*extract instruction*/
	if (strchr(current_pointer,'.')!= NULL){
		/*Instruction exists:
		result.Instruction should be updated
		current pointer should be advanced
		operation should be updated with null
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
		/*Count number of operands*/
		num_commas=0;
		/*i=0;
		while(current_pointer[i]!='\0'){
			if(current_pointer[i]==','){
				data_array_size++;
			}
			i++;
		}


		if (data_array_size>0 || i>0){
			data_array_size++;
		}
*/
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
	else if (strcmp(result.instruction,"mat")==0){

		printf("mat\n");
		extracted_value=parse_mat_size(current_pointer);
		extracted_value_length=strlen(extracted_value)+1;

		printf(BOLDRED"pointer after extracting parse_mat: %s\n",current_pointer);

		/*EXTRACT OPERAND1*/
		result.OPERAND1=allocate_mem_string(extracted_value_length);
		strcpy(result.OPERAND1,extracted_value);
		current_pointer+=extracted_value_length;

		spaces=count_spaces(current_pointer);
		current_pointer+=spaces;
		REALLOCATE_EXTRACTED_VALUE;


		/*EXTRACT OPERAND2*/


		/*Count number of operands*/
		/*i=0;
		while(current_pointer[i]!='\0'){
			if(current_pointer[i]==','){
				data_array_size++;
			}
			i++;
		}

		if (data_array_size>0){
			data_array_size++;
		}*/

		COUNT_DATA_STRINGS_SIZE

		result.data_values_number=data_array_size;
		result.data_string_array=(String*)allocate_mem_general(data_array_size+1,sizeof(String));

		result.data_string_array=extract_data_strings(current_pointer,data_array_size);

		current_pointer+=(data_array_size+i);


		extracted_value_length=strlen(current_pointer);
		result.leftovers=allocate_mem_string(extracted_value_length);
		strcpy(result.leftovers,current_pointer);

		NORMALCOLOR
	}




	else {


		if (strlen(current_pointer)>0){
			/*Extractring OPERAND1*/

			extracted_value=extract_operand(current_pointer);
			extracted_value_length=strlen(extracted_value);


			result.OPERAND1=allocate_mem_string(extracted_value_length+1);
			strcpy(result.OPERAND1,extracted_value);


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
				result.OPERAND2=allocate_mem_string(extracted_value_length+1);
				strcpy(result.OPERAND2,extracted_value);

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
				RETURN_NULL(result.OPERAND2)
				RETURN_NULL(result.leftovers)
			}
		}
		else {
			RETURN_NULL(result.OPERAND1)
			RETURN_NULL(result.OPERAND2)
			RETURN_NULL(result.leftovers)

		}

	}

	free(extracted_value);
	return result;

}


/*
 * Recieves a substrings
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

	printf(KCYN);
	n_spaces=count_spaces(str);
	str+=n_spaces;

	ptr=strchr(str,',');
	i=0;
	if (!ptr){
		/*',' was not found so we are the last operand*/
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

	result=allocate_mem_string(operand_size+ADDEDSIZE);

	strncy_safe(result,str,operand_size);

	return result;

}

/*
 * This function recieves a string, and derives the following: [][]
 * This function counts how many chars are not spaces, then copies them to a new array.
 * Function returns the extracted value [][]
 */
String parse_mat_size (String str){
	String result;
	int op_length;

	op_length=0;
	op_length=count_non_spaces(str);

	result=allocate_mem_string(op_length+1);
	strncy_safe(result,str,op_length);

	printf("parsed size by parse_mat: <%s>\n",result);
	return result;
}



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
	/*size = (found_char-array_start) * sizeof(char);*/
	size = CALCSIZE(array_start,found_char);
/*	fprintf(stderr,"---label length: %d\n",size);*/
	result = allocate_mem_string(size+ADDEDSIZE);

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

	result=allocate_mem_string(strlen(str)+ADDEDSIZE);
	array_start=str;

	found_char = strchr(str,'.');
	if (!found_char){
		RETURN_NULL(result)
		return result;
	}

	/*In which position the dot appears. 1 is added because we care about what's after the dot*/
	size=CALCSIZE(array_start,found_char);
	size++;

	inspection_start=str+size;
	inspection_end = str+(count_non_spaces(str));


/*	if (!inspection_end){
		size=strlen(inspection_start);
		inspection_end=inspection_start+size; point to the last cell of the array
	}*/

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


int reverse_count_spaces (String start, String end){
	int size,i,n;
	i=0;
	size=CALCSIZE(start,end);

	while (i<size && start[i]!=' ' && start[i]!='\t'){
		i++;
	}

/*	printf("number of non spaces: %d\n",i);*/
	n=size-i;

/*	printf(KYELLOW "size:%d, i:%d, calculated n: %d\n",size,i,n);*/
	NORMALCOLOR
	return n;
}

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

	result=allocate_mem_string(size+ADDEDSIZE);

	strncpy(result,str,size);

/*	printf(KMAGENTA "STR: [%s\n",str);*/

	NORMALCOLOR
	return result;
}

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
 * It creates a seperated string for each section devided by ','
 * Input: a pointer to a string, which holds all the parametes as one chunk
 * Output: an array of char*, where each parameter stored in a seperated cell
 */
String* extract_data_strings(char* str, int array_size){
	String* final_array;
	char* pointer;
	int size;
	int i;
	int cell=0;
	int n_spaces;

/*	final_array=allocate_mem_matrix(array_size+1);*/
	final_array=(String*)allocate_mem_general(array_size+1,sizeof(String));
/*

	printf("------------------------------\n");
	printf(" Extracting strings for data\n");
	printf("------------------------------\n");

*/

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
			int non_spaces;

			n_spaces=count_spaces(str);
			str+=n_spaces;
			/*count how many chars until next spaces*/
			non_spaces=count_non_spaces(str)+1;

			final_array[cell]=allocate_mem_string((count_non_spaces(str))+1);
			strncy_safe(final_array[cell],str,(count_non_spaces(str)));
			cell++;

			final_array[cell]=allocate_mem_string(1);
			final_array[cell]='\0';


		}

	}

	return final_array;
}

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


