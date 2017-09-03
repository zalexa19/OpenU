#include "utils.h"
#include <ctype.h>
#include "validator.h"
#include "operation_dictionary.h"


#define MAXLABELSIZE 30
#define NOMATCH "none"
#define TERMINATOR "\0"
#define MATRIXCOLANDROW 2
#define NUMOFBRACKETS 2


/*Macro that adds a log*/
#define INVALIDINPUT fprintf(stderr, "Invalid input: ");
/*
 * Macro for printing
 */
#define PRINT_PASSED_OR_FAILED(value) \
{\
			if (value==TRUE){\
			printf(KGREEN "PASSED\n");\
		} else {\
			printf(KRED "FAILED\n");\
		}\
		NORMALCOLOR\
}

#define SET_ERROR_FOUND\
		if (item.valid==FALSE){\
		error_found=TRUE;\
	}


Bool validate_file(bodyArray parsed, int array_size){
	int counter;
	body item;
	list_item_reference error_list_head;
	char error[MAXERRORSIZE];
	label_status_ref validated_label;
	Bool error_found=FALSE;


	NORMALCOLOR

	error_list_head=NULL;


	for (counter=0;counter<array_size;counter++){
		item=parsed[counter];


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




			/*DATA*/
			if (strcmp(item.instruction,"data")==0){
				validate_ins_data(&item, &error_list_head);
				SET_ERROR_FOUND

			}


			if (strcmp(item.instruction,"string")==0){
				validate_ins_string(&item,&error_list_head);
				SET_ERROR_FOUND
			}

			/*MAT*/
			if (strcmp(item.instruction,"mat")==0){
				/*validate the numbers received*/
				validate_ins_data(&item,&error_list_head);
				mat_validation_errors(validate_ins_mat(&item),item);
				SET_ERROR_FOUND
			}


			/*ENTRY*/
			if (strcmp(item.instruction,"entry")==0){
				validate_ins_entry(&item,&error_list_head,error);
				SET_ERROR_FOUND
			}



			/*EXTERN*/
			if (strcmp(item.instruction,"extern")==0){
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


	printf(BOLDGREEN"finished validating file\n");
	NORMALCOLOR

	return TRUE;
}



/*label_val_status validate_label (body* item, list_item_reference*  head){*/
label_status_ref validate_label (String label){
	int length;
	int i;
	char c;
	label_status_ref validation_result;
	Bool valid_letter;

	length=strlen(label);

	validation_result=initialize_label_struct();

	/*validating label length*/

	if (length > MAXLABELSIZE){
		validation_result->TOO_LONG=TRUE;
		validation_result->VALID_LABEL=FALSE;
	}



	/*validate the first char*/
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




void validate_instruction(body* item, list_item_reference*  head){
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







Bool validate_operation(body* item, list_item_reference*  head, String error){
	String value;
	int line;

	line=item->line_number;
	value=item->operantion;

	printf("values to be validated: %s, status: %d\n",value,is_operational_command(value));
	if (is_operational_command(value)==FALSE){
		sprintf(error,"Error in line %d: Operational value <%s> is unrecognized.\n",line,value);
		add_to_list(head,error);
		return FALSE;
	}

	return TRUE;
}

/*This function validates that the operands are valid numbers*/
void validate_ins_data (body* item, list_item_reference*  head){
	int num_of_operands;
	int line,i;
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
	if((item->data_int_values=(int*)malloc(sizeof(int)*item->data_values_number)) == NULL){
		fprintf(stderr,"Unable to allocate memory to data_int_values. Continuing\n");
	}


	for (counter=0;counter<num_of_operands;counter++){
		item->data_int_values[counter]=atoi(item->data_string_array[counter]);
	}
}


void validate_ins_string (body* item, list_item_reference*  head){
	char error[MAXERRORSIZE];
	String temp;
	int length;
	String pointer;

	/*checks that the string was received with ""*/


	/*checks if enough operands were received*/
	if ((strcmp(item->OPERAND2,TERMINATOR))!=0){
		item->valid=FALSE;

		sprintf(error,"10. Error in line %d: Excess operand for .string: <%s>.\n",item->line_number,item->OPERAND2);
		add_to_list(head,error);
	}

	if ((strcmp(item->leftovers,TERMINATOR))!=0){
		item->valid=FALSE;
		sprintf(error,"11. Error in line %d: Excess operand for .string: <%s>.\n",item->line_number,item->leftovers);
		add_to_list(head,error);
	}

	if ((strcmp(item->OPERAND1,TERMINATOR))==0){
		item->valid=FALSE;
		sprintf(error,"9. Error in line %d: Missing operands for .string.\n",item->line_number);
		add_to_list(head,error);
		return;
	}


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
			printf("advanced the pointer\n");
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
 * 1.Removes all spaces. According to the forum, matrix will be recieved without unexpected spaces
 * 2.check that operand1 includes valid numbers
 * 3. Put the valid numbers in a special array
 * 4. check that the other values recieved also includes valid numbers
 */



mat_status_report_ref validate_ins_mat (body* item){
	mat_status_report_ref result;
	int i,size,r,c;
	int brackets_balance=0;
	int op1_length=strlen(item->OPERAND1);
	String oper1=item->OPERAND1;
	String pointer;
	String extracted_n; /*pointer that is used for deriving matrix size*/
	String copy;


	printf(KBLUE "VALIDATE_INS_MAT\n");

	result=(mat_status_report_ref)allocate_mem_general(1,sizeof(mat_status_report));


	result->inv_char_in_brackets=FALSE;
	result->inv_n_brackets=FALSE;
	result->syntax_error=FALSE;
	result->inv_label_found=FALSE;
	result->inv_registry_found=FALSE;
	result->valid_mat=TRUE;


/*	strcpy(op1,item->OPERAND1);*/

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

/*
		item->mat_params=(String*)allocate_mem_general(2,sizeof(String));
		data_pointer=item->mat_params;
		data_pointer[0]=allocate_mem_string(size);
*/

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
			printf("freed copy\n");
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





/*VALIDATE MAT*/

Bool validate_mat_as_operand(String operand){
/*	mat_status_report_ref result;*/
	int i,size;
	int brackets_balance=0;
	int op1_length=strlen(operand);
	String pointer;
	String copy;


	/*check label*/
	pointer=strchr(operand,'[');
	if (!pointer){
		return FALSE;
	}



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

	/*check if all brackers appear correctly, and that the it includes only a number*/
	operand+=1;/*advance once to skip the first [*/


	pointer=strchr(operand,']');
	size=CALCSIZE(operand,pointer);

/*	free(copy);*/

	copy=allocate_mem_string(size+1);
	strncy_safe(copy,operand,size);



	if (is_register(copy)==FALSE){
		return FALSE;

	}


	operand=strchr(operand,'[');
	operand+=1;/*1 is to skip '['*/


	pointer=strchr(operand,']');
	size=CALCSIZE(operand,pointer);

/*	free(copy);*/

	copy=allocate_mem_string(size);
	strncy_safe(copy,operand,size);


	if (is_register(copy)==FALSE){
		return FALSE;
	}

	free(copy);
	printf("Finished validating operand mat\n");
	return TRUE;
}




void mat_validation_errors(mat_status_report_ref errors, body item)
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



void validate_ins_entry(body* item, list_item_reference*  head, char * error){
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

	/*remove the received label*/
	strcpy(item->label,"\0");
}

void validate_ins_extern(body* item, list_item_reference*  head,String error){

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


void validate_oper_operands (body* item, list_item_reference*  head, String error){
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

	/*received a valid number of operands. now check that it's valid*/
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

Operand_type get_operand_type (String operand){
	int i;

	i=0;
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

void print_label_errors(label_status_ref status, body item, list_item_reference * head){
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

