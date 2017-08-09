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
	String label;
	String instruction;
	String operantion;
	String operand1;
	String operand2;
	String operand3; /*This exists to hold additional operands (for validation)*/
	/*decide on how to deal with .data*/


} body;

typedef  body * bodyArray;

bodyArray allocate_mem_struct (int); /*dynamically allocates memory for a struct array*/

/*A function that receives a string length and allocates the required memory */
String  allocate_mem_string(int);



/*for testing*/
void print_structs(bodyArray, int);

void add_spaces_print (String array);

#endif /* UTILS_H_ */
