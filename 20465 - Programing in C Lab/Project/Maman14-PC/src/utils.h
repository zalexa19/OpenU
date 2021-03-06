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
#include "constants.h"



#define NORMAL  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGREEN  "\x1B[32m"
#define KYELLOW  "\x1B[33m"
#define KBLUE  "\x1B[34m"
#define KMAGENTA  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHITE  "\x1B[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */




#define NORMALCOLOR printf(NORMAL "");
#define MAXERRORSIZE 200
#define INITIAL_ADDRESS 100

#define MAXMEM 81
#define COMPARE(a,b) strcmp(a,"b")

/*
 * This macro helps calculating which parts of the array need to be copied
 */

#define CALCSIZE(array_start, index)\
	(index-array_start)*sizeof(char);




typedef char* String;


typedef enum {
	FALSE = 0,
	TRUE = 1
} Bool;




typedef enum{
	instructional=0,
	operational=1,
	unknown=2
}label_type;

typedef enum{
	internal=0,
	external=1
}declared;


typedef enum{
	instruction=0,
	operation=1,
	unrecognized_command=2
}command_type;




/*
 * Parser  related
 */
typedef struct parsed_line {
	int line_number;
	int data_values_number;
	String label;
	String instruction;
	String operantion;
	String operand1;
	String operand2;
	String leftovers; /*This exists to hold additional operands (for validation)*/
	String* data_string_array;
	int * data_int_values;
	int mat_size;
	Bool valid;
	Operand_type op1_type;
	Operand_type op2_type;
} parsed_item;

typedef  parsed_item * parsed_item_ptr;

typedef struct symbol* symbol_ptr;

/*for symbols list*/
typedef struct symbol{
	String name;
	label_type command_type;
	declared declared_as;
	int address;
	Bool is_entry;
	Bool is_matrix;
	symbol_ptr next;
}symbol;



/*
 * Linked List
 */

typedef struct node* list_item_reference;
typedef struct node {
	String str;
	list_item_reference next;
	list_item_reference prev;
}list_item;



/**********************************/
/***********FUNCTIONS**************/
/**********************************/


parsed_item_ptr allocate_mem_struct (int); /*dynamically allocates memory for a struct array*/

/*A function that receives a string length and allocates the required memory */
/*String* allocate_mem_matrix(int size);*/
String  allocate_mem_string(int);


/**
 * For linked list
 */

/*general function for allocating memory*/
void * allocate_mem_general(int count, int size);

void add_to_list(list_item_reference*,String);

void print_list(list_item_reference);

void free_list(list_item_reference*);

void strncy_safe(String  dest, String  source, int size);

command_type get_command_type(parsed_item);




/*for testing*/
void print_structs(parsed_item_ptr, int size);

void add_spaces_print (String array);

void print_line(parsed_item);
void print_mat (String*, int);

void print_symbol_list(symbol_ptr );

void print_bin(int);
void print_binary_array(int array[], int size);
#endif /* UTILS_H_ */
