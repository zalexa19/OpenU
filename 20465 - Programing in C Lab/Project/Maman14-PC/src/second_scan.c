/*
 * second_scan.c
 *
 *  Created on: Aug 27, 2017
 *      Author: alexz
 */

#include "second_scan.h"
#define WORD_SIZE 10
#define OPCODE_SIZE 4
#define OPER_SIZE 2
#define ABSOLUTE_VALUE 0
#define EXTERNAL_VALUE 1
#define RELLOCATABLE_VALUE 2
#define ARRAYSIZE 200
#define MAX_DATA_ARR_SIZE 10000
#define REG_NAME_LENGTH 2





#define ADD_CALCULATED_VALUE_TO_LIST\
		encoded_item=create_encoded_struct(ic_address,calculated_memory_line);\
		add_encoded_struct_to_list(encoded_list,encoded_item);\
		ic_address++;


Bool second_scan (bodyArray parsed, int parsed_size, symbol_ptr*symbols, int ic,encoded_ptr* encoded_list,int DC,external_labels_ptr* external_labels_list){
	int i,j, length;
	int ic_address; /*tracks addresses when encoding and adding additional word memories*/
	int combined_data_list_counter; /*counter for the combined lise*/
	int parse_scanner;
	int calculated_memory_line; /*stores the encoded word memory*/
/*	int data_counter;*/
	body current;
	int opcode; /*stores the opcode received*/
	Operand_type op1_type,op2_type;
/*	int data_array[DC]; *//*remove this later keeping it for the orig function*/
/*	encoded_ptr encoded_node;*/
	encoded_ptr encoded_item; /*item that holds info about the encoded value and it's address, to be printed by output.c*/
	command_type command_type;
	symbol_ptr relevant_symbol; /*stores the symbol found when using the search_symbol function*/
	int* combined_data_list; /*array with all data received as instruction, to be added to the end of obj file*/
	Bool valid_file=TRUE;
	encoded_ptr temp;


	printf(KMAGENTA"SECOND SCAN STARTED\n\n");

	/*preparations*/
	combined_data_list=(int*)allocate_mem_general(DC,sizeof(int));
	combined_data_list_counter=0;
	calculated_memory_line=0;
	ic_address=INITIAL_ADDRESS; /*starts with 100*/
	encoded_item=(encoded_ptr)allocate_mem_general(1,sizeof(encoded));


	/*This loop makes sure that each label is difined*/
	for (i=0;i<parsed_size;i++){
		current=parsed[i];

/*		printf("checking label: %s\n",current.label);*/
		if (strlen(current.label)>0){
			if (! search_symbol(current.label,*symbols)){ /*label is not found*/
				fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.label);
				valid_file=FALSE;
			}
		}

		if (strcmp(current.instruction,EXTERN)!=0 &&
			strcmp(current.instruction,STR) !=0 &&
			strcmp(current.instruction,DATA) !=0 &&
			strcmp(current.instruction,MAT) !=0){

			/*for everything that is not .extern*/
			if (get_operand_type(current.OPERAND1)==type_label){
				if (!search_symbol(current.OPERAND1,*symbols)){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND1);
					valid_file=FALSE;
				}

			}

/*			printf("checking if op2 is a label\n");*/

			if (get_operand_type(current.OPERAND2)==type_label){

				if (!(search_symbol(current.OPERAND2,*symbols))){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND2);
					valid_file=FALSE;
				}

			}

			if (get_operand_type(current.OPERAND1)==type_matrix){
				relevant_symbol=search_symbol(extract_mat_label(current.OPERAND1),*symbols);

				if (!relevant_symbol){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND1);
					valid_file=FALSE;
				}

				else if(relevant_symbol->is_matrix==FALSE){
					fprintf(stderr, "Error in line %d: Label %s is not defined as a matrix\n",current.line_number,current.OPERAND1);
					valid_file=FALSE;
				}
			}
			if (get_operand_type(current.OPERAND2)==type_matrix){
				relevant_symbol=search_symbol(extract_mat_label(current.OPERAND2),*symbols);
				if (!relevant_symbol){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND2);
					valid_file=FALSE;
				}
				if(relevant_symbol->is_matrix==FALSE){
					fprintf(stderr, "Error in line %d: Label %s is not defined as a matrix\n",current.line_number,current.OPERAND2);
					valid_file=FALSE;
				}
			}

		}
	}

	if (valid_file==FALSE){
		return FALSE;
	}

	/*end of labels validation*/



	/*this loop goes over each parsed line*/
	for (parse_scanner=0;parse_scanner<parsed_size;parse_scanner++){
		current=parsed[parse_scanner];

		print_line(current);

		/*extract info about the line*/
		command_type=get_command_type(current);
		if (command_type==operation){

			opcode=get_opcode(current.operantion);
			op1_type=current.op1_type;
			op2_type=current.op2_type;

			/*code the command and add it to the final list*/
			if (opcode==15 || opcode==14){
				calculated_memory_line=opcode;
				calculated_memory_line<<=(WORD_SIZE-OPCODE_SIZE);
				print_bin(calculated_memory_line);
			}
			else {
				calculated_memory_line=code_command_line(opcode,op1_type,op2_type,ABSOLUTE_VALUE);

			}

			ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/


			/*
			 * label:
			 * if external, we encode address zero with last two digits to show that it's external
			 * if internal, we encode the address of the label
			 */

			 if (op1_type != type_unrecognized){
				if (op1_type==type_label){

					relevant_symbol=search_symbol(current.OPERAND1,*symbols);

					if (relevant_symbol->declared_as==external){
						calculated_memory_line=EXTERNAL_VALUE; /*adding 0001*/
						add_external_item_to_list(external_labels_list,current.OPERAND1,ic_address);
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/


					}
					else {
						calculated_memory_line=encode_operand(op1_type,current.OPERAND1,*symbols,FALSE); /*FALSE is relevant to registers only*/
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/
					}
					/*end of op1==label*/
				}


				else if (op1_type==type_matrix){
					String derived_label,reg_searcher;
					String reg1,reg2;
					int label_length;


					/*derive_label*/
					/*reg_searcher=strchr(current.OPERAND1,'[');
					label_length=CALCSIZE(current.OPERAND1,reg_searcher);
					derived_label=allocate_mem_string(label_length+1);
					strncy_safe(derived_label,current.OPERAND1,label_length);*/
					derived_label=extract_mat_label(current.OPERAND1);

					relevant_symbol=search_symbol(derived_label,*symbols);

					label_length=strlen(derived_label);

					if (relevant_symbol->declared_as==external){
						calculated_memory_line=EXTERNAL_VALUE;
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/

					}
					else {
						calculated_memory_line=encode_operand(type_label,derived_label,*symbols,FALSE); /*FALSE is relevant to registers only*/
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/
					}

					/*extract registers*/
					reg_searcher=current.OPERAND1;
					reg1=extract_reg_from_mat(reg_searcher);
					reg_searcher+=label_length+REG_NAME_LENGTH;
					reg2=extract_reg_from_mat(reg_searcher); /*reg_searcher is apointer that is used to extract reg names.*/
					calculated_memory_line=encode_register(reg1,reg2);
					ADD_CALCULATED_VALUE_TO_LIST



						/*print label address*/
					/*another memory word for the registers*/

					/*end of op1_type == matrix*/
				}

				else if (op1_type==type_register){

					if (op2_type==type_register){
						calculated_memory_line=encode_register(current.OPERAND1,current.OPERAND2);
						ADD_CALCULATED_VALUE_TO_LIST
					}
					else {
						calculated_memory_line=encode_operand(op1_type,current.OPERAND1,*symbols,TRUE);
						ADD_CALCULATED_VALUE_TO_LIST
					}

					/*end of op1_type == register*/

				}

				else if (op1_type==type_intermid){
					calculated_memory_line=encode_operand(op1_type,current.OPERAND1,*symbols,FALSE);
					ADD_CALCULATED_VALUE_TO_LIST

					/*end of op1=direct*/
				}


				/*end of op1_type != type_unrecognized*/
			}

			if (op2_type != type_unrecognized){
				if (op2_type==type_label){
					relevant_symbol=search_symbol(current.OPERAND2,*symbols);

					if (relevant_symbol->declared_as==external){
						calculated_memory_line=EXTERNAL_VALUE;
						add_external_item_to_list(external_labels_list,current.OPERAND2,ic_address);

						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/

					}
					else {
						calculated_memory_line=encode_operand(op2_type,current.OPERAND2,*symbols,FALSE); /*FALSE is relevant to registers only*/
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/
					}
					/*end of op2==label*/
				}

				else if (op2_type==type_matrix){
					String derived_label,reg_searcher;
					String reg1,reg2;
					int label_length;


					/*derive_label*/
					derived_label=extract_mat_label(current.OPERAND2);
					label_length=strlen(derived_label);


					printf("derived matrix label: <%s>\n",derived_label);

					relevant_symbol=search_symbol(derived_label,*symbols);
					printf("found_symbol\n");
					if (relevant_symbol->declared_as==external){
						calculated_memory_line=EXTERNAL_VALUE;
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/

					}
					else {
						calculated_memory_line=encode_operand(type_label,derived_label,*symbols,FALSE); /*FALSE is relevant to registers only*/
						ADD_CALCULATED_VALUE_TO_LIST /*creates encoded struct and adds to list*/
					}

					/*extract registers*/
					reg_searcher=current.OPERAND2;
					reg1=extract_reg_from_mat(reg_searcher);
					reg_searcher+=label_length+REG_NAME_LENGTH;
					reg2=extract_reg_from_mat(reg_searcher); /*reg_searcher is apointer that is used to extract reg names.*/
					calculated_memory_line=encode_register(reg1,reg2);
					ADD_CALCULATED_VALUE_TO_LIST



						/*print label address*/
					/*another memory word for the registers*/

					/*end of op2_type == matrix*/
				}


				else if (op2_type==type_register){
					printf("op2 is reg\n");

					if (op1_type !=type_register){
						printf("op2 is reg\n");
						calculated_memory_line=encode_operand(op2_type,current.OPERAND2,*symbols,FALSE);

						ADD_CALCULATED_VALUE_TO_LIST
					}


					/*end of op2_type == register*/

				}



				else if(op2_type==type_intermid){
					calculated_memory_line=encode_operand(op1_type,current.OPERAND1,*symbols,FALSE);
					ADD_CALCULATED_VALUE_TO_LIST

					/*end of op2=direct*/
				}
				/*end of op2_type != type_unrecognized*/
			}





			/*end of the operation*/
		}

		else {/*set as instruction*/

			/*mark the symbol for future printing*/
			if (strcmp(current.instruction,ENTRY)==0){
				search_symbol(current.OPERAND1,*symbols)->is_entry=TRUE;
			}

			if (strcmp(current.instruction,DATA)==0){
				length=current.data_values_number;


				for(j=0;j<length;j++){
					combined_data_list[combined_data_list_counter]=current.data_int_values[j];
					combined_data_list_counter++;
				}
				/*end of data*/
			}

			if (strcmp(current.instruction,STR)==0){
				length=strlen(current.OPERAND1);
				for(j=0;j<length;j++){
					combined_data_list[combined_data_list_counter]=current.OPERAND1[j];
					combined_data_list_counter++;
				}

				combined_data_list[combined_data_list_counter]='\0';
				combined_data_list_counter++;
			/*end of STR*/
			}
			printf(KRED"trying to access mat params in the struct\n");
			NORMALCOLOR
			printf("instruction: %s\n",current.instruction);
			if (strcmp(current.instruction,MAT)==0){
				int m=0;

				length=current.mat_size;


				printf("mat size: %d\n",current.mat_size);

				for(j=0;j<length;j++){
					if (m<current.data_values_number){
						combined_data_list[combined_data_list_counter]=current.data_int_values[m];
						combined_data_list_counter++;
						m++;
					}
					else {
						combined_data_list[combined_data_list_counter]=0;
						combined_data_list_counter++;
					}
				}
				/*end of MAT*/
			}

		}

		/*end of the main loop*/
	}


	for (j=0;j<combined_data_list_counter;j++){
		calculated_memory_line=combined_data_list[j];
		ADD_CALCULATED_VALUE_TO_LIST

	}

	printf("encoded list before exiting second scan: %d\n",((*encoded_list)->address));
	temp=*encoded_list;
	while (temp!=NULL){
		printf("address: %d\n",temp->address);
		temp=temp->next;
	}
	return TRUE;
}



int code_command_line(int opcode,Operand_type op1, Operand_type op2, int rea){
	int op1_coded,op2_coded;
	int result=0;

	printf(KCYN);

	result=opcode;
	result<<=WORD_SIZE-OPCODE_SIZE;
/*	printf("opcode received: %d result: ",opcode);*/



	if (opcode <4 || opcode==6 ){
		/*src exists*/

		op1_coded=op1<<OPER_SIZE*2;
		op2_coded=op2<<OPER_SIZE;

		result|=op1_coded;
		result|=op2_coded;

/*		printf("operand1: %d\n",op1);*/

	}

	else { /*opcode is4,5, or >6*/

		/*no source for these commands*/

		op1_coded=op1<<OPER_SIZE;

		result|=op1_coded;

	}



		/*EXTRACT THE LAST BITS*/
	if(rea!=ABSOLUTE_VALUE){
		result|=rea;
	}



/*
	printf("result: ");
	print_bin(result);*/
	NORMALCOLOR

	return result;
}








int get_opcode(String command){

	if (strcmp(command,CMP) ==0 ){
		return 1;
	}

	if (strcmp(command,ADD) ==0 ){
		return 2;
	}

	if (strcmp(command,SUB) ==0 ){
		return 3;
	}


	if (strcmp(command,NOT) ==0 ){
		return 4;
	}

	if (strcmp(command,CLR) ==0 ){
		return 5;
	}
	if (strcmp(command,LEA) ==0 ){
		return 6;
	}

	if (strcmp(command,INC)==0){
		return 7;
	}

	if (strcmp(command,DEC)==0){
		return 8;
	}

	if (strcmp(command,JMP)==0){
		return 9;
	}

	if (strcmp(command,BNE)==0){
		return 10;
	}

	if (strcmp(command,RED)==0){
		return 11;
	}
	if (strcmp(command,PRN)==0){
		return 12;
	}

	if (strcmp(command,JSR)==0){
		return 13;
	}

	if (strcmp(command,RTS)==0){
		return 14;
	}

	if (strcmp(command,STOP)==0){
		return 15;
	}
	return 0;

}


int encode_register(String op1,String op2){
	int op1_n,op2_n;
	int result;


	/*first char is r, second is num of register*/
	op1_n=(op1[1])-'0';
	op2_n=(op2[1])-'0';

	result=0;

	result=op1_n<<(WORD_SIZE-OPCODE_SIZE);
	result|=(op2_n<<OPER_SIZE);
	/*last two bits are 00 (because it's absolute*/


	return result;
}



int encode_operand(Operand_type type,String op, symbol_ptr symbols, Bool is_source){
	int result;
	symbol_ptr symbol_found;


	result=0;
	if (type==type_intermid){
		op+=1;
		result=atoi(op);
		result<<=OPER_SIZE;
		return result;
	}

	if (type==type_label){

		symbol_found=search_symbol(op,symbols);

		if ((symbol_found->declared_as)==external){
			result=EXTERNAL_VALUE;
			return result;
		}

		result=(symbol_found->address)+INITIAL_ADDRESS;
		result<<=OPER_SIZE;
		result|=RELLOCATABLE_VALUE;
		return result;
	}

	if (type==type_register){
		result=(op[1])-'0';
		if (is_source==TRUE){
			result<<=(WORD_SIZE-OPCODE_SIZE);
			return result;
		}else{
			result<<=OPER_SIZE;
			return result;

		}

	}

	/*MATRIX*/

	return result;
}



encoded_ptr create_encoded_struct(int address,int value){
	encoded_ptr encoded_struct;

	encoded_struct=(encoded_ptr)allocate_mem_general(1,sizeof(encoded));

	encoded_struct->address=address;
	encoded_struct->value=value;
	encoded_struct->next=NULL;

	return encoded_struct;

}

void print_encoded_struct(encoded_ptr s){
	encoded_ptr pointer;

	printf(BOLDWHITE"\n");
	printf("%-15s|","ADDRESS");
	printf("%-15s|","VALUE");
	printf("\n");
	NORMALCOLOR

	pointer=s;
	while (pointer->next != NULL){
/*		n=pointer->address;*/
		print_bin(pointer->value);

		pointer=pointer->next;
	}


	print_bin(s->value);

	printf("\n");
}

void add_encoded_struct_to_list(encoded_ptr * list, encoded_ptr item){
	encoded_ptr p;

	if (*list==NULL){
		(*list)=item;
		(*list)->next=NULL;
		return;
	}

	p=*list;

	while (p->next != NULL){
		p=p->next;
	}

	p->next=item;

	printf("added value %d to list\n",p->address);

/*	printf(KRED"encoded to struct - item:%s, item:%s\n",p->value,item->value);*/
}


String extract_reg_from_mat(String oper){
	String reg,pointer;

	reg=allocate_mem_string(REG_NAME_LENGTH+1);
	pointer=strchr(oper,'[');
	pointer+=1; /*advancing 1 to skip the [*/
	printf("found pointer: %s\n",pointer);

	strncy_safe(reg,pointer,REG_NAME_LENGTH);
	printf("found reg: %s\n",reg);
	return reg;


}

/*
 * This function receives a matrix operand (M1[r3][r2])
 * and extracts the label M1 by calculating the length of the label, and copying it
 * to 'result'
 * the function the returns 'result'
 */
String extract_mat_label (String str){
	String label,searcher;
	int label_length;

	searcher=strchr(str,'[');
	label_length=CALCSIZE(str,searcher);
	label=allocate_mem_string(label_length+1);
	strncy_safe(label,str,label_length);

	return label;

}
