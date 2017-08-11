/*
 * utils.h
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXMEM 81

#define COMPARE(a,b) strcmp(a,"b")





typedef char* String;

typedef enum {
	FALSE = 0,
	TRUE = 1
} Bool;

typedef enum {
	ACTION =0,
	INSTRUCTION=1,
	UNKNOWN=3
}line_type;



/*
 * Parser  related
 */
typedef struct parsed_line {
	int line_number;
	String label;
	String instruction;
	String operantion;
	String operand1;
	String operand2;
	String operand3; /*This exists to hold additional operands (for validation)*/
	String* data_string_array;
	int * data_int_values;
	Bool valid;
	/*decide on how to deal with .data*/


} body;

typedef  body * bodyArray;





/**********************************/
/***********FUNCTIONS**************/
/**********************************/


bodyArray allocate_mem_struct (int); /*dynamically allocates memory for a struct array*/

/*A function that receives a string length and allocates the required memory */
String* allocate_mem_matrix(int size);
String  allocate_mem_string(int);




/*for testing*/
void print_structs(bodyArray, int);

void add_spaces_print (String array);

void print_line(body);
void print_mat (String*, int);

#endif /* UTILS_H_ */
