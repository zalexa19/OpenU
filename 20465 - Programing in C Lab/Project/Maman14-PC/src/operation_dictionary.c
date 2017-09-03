/*
 * operation_dictionary.c
 *
 *  Created on: Aug 23, 2017
 *      Author: alexz
 */
#include "operation_dictionary.h"

/*
 * POinter to the list of all avaitype_label operations in our assembler
 */
static operation_info * global_operation_dictionary;



#define INITIALIZE_OPERATION(name_value,number_of_operands,op1_type_intermid,op1_label,op1_mat,op1_type_register,op2_type_intermid,op2_label,op2_mat,op2_type_register)\
	operational_dictionary[i].name=name_value;\
	operational_dictionary[i].num_of_operands=number_of_operands;\
	operational_dictionary[i].op1_intermid_allowed=op1_type_intermid;\
	operational_dictionary[i].op1_label_allowed=op1_label;\
	operational_dictionary[i].op1_matrix_allowed=op1_mat;\
	operational_dictionary[i].op1_register_allowed=op1_type_register;\
	operational_dictionary[i].op2_intermid_allowed=op2_type_intermid;\
	operational_dictionary[i].op2_label_allowed=op2_label;\
	operational_dictionary[i].op2_matrix_allowed=op2_mat;\
	operational_dictionary[i].op2_register_allowed=op2_type_register;\
	i++;





void create_operation_info_array(){
	int i;
	operation_info * operational_dictionary;

	if (!(operational_dictionary= malloc(sizeof(operation_info)*OPERANDS_NUMBER))){
		fprintf(stderr,"Unable to allocate memory to operation_info \n." );
		exit(1);
	}

	i=0;
/*	operational_dictionary[i].name="mov";
	operational_dictionary[i].num_of_operands=2;
	operational_dictionary[i].op1_intermid_allowed=TRUE;
	operational_dictionary[i].op1_label_allowed=TRUE;
	operational_dictionary[i].op1_type_register_allowed=TRUE;
	operational_dictionary[i].op1_matrix_allowed=TRUE;
	operational_dictionary[i].op2_intermid_allowed=FALSE;
	operational_dictionary[i].op2_label_allowed=TRUE;
	operational_dictionary[i].op2_register_allowed=TRUE;
	operational_dictionary[i].op2_matrix_allowed=TRUE;*/

	INITIALIZE_OPERATION("mov",2,TRUE,TRUE,TRUE,TRUE,FALSE,TRUE,TRUE,TRUE)
	INITIALIZE_OPERATION("cmp",2,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE)
	INITIALIZE_OPERATION("add",2,TRUE,TRUE,TRUE,TRUE,FALSE,TRUE,TRUE,TRUE)
	INITIALIZE_OPERATION("sub",2,TRUE,TRUE,TRUE,TRUE,FALSE,TRUE,TRUE,TRUE)
	INITIALIZE_OPERATION("not",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("clr",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("lea",2,FALSE,TRUE,TRUE,FALSE,FALSE,TRUE,TRUE,TRUE)
	INITIALIZE_OPERATION("inc",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("dec",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("jmp",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("bne",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("red",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("prn",1,TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("jsr",1,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("rts",0,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE)
	INITIALIZE_OPERATION("stop",0,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE)

	global_operation_dictionary = operational_dictionary;

}


operation_info get_operation_info(String str){

	int i;
	operation_info result;

	i=0;
	while (i<OPERANDS_NUMBER){
		if (strcmp(global_operation_dictionary[i].name,str)==0){
			result=global_operation_dictionary[i];
		}

		i++;
	}

	return result;
}

/*This function compares the operand type extracted by the validator to the allowed one according to the command*/
Bool is_operand1_allowed(operation_info info,String command,Operand_type type){

	if ((type==type_intermid) && (info.op1_intermid_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_label) && (info.op1_label_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_matrix) && (info.op1_matrix_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_register) && (info.op1_register_allowed==TRUE)){
		return TRUE;
	}

	return FALSE;
}


Bool is_operand2_allowed(operation_info info,String command,Operand_type type){

	if ((type==type_intermid) && (info.op2_intermid_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_label) && (info.op2_label_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_matrix) && (info.op2_matrix_allowed==TRUE)){
		return TRUE;
	}

	if ((type==type_register) && (info.op2_register_allowed==TRUE)){
		return TRUE;
	}

	return FALSE;
}



