/*
 * in this file, each struct (that represents a line" is validated.
 * if validation failes, the main function valudate_file return false back to main, and we skip to the next file
 */


#include "utils.h"
#include <ctype.h>
#include "validator.h"
#include "operation_dictionary.h"


#define MAX_LABEL_SIZE 30
#define NOMATCH "none"
#define TERMINATOR "\0"


/*This macro simply sets a flag*/
#define SET_ERROR_FOUND\
		if (item.valid==FALSE){\
		error_found=TRUE;\
	}

/*
 * input: array of structs to validate, number of structs in the array
 * output: true if validation passed, false if not (error_found=TRUE)
 *
 * each field of the command is validated by a specific function
 * if a struct is invalid, it's marked as invalid and sets error_found=TRUE;
 * this way we can check all of the structs, and find all the errors.
 *
 */
Bool validate_file(parsed_item_ptr parsed, int array_size){
	int counter;
	parsed_item item; /*current item we're validating*/
	list_item_reference error_list_head;
	char error[MAXERRORSIZE]; /*temp array to write an error into. used only for printing errors*/
	label_status_ref validated_label;
	Bool error_found=FALSE;



	error_list_head=NULL;

	for (counter=0;counter<array_size;counter++){
		item=parsed[counter];

		/*label exists*/
		if(strcmp(item.label,TERMINATOR) != 0){
			validated_label=validate_label(item.label);

			item.valid=validated_label->VALID_LABEL;
			print_label_errors(validated_label,item,&error_list_head);
			SET_ERROR_FOUND

		}


		if(strcmp(item.instruction,"\0") != 0){
			/***********************
			 * VALIDATE INSTRUCTION*
			 ***********************/

			validate_instruction(&item,&error_list_head);
			SET_ERROR_FOUND


			if (strcmp(item.instruction,DATA)==0){
				validate_ins_data(&item, &error_list_head);
				SET_ERROR_FOUND

			}


			if (strcmp(item.instruction,STR)==0){
				validate_ins_string(&item,&error_list_head);
				SET_ERROR_FOUND
			}

			/*MAT*/
			if (strcmp(item.instruction,MAT)==0){
				/*validate the numbers received*/
				validate_ins_data(&item,&error_list_head);
				mat_validation_errors(validate_ins_mat(&item),item);
				SET_ERROR_FOUND
			}


			/*ENTRY*/
			if (strcmp(item.instruction,ENTRY)==0){
				validate_ins_entry(&item,&error_list_head,error);
				SET_ERROR_FOUND
			}



			/*EXTERN*/
			if (strcmp(item.instruction,EXTERN)==0){
				validate_ins_extern(&item,&error_list_head,error);
				SET_ERROR_FOUND
			}
		}
		else {
			/*
			 * Validate the operation
			 */

			if (strcmp(item.operantion,"\0")==0){
				item.valid=FALSE;
				sprintf(error,"Error in line: %d: Operation/Instruction were not received.\n",item.line_number);
				add_to_list(&error_list_head,error);
				SET_ERROR_FOUND
			} else {

				if (validate_operation(&item,&error_list_head,error)==FALSE){
					SET_ERROR_FOUND
				}
				/*validating the operands received for the operational command*/
				validate_oper_operands(&item,&error_list_head,error);
				SET_ERROR_FOUND
			}


			/*end of operation validation*/
			}

		parsed[counter] = item;

	}

	if (error_found==TRUE){
		print_list(error_list_head);

		return FALSE;
	}


	return TRUE;
}

/*
 * label_status_ref is a struct of flags.
 * each flag represents a different validation done to the label.
 * This is used later on for printing, by a different function
 *
 *
 */

label_status_ref validate_label (String label){
	int length;
	int i;
	char c;
	label_status_ref validation_result;
	Bool valid_letter;

	length=strlen(label);

	validation_result=initialize_label_struct();

	/*validating label length*/
	if (length > MAX_LABEL_SIZE){
		validation_result->TOO_LONG=TRUE;
		validation_result->VALID_LABEL=FALSE;
	}



	/*validate the first char - should start with a letter*/
	i=0;
	c=label[i];
	valid_letter=is_valid_letter(c);

	if (valid_letter==FALSE){
		validation_result->INV_FIRST_CHAR=TRUE;
		validation_result->VALID_LABEL=FALSE;
	}
	i++;


	/*validating each char in the string, starting from cell #1:*/
	while (i<length){
		c=label[i];
		valid_letter=is_valid_letter(c);
		if (valid_letter==FALSE){
			/*not a letter*/

			if (isdigit(c)==FALSE){
				validation_result->INV_CHAR_FOUND=TRUE;
				validation_result->VALID_LABEL=FALSE;
			}

		}

		i++;
	}

	/*validating that the label is not a saved word*/
	if (is_operational_command(label)==TRUE || is_instructional_command(label)==TRUE){
		validation_result->RESERVED=TRUE;
		validation_result->VALID_LABEL=FALSE;
	}

	return validation_result;
}


/*
 * This function validates the instruction operand
 * head - list of errors to add a new error to
 * it doesn't return any value - it marks the struct as invalid and adds the relevant error to the error list
 */

void validate_instruction(parsed_item* item, list_item_reference*  head){
	int line=item->line_number;
	String inst_value= item->instruction;
	char error[MAXERRORSIZE];

	/*Check if instruction is all lower case*/
	if (is_string_lowercase(inst_value)==FALSE){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Instruction value <%s> has non-lowecase chars.\n",line,inst_value);
		add_to_list(head,error);
	}

	/*check if instruction is a valid command*/
	if (is_instructional_command(inst_value)==FALSE){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Instruction value <%s> is unrecognized.\n",line,inst_value);
		add_to_list(head,error);
	}

}



/*
 * This function validates the operation
 * it returns true if operation is valid
 * checks if the value received matches one of the operation commands
 */



Bool validate_operation(parsed_item* item, list_item_reference*  head, String error){
	String value;
	int line;

	line=item->line_number;
	value=item->operantion;

	if (is_operational_command(value)==FALSE){
		sprintf(error,"Error in line %d: Operational value <%s> is unrecognized.\n",line,value);
		add_to_list(head,error);
		return FALSE;
	}

	return TRUE;
}

/*This function validates that the operands are valid numbers
 * at this point, the struct has an array of string where each string has a value that might be a number
 * so for each cell, i check that the string is indeed a number. if so, each such string converted to a number
 * and stored in a numbers array in the struct
 * function doesn't return a value, but updates the struck if an error was found.
 * errors are sent to the errors list
 */
void validate_ins_data (parsed_item* item, list_item_reference*  head){
	int num_of_operands;
	int line;
	int counter;
	String current;
	char error[MAXERRORSIZE];

	num_of_operands=item->data_values_number;
	line=item->line_number;


	if (item->data_values_number==0){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: No operands received for .data.\n",line);
		add_to_list(head,error);
	}


	/*check if each string has valid numbers*/
	for(counter=0;counter<num_of_operands;counter++){
		current=item->data_string_array[counter];

		if (is_valid_number(current)==FALSE){

			item->valid=FALSE;
			sprintf(error,"Error in line %d: non-numbers received in %s, for command %s.\n",line,current,item->instruction);
			add_to_list(head,error);
			return;
		}

	}


	/*If we reached here, it means that we have valid numbers*/
	item->data_int_values=(int*)allocate_mem_general(item->data_values_number,sizeof(int));


	for (counter=0;counter<num_of_operands;counter++){
		item->data_int_values[counter]=atoi(item->data_string_array[counter]);
	}

}

/*
 * validate if the string stored in the struct
 * function doesn't return a value, but updates the struck if an error was found.
 * errors are sent to the errors list
 */

void validate_ins_string (parsed_item* item, list_item_reference*  head){
	char error[MAXERRORSIZE];
	String temp;
	int length;
	String pointer;

	/*checks that the string was received with ""*/

	/*checks if enough operands were received*/
	if ((strcmp(item->OPERAND2,TERMINATOR))!=0 ||(strcmp(item->leftovers,TERMINATOR))!=0 ){
		item->valid=FALSE;

		sprintf(error,"Error in line %d: Excess operand for .string: <%s>.\n",item->line_number,item->OPERAND2);
		add_to_list(head,error);
	}


	if ((strcmp(item->OPERAND1,TERMINATOR))==0){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Missing operands for .string.\n",item->line_number);
		add_to_list(head,error);
		return;
	}

	length=strlen(item->OPERAND1);

	if (item->OPERAND1[strlen(item->OPERAND1)]!='\0'){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: .string <%s> is not closed with a turminating char.\n",item->line_number,item->OPERAND1);
		add_to_list(head,error);
	}

	if(item->valid==TRUE){
		pointer=item->OPERAND1;
		length=strlen(pointer);

		if (pointer[length-length]!= '"'){
			item->valid=FALSE;
			sprintf(error,"Error in line %d: .string <%s> is missing opening <\">.\n",item->line_number,item->OPERAND1);
			add_to_list(head,error);
		}else{
			pointer++;
			length--;
		}
		if (pointer[length-1] != '"'){
			item->valid=FALSE;
			sprintf(error,"Error in line %d: .string <%s> is missing closing <\">.\n",item->line_number,item->OPERAND1);
			add_to_list(head,error);
		}else{

			length--;

		}

		temp=allocate_mem_string(length+1);

		strncy_safe(temp,pointer,length);

		free(item->OPERAND1);
		item->OPERAND1=allocate_mem_string(length+1);

		strcpy(item->OPERAND1,temp);


	}

	free(temp);
}


/*
 *
 * function recieves the parsed struct, returns a struct with flags regarding the validation status.
 * These are used by a function that prints the relevant errors
 */

mat_status_report_ref validate_ins_mat (parsed_item* item){
	mat_status_report_ref result;
	int i,size,r,c;
	int brackets_balance=0;
	int op1_length=strlen(item->OPERAND1);
	String oper1=item->OPERAND1;
	String pointer;
	String extracted_n; /*pointer that is used for deriving matrix size*/
	String copy;


	result=(mat_status_report_ref)allocate_mem_general(1,sizeof(mat_status_report));

	result->inv_char_in_brackets=FALSE;
	result->inv_n_brackets=FALSE;
	result->syntax_error=FALSE;
	result->inv_label_found=FALSE;
	result->inv_registry_found=FALSE;
	result->valid_mat=TRUE;



/*	starting to check op1*/
/*	check number of brackets*/

	for (i=0;i<op1_length;i++){
		if (item->OPERAND1[i]=='['){
			brackets_balance++;
		}
		if(item->OPERAND1[i]==']'){
			brackets_balance--;
		}
	}

	if (brackets_balance!=0){
		result->inv_n_brackets=TRUE;
		result->valid_mat=FALSE;
		item->valid=FALSE;
	}


/*	check brackets structure is correct*/
	if( oper1[0]!='['|| oper1[op1_length-1]!=']' || strstr(item->OPERAND1,"][")==NULL  ){
		result->syntax_error=TRUE;
		result->valid_mat=FALSE;
		item->valid=FALSE;
	}
	else {
/*		check if all brackets appear correctly, and that the it includes only a number*/
		oper1+=1;	/*advance once to skip the first [*/

		pointer=strchr(oper1,']');

		size=CALCSIZE(oper1,pointer);

		copy=allocate_mem_string(size+1);
		strncy_safe(copy,oper1,size);

		/*checking if the first [] is valid*/
		if (is_valid_number(copy)==FALSE){
			result->inv_char_in_brackets=TRUE;
			result->valid_mat=FALSE;
			item->valid=FALSE;
		}

		extracted_n=allocate_mem_string(size+1);
		strncy_safe(extracted_n,copy,size);
		r=atoi(copy);

		/*checking the second []*/
		oper1=strchr(oper1,'[');
		oper1+=1;

		pointer=strchr(oper1,']');
		size=CALCSIZE(oper1,pointer);

		if (size >strlen(copy)){
			free(copy);
			copy=allocate_mem_string(size+1);
		}

		strncy_safe(copy,oper1,size);

		if (is_valid_number(copy)==FALSE){
			result->inv_char_in_brackets=TRUE;
			result->valid_mat=FALSE;
			item->valid=FALSE;
		}

		extracted_n=allocate_mem_string(size+1);

		strncy_safe((extracted_n),copy,size);
		c=atoi(copy);

		item->mat_size=r*c;
		free(extracted_n);
	}

	free(copy);
	return result;
}



/*
 * This function is used when a matrix is received as an operand.
 * It check that the label is valid, and that registers are received in [][]
 * if any validation fails, function returns FALSE, else, TRUE
 */


Bool validate_mat_as_operand(String operand){
	int i,size;
	int brackets_balance=0;
	int op1_length=strlen(operand);
	String pointer;
	String copy;



	pointer=strchr(operand,'[');
	if (!pointer){
		return FALSE;
	}


	/*check label*/
	size=CALCSIZE(operand,pointer);
	copy=allocate_mem_string(size+1);
	strncy_safe(copy,operand,size);


	if (validate_label(copy)==FALSE){
		return FALSE;
	}

	operand+=size;
	op1_length=strlen(operand);


	/*starting to check op1*/
	/*check number of brackets*/
	for (i=0;i<strlen(operand);i++){
		if (operand[i]=='['){
			brackets_balance++;
		}
		if(operand[i]==']'){
			brackets_balance--;
		}
	}

	if (brackets_balance!=0){
		return FALSE;
	}




	/*check brackets structure is correct*/
	if( operand[0]!='['|| operand[op1_length-1]!=']' || strstr(operand,"][")==NULL  ){
		return FALSE;
	}

	/*check if all brackets appear correctly, and that the it includes only a number*/
	operand+=1;/*advance once to skip the first [*/

	pointer=strchr(operand,']');
	size=CALCSIZE(operand,pointer);

	copy=allocate_mem_string(size+1);
	strncy_safe(copy,operand,size);


	if (is_register(copy)==FALSE){
		return FALSE;
	}


	operand=strchr(operand,'[');
	operand+=1;/*1 is to skip '['*/


	pointer=strchr(operand,']');
	size=CALCSIZE(operand,pointer);

	copy=allocate_mem_string(size);
	strncy_safe(copy,operand,size);


	if (is_register(copy)==FALSE){
		return FALSE;
	}

	free(copy);
	return TRUE;
}


/*
 * Function recieves a truct with flags regarding a matrix validation.
 * Prints errors accordingly
 */

void mat_validation_errors(mat_status_report_ref errors, parsed_item item)
{
	int line=item.line_number;

	if (errors->inv_char_in_brackets){
		fprintf(stderr,"Error in line %d: inv char found inside mat brackets: %s\n",line,item.OPERAND1);
	}

	if (errors->inv_label_found){
		fprintf(stderr,"Error in line %d: inv label found inside mat brackets: %s\n",line,item.OPERAND1);

	}


	if (errors->inv_n_brackets){
		fprintf(stderr,"Error in line %d: missing brackets - %s\n",line,item.OPERAND1);

	}

	if (errors->inv_registry_found){
		fprintf(stderr,"Error in line %d:in registry provided %s.\n",line,item.OPERAND1);

	}

	if (errors->syntax_error){
		fprintf(stderr,"Error in line %d: invalid brackets %s.\n",line,item.OPERAND1);

	}


}

/*
 * function validays .entry command.
 * recieves a parsed struct, the errors list and a string of error to write in an error
 * if label is received, i write a warning
 */

void validate_ins_entry(parsed_item* item, list_item_reference*  head, char * error){
	int line;

	line=item->line_number;

	if (strcmp(item->label,TERMINATOR)!=0){
		sprintf(error,"Attention to line %d: label '%s' received for .entry command will be ignored.\n",line,item->label);
		add_to_list(head,error);
	}

	if (strcmp(item->OPERAND1,TERMINATOR)==0){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Missing statement for .entry command .\n",line);
		add_to_list(head,error);

	}

	if (strcmp(item->OPERAND2,TERMINATOR)!=0 ||strcmp(item->leftovers,TERMINATOR)!=0 ){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Too much data received for .entry command: %s %s .\n",line,item->OPERAND2,item->leftovers);
		add_to_list(head,error);
	}

	if ((validate_label(item->OPERAND1)->VALID_LABEL)==FALSE){
		item->valid=FALSE;
		sprintf(error,"Error in line %d: Invalid label received in operand1: %s .\n",line,item->OPERAND1);
		add_to_list(head,error);
	}

	/*remove the received label because it's not necessary*/
	strcpy(item->label,"\0");
}

/*
 * function validays .extern command.
 * recieves a parsed struct, the errors list and a string of error to write in an error
 * if label is received, i write a warning
 */

void validate_ins_extern(parsed_item* item, list_item_reference*  head,String error){
	int line;
	line=item->line_number;

	if (strcmp(item->label,TERMINATOR)!=0){
		sprintf(error,"Attention to line %d: label '%s' received for .extern command will be ignored.\n",line,item->label);
		add_to_list(head,error);
	}

	if (strcmp(item->OPERAND1,TERMINATOR)==0){
		item->valid=FALSE;
		sprintf(error,"24. Error in line %d: Missing statement for .extern command .\n",line);
		add_to_list(head,error);

	}

	if (strcmp(item->OPERAND2,TERMINATOR)!=0 ||strcmp(item->leftovers,TERMINATOR)!=0 ){
		item->valid=FALSE;
		sprintf(error,"25. Error in line %d: Too much data received for .extern command: %s %s .\n",line,item->OPERAND2,item->leftovers);
		add_to_list(head,error);
	}


	if ((validate_label(item->OPERAND1)->VALID_LABEL)==FALSE){
		item->valid=FALSE;
		sprintf(error,"26. Error in line %d: Invalid label received in operand1: %s .\n",line,item->OPERAND1);
		add_to_list(head,error);
	}

	/*remove the received label*/
	strcpy(item->label,"\0");

}





/*
 * This function validates the operands received for an operational command.
 * At first we check the number of operands received.
 * Then, we retrieve the struct that holds info about what is allowed for each command.
 * Validation is done by comparing what is stored in the parsed line, and the info for the command
 */

void validate_oper_operands (parsed_item* item, list_item_reference*  head, String error){
	String command;
	int operand_type;
	int line;
	int operand_count;
	operation_info command_info;

	line=item->line_number;
	command=item->operantion;

	if (is_operational_command(item->operantion)==FALSE){
		sprintf(error,"Error in line %d: Unrecognized command <%s>.\n",line,command);
		add_to_list(head,error);
		item->valid=FALSE;
		return;
	}

	/*count number of operands*/
	operand_count=0;
	if (strlen(item->OPERAND1)>0){
		operand_count++;
	}

	if (strlen(item->OPERAND2)>0){
		operand_count++;
	}

	if (strlen(item->leftovers)>0){
		operand_count++;
	}

	if (operand_count>2){
		sprintf(error,"Error in line %d: Too many operands <%s>.\n",line,item->leftovers);
		add_to_list(head,error);
		item->valid=FALSE;
		return;
	}


	/*Check that the number of operands received is correct*/
	/* Search the struct and compare its info  */
	command_info=get_operation_info(command); /*return the relevant command info*/

	if (command_info.num_of_operands!=operand_count){
		sprintf(error,"Error in line %d: Invalid number of operands %d, expected: %d.\n",line,operand_count,command_info.num_of_operands);
		add_to_list(head,error);
		item->valid=FALSE;
		return;
	}

	/*received a valid number of operands. now check that it's valid, depending on the command*/
	if (command_info.num_of_operands>0){
		operand_type=get_operand_type(item->OPERAND1);
		item->op1_type=operand_type;

		if (operand_type==type_unrecognized){
			/*ERROR*/
			sprintf(error,"Error in line %d: received operand <%s> in unrecognized.\n",line,item->OPERAND1);
			add_to_list(head,error);
			item->valid=FALSE;
		}

		/*check that operand type is allowed*/
		if (is_operand1_allowed(command_info,command,operand_type)==FALSE){
			/*ERROR*/
			sprintf(error,"Error in line %d: received operand <%s> in not allowed for command <%s>.\n",line,item->OPERAND1,command);
			add_to_list(head,error);
			item->valid=FALSE;
		}

		/*checking the second operand*/
		if (command_info.num_of_operands>1){
			operand_type=get_operand_type(item->OPERAND2);
			item->op2_type=operand_type;

			if (operand_type==type_unrecognized){
				/*ERROR*/
				sprintf(error,"Error in line %d: received operand2 <%s> in unrecognized.\n",line,item->OPERAND2);
				add_to_list(head,error);
				item->valid=FALSE;
			}


			if (is_operand2_allowed(command_info,command,operand_type)==FALSE){
				/*ERROR*/
				sprintf(error,"Error in line %d: received operand2 <%s> in not allowed for command <%s>.\n",line,item->OPERAND2,command);
				add_to_list(head,error);
				item->valid=FALSE;
			}

		}



	}


/*DONE VALIDATING THE OPERATION*/
}



/*
 * Checks if a character is valid letter by comparing the asci value
 */
Bool is_valid_letter(char c){

	if ( ('a'<=c && c<= 'z') || ('A'<=c && c<= 'Z')){
		return TRUE;
	}

	return FALSE;


}

Bool is_white_char (char c){
	if (c==' ' || c=='\t' || c=='\n' || c=='\0'){
		return TRUE;
	}
	return FALSE;
}




Bool is_lowcase(char c){
	if ('a'<=c && c<='z'){
			return TRUE;
	}

	return FALSE;
}

/*
 * returns true when the string is all in lowercase
 */
Bool is_string_lowercase(String str){
	int length = strlen(str);
	Bool lowercase=TRUE;
	int i;
	char c;
	i=0;

	c=str[i];
	while(i<length && lowercase==TRUE){
		if(is_lowcase(c)==FALSE){
			lowercase=FALSE;

		}

		i++;
		c=str[i];
	}

	return lowercase;
}


/*
 * return true when each char in the str is a digit, so that the str can be converted to a number
 */
Bool is_valid_number (String str){
	int str_length,i;
	char c;


	i=0;
	str_length=strlen(str);

	if (str_length==0){
		return FALSE;
	}



	if (str[i]=='-' || str[i]=='+'){
		if (str_length==1){
			return FALSE;
		}

		i++;
	}



	while (i<str_length){
		c=str[i];
		if (isdigit(c)==FALSE){
			return FALSE;
		}
		i++;
	}

	return TRUE;
}


int extract_number (String str){
	int result;

	result=atoi(str);

	if (!result){
		fprintf(stderr,"unable to parse into from string %s\n.",str);
	}
	return result;
}







Bool is_instructional_command(String str){

	if (strcmp(str,DATA)==0){
		return TRUE;
	}

	if (strcmp(str,STR)==0){
		return TRUE;
	}
	if (strcmp(str,MAT)==0){
		return TRUE;
	}
	if (strcmp(str,ENTRY)==0){
		return TRUE;
	}
	if (strcmp(str,EXTERN)==0){
		return TRUE;
	}

	return FALSE;

}

Bool is_operational_command(String str){

	if (strcmp(str,MOV)==0){
		return TRUE;
	}

	if (strcmp(str,CMP)==0){
		return TRUE;
	}

	if (strcmp(str,ADD)==0){
		return TRUE;
	}

	if (strcmp(str,SUB)==0){
		return TRUE;
	}

	if (strcmp(str,NOT)==0){
		return TRUE;
	}

	if (strcmp(str,CLR)==0){
		return TRUE;
	}

	if (strcmp(str,LEA)==0){
		return TRUE;
	}

	if (strcmp(str,INC)==0){
		return TRUE;
	}

	if (strcmp(str,DEC)==0){
		return TRUE;
	}

	if (strcmp(str,JMP)==0){
		return TRUE;
	}

	if (strcmp(str,BNE)==0){
		return TRUE;
	}

	if (strcmp(str,RED)==0){
		return TRUE;
	}
	if (strcmp(str,PRN)==0){
			return TRUE;
	}

	if (strcmp(str,JSR)==0){
			return TRUE;
	}

	if (strcmp(str,RTS)==0){
			return TRUE;
	}

	if (strcmp(str,STOP)==0){
			return TRUE;
	}

	return FALSE;

}


Bool is_register(String str){

	if (strcmp(str,R0)==0){
		return TRUE;
	}

	if (strcmp(str,R1)==0){
		return TRUE;
	}

	if (strcmp(str,R2)==0){
		return TRUE;
	}

	if (strcmp(str,R3)==0){
		return TRUE;
	}

	if (strcmp(str,R4)==0){
		return TRUE;
	}

	if (strcmp(str,R5)==0){
		return TRUE;
	}

	if (strcmp(str,R6)==0){
		return TRUE;
	}

	if (strcmp(str,R7)==0){
		return TRUE;
	}

	return FALSE;
}


/*
 * receives a string, and returns it's operand type
 *
 */
Operand_type get_operand_type (String operand){
	int i;

	i=0;
	/*empty string*/
	if (strlen(operand)==0 || operand==NULL){
		return type_unrecognized;
	}

	if (operand[i]=='#'){
		if (is_valid_number(operand+1)==TRUE){
			return type_intermid;
		}

	}


	if ( validate_mat_as_operand(operand)==TRUE ){
		return type_matrix;
	}

	if (is_register(operand)==TRUE){
		return type_register;
	}


	if ((validate_label(operand)->VALID_LABEL)==TRUE){
		return type_label;
	}

	return type_unrecognized;

}


/*
 * Function creates a new struct to store info about label's validation.
 * return a pointer to this struct (used in validate_label)
 */



label_status_ref initialize_label_struct(){

	label_status_ref new;

	new =(label_status_ref)allocate_mem_general(1,sizeof(label_status));


	new->VALID_LABEL=TRUE;
	new->INV_FIRST_CHAR=FALSE;
	new->INV_CHAR_FOUND=FALSE;
	new->RESERVED=FALSE;
	new->TOO_LONG=FALSE;

	return new;
}


/*
 * receives a struct with info about label, and prints errors according to the flags
 */

void print_label_errors(label_status_ref status, parsed_item item, list_item_reference * head){
	String error =allocate_mem_string(MAXERRORSIZE);

	if (status->TOO_LONG==TRUE){
		sprintf(error,"1. Error in line %d: Label <%s> is too long.\n",item.line_number,item.label);
		add_to_list(head,error);

	}

	if (status->INV_FIRST_CHAR==TRUE){
		sprintf(error,"2. Error in line %d: Label <%s> doesn't start with a letter.\n",item.line_number,item.label);
		add_to_list(head,error);


	}

	if (status->INV_CHAR_FOUND==TRUE){
		sprintf(error,"3. Error found in line %d: invalid char was found in label <%s>.\n",item.line_number,item.label);
		add_to_list(head,error);


	}

	if (status->RESERVED==TRUE){
		sprintf(error,"4. Error found in line %d: label <%s> is a preserved word.\n",item.line_number,item.label);
		add_to_list(head,error);


	}
	free(error);
}

