/*
 * second_scan.h
 *
 *  Created on: Aug 27, 2017
 *      Author: alexz
 */

#ifndef SECOND_SCAN_H_
#define SECOND_SCAN_H_

#include "utils.h"
#include "operation_dictionary.h"
#include "first_scan.h"
#include "constants.h"

typedef struct encoded* encoded_ptr;
typedef struct encoded{
	int address;
	int value;
	encoded_ptr next;

}encoded;



Bool second_scan (bodyArray,int,symbol_ptr*,int, encoded_ptr *, int *,external_labels_ptr*);

int get_opcode(String);

int code_command_line(int opcode,Operand_type op1, Operand_type op2, int rea);

int encode_register(String,String);

int encode_operand(Operand_type,String, symbol_ptr, Bool);
#endif /* SECOND_SCAN_H_ */

void print_encoded_struct(encoded_ptr s);
void add_encoded_struct_to_list(encoded_ptr * list, encoded_ptr item);
encoded_ptr create_encoded_struct(int,int);
