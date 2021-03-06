/*
 * utils.c
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#include "utils.h"
#include "first_scan.h"


int structs_array_size;

/*String* allocate_mem_matrix(int size){
	String* matrix = (String*)malloc(sizeof( String*)*size);
	if (!matrix){
		fprintf(stderr,"Unable to allocate memory to the matrix.\nContinuing with no operanns\n");
		exit(0);
	}
	return matrix;
}*/


String allocate_mem_string (int size){
	String	str;
	str= (String)malloc (size * sizeof(char));
	if (!str){
		fprintf(stderr,"---Unable to allocate memory\n");
	}

/*	fprintf(stderr,"---Memory allocated successfully, size: %d\n",size);*/
	return str;
}



parsed_item_ptr allocate_mem_struct (int size){
	parsed_item_ptr array=(parsed_item_ptr) malloc(sizeof(parsed_item)*size);

	if (!array){
		fprintf(stderr,"---Unable to allocate memory to structs-array");
		exit(0);

	}
	return array;

}

int increase_mem_struct (int size,parsed_item_ptr array){
	int new_size=size*2;
	parsed_item_ptr tmp = (parsed_item_ptr)realloc(array,sizeof(parsed_item)*new_size);
	if (!tmp){
		fprintf(stderr,"unable to increase memory to structs-array");
		exit (0);
	}

	array=tmp;
	return new_size;

}


/*
 * This function retrieves the command type received in a line.
 * It receives a struct with the parsed line and returns
 * 0 if it's an instruction, 1 if it's an operation
 * 2 if it's neither (when the line has invalid syntax
 * note: unused fields in the struct are saved as '\0'
 */
command_type get_command_type(parsed_item item){
	if (strlen(item.instruction)>0){
		return instruction;
	}

	if (strlen(item.operantion)>0){
		return operation;
	}

	return unrecognized_command;
}
























void print_structs(parsed_item_ptr array, int size){
	int i;
	char tmp[15];

	i=0;
	printf("\n--------------------------------------------------------");
	printf("--------------------------------------------------------\n");
	printf("                       STRUCT PRINT:\n");
	printf("\n--------------------------------------------------------");
	printf("--------------------------------------------------------\n");

	printf("\n");
	printf("Line |");
	printf("LABEL        |");
	printf("INSTRUCTION  |");
	printf("OPERATION    |");
	printf("OPERAND1     |");
	printf("OPERAND2     |");
	printf("OPERAND3     |");
	printf("\n");


	for (i=0;i<size;i++){
		printf(KYELLOW);
		/*Line number*/
		printf("%d    ",array[i].line_number);

		/*label*/
		if ((strcmp(array[i].label,"\0") ) !=0){
			strcpy(tmp,array[i].label);
			add_spaces_print(tmp);
			printf("%s",tmp);

		}else printf("               ");




/*		if ((strcmp(array[i].instruction,"\0") ) !=0){

		}*/
		strcpy(tmp,array[i].instruction);
		add_spaces_print(tmp);
		printf("%s",tmp);


		if (strcmp(array[i].instruction,"mat")==0){
			strcpy(tmp,array[i].operand1);
			add_spaces_print(tmp);
			printf("%s",tmp);

			print_mat(array[i].data_string_array,array[i].data_values_number);

/*
			if (strlen(array[i].data_string_array)>0){
				print_mat(array[i].data_string_array,array[i].data_values_number);
			}*/

			printf("\n");

		}
		else {


			if (strcmp(array[i].instruction,"data")==0){
				print_mat(array[i].data_string_array,array[i].data_values_number);

			}else printf("               ");

				/*OPERATION*/
			if ((strcmp(array[i].operantion,"\0") ) !=0){
				strcpy(tmp,array[i].operantion);
				add_spaces_print(tmp);
				printf("%s",tmp);
			}else printf("               ");


			if (strcmp(array[i].instruction,"data")!=0){

				if ((strcmp(array[i].operand1,"\0") ) !=0)
				{
						strcpy(tmp,array[i].operand1);
						add_spaces_print(tmp);
						printf("%s",tmp);
				}else printf("               ");





				if ((strcmp(array[i].operand2,"\0")) !=0){
						strcpy(tmp,array[i].operand2);
						add_spaces_print(tmp);
						printf("%s",tmp);
					}else printf("               ");

				if ((strcmp(array[i].leftovers,"\0")) !=0){
						strcpy(tmp,array[i].leftovers);
						add_spaces_print(tmp);
						printf("%s",tmp);
					}else printf("               ");


			}
		}
		printf("\n");
	}
	printf("\n-------------------------------------------------");
	printf("--------------------------------------------------\n");
}


void add_spaces_print (String  array){
	int length;
	int i=0;

	length=strlen(array);
	while (array[i] != ' '){
		i++;
	}

	i=length;
	for (i=length; i<14; i++){
		array[i]=' ';
	}

}


void print_line(parsed_item item){

	if (strcmp(item.instruction,"data")==0){
		printf("%d %s %s ",item.line_number,item.label,item.instruction);
		print_mat(item.data_string_array,item.data_values_number);
	}
/*

	if (strcmp(item.instruction,"mat")){
		printf("%d %s %s ",item.line_number,item.label,item.instruction);
		print_mat(item.data_string_array,item.data_values_number);
	}
*/

	else {
		printf("<%d",item.line_number);
		if (strcmp(item.label,"\0")!=0){
			printf(" %s",item.label);
		}

		if (strcmp(item.instruction,"\0")!=0){
			printf(" %s",item.instruction);

		}
		if (strcmp(item.operantion,"\0")!=0){
			printf(" %s",item.operantion);

		}

		if (strcmp(item.operand1,"\0")!=0){
			printf(" %s",item.operand1);

		}

		if (strcmp(item.operand2,"\0")!=0){
			printf(" %s",item.operand2);

		}

		if (strcmp(item.leftovers,"\0")!=0){
			printf(" %s",item.leftovers);

		}
	}
	printf(">\n");
}

void print_mat (String* mat, int size){
	int i;

	for (i=0;i<size;i++){
		printf("%s ",*mat);
		mat++;
	}

	NORMALCOLOR

	printf(" ");

}


/*
 * Linked List
 */

void add_to_list(list_item_reference * head, String str){
	list_item_reference new_item,temp;

	if ((new_item = (list_item_reference)malloc( sizeof(list_item))) == NULL)
	{
		fprintf(stderr,"unable to allocate memory to a list item. Exiting the program\n");
		exit(0);
	}

	new_item->str=allocate_mem_string(strlen(str)+1);

	strcpy(new_item->str,str);
	new_item->next=NULL;

	if (*head == NULL){
		new_item->prev=NULL;
		*head=new_item;
	}
	else{
		temp=*head;

		while (temp->next != NULL){
			temp=temp->next;
		}

		temp->next=new_item;
		new_item->prev=temp;
	}

}

void print_list(list_item_reference head){

	if (head==NULL){
		printf("Empty list\n");
		return;
	}


	while (head != NULL){
		printf("%s",head->str);
		head=head->next;
	}
	printf("\n");
}

void free_list(list_item_reference *head){
	free(*head);
}



void strncy_safe(String  dest, String  source, int size){

	strncpy(dest,source,size);
	dest[size]='\0';
}


void * allocate_mem_general(int count, int size){

	void * p;
	p = malloc(size*count);


	if (!p){
		fprintf(stderr,"Unable to allocate memory. exiting thr program\n.");
		exit(1);
	}

	return p;
}


void print_symbol_list(symbol_ptr head){
	symbol_ptr pointer;

	pointer=head;
	printf(BOLDYELLOW"\n-----------------------------------------------");
	printf("-----------------------------------------------\n");
	printf("                       SYMBOLS PRINT:\n");
	printf("\n-----------------------------------------------");
	printf("-----------------------------------------------\n");
	NORMALCOLOR


	if (head==NULL){
		printf("EMPTY LIST\n");
		return;
	}

	printf(BOLDWHITE"\n");
	printf("%-15s|","LABEL");
	printf("%-15s|","DECLARED AS");
	printf("%-15s|","LINKED TO");
	printf("%-15s|","ADDRESS");
	printf("%-15s|","MATRIX?");

	printf("\n");
	NORMALCOLOR

	while (pointer->next != NULL){

		printf("%-15s|",pointer->name);

		if (pointer->command_type == instructional){
			printf("%-15s|","instructional");
		}
		else if (pointer->command_type == operational){
			printf("%-15s|","operational");
		}else {
			printf("%-15s|","unknown");
		}
		if (pointer->declared_as == internal){
			printf("%-15s|","internal");
		}
		else {
			printf("%-15s|","external");

		}

		printf("%-15d|",pointer->address);

		printf("\n");
		pointer=pointer->next;
	}



	if (!pointer->next){
		printf("%-15s|",pointer->name);
		if (pointer->command_type == instructional){
			printf("%-15s|","instructional");
		}
		else if (pointer->command_type == operational){
			printf("%-15s|","operational");
		}else {
			printf("%-15s|","unknown");
		}
		if (pointer->declared_as == internal){
			printf("%-15s|","internal");
		}
		else {
			printf("%-15s|","external");

		}

		printf("%-15d|",pointer->address);
		printf("%-15d|",pointer->is_matrix);


	}




	printf("\n");


}



void print_bin(int n){
	char result[32];
	int i = 0;
	int j = 0;

	if(n==0) {
		printf("0\n");
		return;
	}

	while (n) {
	    if (n & 1)
	        result[i++]='1';
	    else
	        result[i++]='0';

	    n >>= 1;
	}

	/* leading zeros */
	for(j=10; j>i; j--) {
		printf("0");
	}
	while((--i)>=0) {
		if(i%4==0) {
			printf("-");
		}
		printf("%c",result[i]);
	}
	printf("\n");
}


void print_binary_array(int array[], int size){
	int i;

	printf(BOLDYELLOW"\n-----------------------------------------------");
	printf("-----------------------------------------------\n");
	printf("                       BINARY PRINT:\n");
	printf("\n-----------------------------------------------");
	printf("-----------------------------------------------\n");
	NORMALCOLOR




	for (i=0;i<size;i++){
		print_bin(array[i]);
	}
}

