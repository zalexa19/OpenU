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


Bool second_scan (bodyArray parsed, int parsed_size, symbol_ptr*symbols, int ic,encoded_ptr* encoded_list,int DC,external_labels_ptr* external_labels_list){
	int i,j, length,general_counter,address_helper;
	int result,counter,data_counter;
	body current;
	int opcode; /*stores the opcode received*/
	Operand_type op1_type,op2_type;
	int data_array[DC];
	encoded_ptr encoded_node;
	Bool valid_file=TRUE;



	general_counter=data_counter=counter=0;
	address_helper=0;
	*encoded_list = NULL;


	/*Check if the label is valid*/
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
			if (get_operand_type(current.OPERAND1)==LABLE){
				if (!search_symbol(current.OPERAND1,*symbols)){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND1);
					valid_file=FALSE;
				}

			}

/*			printf("checking if op2 is a label\n");*/

			if (get_operand_type(current.OPERAND2)==LABLE){

				if (!(search_symbol(current.OPERAND2,*symbols))){ /*label is not found*/
					fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.OPERAND2);
					valid_file=FALSE;
				}

			}

		}
	}

	if (valid_file==FALSE){
		return FALSE;
	}

	/*ALL LABELS ARE VALID*/
	for (i=0;i<parsed_size;i++){
		symbol_ptr current_symbol;
		current=parsed[i];
		NORMALCOLOR


		/*Working on operation*/
		if (strlen(current.operantion)>0){
			opcode=get_opcode(current.operantion);
			op1_type=get_operand_type(current.OPERAND1);
			op2_type=get_operand_type(current.OPERAND2);

			result=code_command_line(opcode,op1_type,op2_type,ABSOLUTE_VALUE);
			encoded_node=create_encoded_struct(address_helper,result); /*address helper = counts address for operationals as well*/
			add_encoded_struct_to_list(encoded_list,encoded_node);
			address_helper++;
			counter++; /*COUNTER FOR LENGTH OF ENCODED VALUES*/


			/*encode operands*/
			if (op1_type==op2_type && op1_type==REGISTER){
				result=encode_register(current.OPERAND1,current.OPERAND2);

				encoded_node=create_encoded_struct(address_helper,result);

				add_encoded_struct_to_list(encoded_list,encoded_node);
				address_helper++;

/*				commands_array[counter]=result;*/
				counter++;

			}
			else {
				if (op1_type != UNRECOGNIZED){ /*is operand1 exists*/
					if(op2_type==UNRECOGNIZED){
						result=encode_operand(op1_type,current.OPERAND1,*symbols,FALSE);
					}
					else {
						result=encode_operand(op1_type,current.OPERAND1,*symbols,TRUE);

					}

					/*if operation uses labels that are external, we add it to the external list to export to the file*/
					if (op1_type==LABLE){
						current_symbol=search_symbol(current.OPERAND1,*symbols);
						if (current_symbol->declared_as==external){
/*							printf(KRED"label %s is external\n",current.OPERAND1);*/
							printf("current address:%d\n",address_helper+100);

							add_external_item_to_list(external_labels_list,current.OPERAND1,address_helper);

						}

					}

					if (op1_type==MATRIX){
						String derived_label,reg_searcher;
						String reg1,reg2;
						int label_length;

						reg_searcher=current.OPERAND1;
						reg_searcher+=label_length;
/*						printf("reg searcher:%s\n",reg_searcher);*/

						reg1=extract_reg_from_mat(reg_searcher);
/*						printf("reg1: %s\n",reg1);*/

						reg_searcher+=label_length+REG_NAME_LENGTH;
/*						printf("reg searcher:%s\n",reg_searcher);*/
						reg2=extract_reg_from_mat(reg_searcher); /*reg_searcher is apointer that is used to extract reg names.*/
						/*to skip: "[r# and point to ][r#]*/



						derived_label=strchr(current.OPERAND1,'[');

						label_length=CALCSIZE(current.OPERAND1,derived_label);

						derived_label=allocate_mem_string(label_length+1);
						strncy_safe(derived_label,current.OPERAND1,label_length);

						current_symbol=search_symbol(derived_label,*symbols);

						/*encode the label address*/
						result=encode_operand(LABLE,derived_label,*symbols,FALSE);

						encoded_node=create_encoded_struct(address_helper,result);

						add_encoded_struct_to_list(encoded_list,encoded_node);

						address_helper++;
						counter++;

						/*encode registries*/

						printf(KYELLOW"----------------------------------------------------------\n");
						result=encode_register(reg1,reg2);

						printf(KYELLOW"----------------------------------------------------------\n");

						encoded_node=create_encoded_struct(address_helper,result);
						add_encoded_struct_to_list(encoded_list,encoded_node);
						address_helper++;

						counter++;

						NORMALCOLOR
					}

					else {
						encoded_node=create_encoded_struct(address_helper,result);

						add_encoded_struct_to_list(encoded_list,encoded_node);
						address_helper++;
						counter++;
					}
				}

				if (op2_type!=UNRECOGNIZED){
					result=encode_operand(op2_type,current.OPERAND2,*symbols,FALSE);
					encoded_node=create_encoded_struct(address_helper,result);

					add_encoded_struct_to_list(encoded_list,encoded_node);

					if (op2_type==LABLE){
						current_symbol=search_symbol(current.OPERAND2,*symbols);
						if (current_symbol->declared_as==external){
							add_external_item_to_list(external_labels_list,current.OPERAND2,address_helper);
							printf(KRED"label2 %s is external\n",current.OPERAND2);
							printf("current address:%d\n",address_helper+100);
							NORMALCOLOR
						}
					}
					address_helper++;
					counter++;
				}
			}
		}
		/*Instructiion was received*/
		else {
			printf("Entered instruction condition for instruction %s\n",current.instruction);
			printf("current instruction command: <%s>\n",current.instruction);
			if (strcmp(current.instruction,ENTRY)==0 ) {
				search_symbol(current.OPERAND1,*symbols)->is_entry=TRUE;
			}

				/*treat mat and data*/
			else if (strcmp(current.instruction,DATA)==0){
				length=current.data_values_number;
				printf("length: %d\n",length);

				printf(KCYN,"2.Working on .DATA\n");
				print_line(current);

				for(j=0;j<length;j++){
					printf("-----------<><><<>\n");
					data_array[data_counter]=current.data_int_values[j];
					data_counter++;
					general_counter++;
				}
				printf("%d\n",data_array[data_counter-1]);
			}

			/*
			 * When handling mat, we copy each number recieved into the data_array. if we received less values than matrix size,
			 * Zeros are added
			 */

			else if (strcmp(current.instruction,MAT)==0){
				int m=0;

				printf("\n8. I'm in mat\n");
				printf("mat_size %d\n", current.mat_size);

				length=current.mat_size;

				for(j=0;j<current.mat_size;j++){
					if (m<current.data_values_number){
						data_array[data_counter]=current.data_int_values[m];
						data_counter++;
						general_counter++;
						m++;
					}
					else {
						data_array[data_counter]=0;
						data_counter++;
						general_counter++;
					}
				}

				printf("%d ",data_array[data_counter]);
			}

			if (strcmp(current.instruction,STR)==0){
				length=strlen(current.OPERAND1);

				for(j=0;j<length;j++){
					data_array[data_counter]=current.OPERAND1[j];
					data_counter++;
					general_counter++;
				}
				NORMALCOLOR
				printf("\n");
			}

		}

	}

	/*adding the data array to the struct*/

	for (j=0;j<data_counter;j++){

		printf("linking %d to address %d\n",data_array[j],address_helper);

		encoded_node=create_encoded_struct(address_helper,data_array[j]);

		add_encoded_struct_to_list(encoded_list,encoded_node);

		address_helper++;
	}


	printf("added to data_array at the end\n");

/*	*result_size=address_helper;*/
	printf(BOLDGREEN"END OF SECOND SCAN\n");
	NORMALCOLOR
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

		printf("operand1: %d\n",op1);


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

	printf("op1: %s, op2:%s\n");


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
	if (type==INTERMID){
		op+=1;
		result=atoi(op);
		result<<=OPER_SIZE;
		return result;
	}

	if (type==LABLE){

		symbol_found=search_symbol(op,symbols);

		if ((symbol_found->declared_as)==external){
			result=EXTERNAL_VALUE;
			return result;
		}

		result=symbol_found->address;
		result<<=OPER_SIZE;
		result|=RELLOCATABLE_VALUE;
		return result;
	}

	if (type==REGISTER){
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

	printf("successfully created encoded_struct\n");
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
		*list=item;
		(*list)->next=NULL;
		return;
	}

	p=*list;

	while (p->next != NULL){
		p=p->next;
	}

	p->next=item;
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
