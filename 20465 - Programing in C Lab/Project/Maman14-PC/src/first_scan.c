/*
 * label_finder.c
 *
 *  Created on: Aug 25, 2017
 *      Author: alexz
 */

#include "first_scan.h"







/*
 * Searches and returns a symbol for a given key (a label in a list of labels)
 */
symbol_ptr search_symbol (String key, symbol_ptr list){
	symbol_ptr current_pointer=list;

	if (!list){
		return NULL;
	}

	while ((current_pointer->next)!=NULL){
		if (strcmp(key,current_pointer->name) == 0){
			return current_pointer;

		}
		current_pointer=current_pointer->next;
	}


	if (strcmp(current_pointer->name,key)==0){
		return current_pointer;
	}

	return NULL;
}


Bool first_scan(bodyArray items, int bodyarray_size, symbol_ptr* symbols_list_head, int* IC,int* DC,external_labels_ptr* external_labels){
	int item_counter;
	body current;
	char error[MAXERRORSIZE];
	symbol_ptr current_symbol;
	list_item_reference errors_list=NULL;
	Bool valid_file=TRUE;




	for (item_counter=0;item_counter<bodyarray_size;item_counter++){
		current=items[item_counter];

		/*Label exists*/
		if (strlen(current.label) != 0){
			/*check if it already exists*/

			if (search_symbol(current.label,*symbols_list_head) != NULL){

				if (search_symbol(current.label,*symbols_list_head)->declared_as ==external){
					sprintf(error,KBLUE"Error is line %d: label %s was declared as .extern and declared in this file.\n",current.line_number, current.label);
					add_to_list(&errors_list,error);
				}

				else {
					sprintf(error,KBLUE"Error is line %d: label %s is a duplicate.\n",current.line_number, current.label);
					add_to_list(&errors_list,error);
				}

				valid_file=FALSE;
				current.valid=FALSE;




			}

			else {
				current_symbol=create_symbol(current,*IC,*DC); /*create new symbol*/
				add_symbol_to_list(current_symbol,symbols_list_head);/*adds to list of symbols*/
				*IC+=calc_new_ic(current);/*advance ic*/
				*DC+=calc_new_dc(current);/*advance dc*/

			}


		}
		/*Label was not recieved*/
		else if (strcmp(current.instruction,EXTERN)==0){
			current_symbol=create_symbol(current,*IC,*DC);/* create new symbol*/

			add_symbol_to_list(current_symbol,symbols_list_head);/*adds to list of symbols*/

/*			add_external_item_to_list(external_labels,current.OPERAND1,0); creates a struct
			(*external_labels_size)++;*/


		}

		else {
			*IC+=calc_new_ic(current);/*advance ic*/

		}



		/*For loop*/
	}




	NORMALCOLOR
	print_list(errors_list);
	return valid_file;

}


symbol_ptr create_symbol(body item,int ic, int dc){
	symbol_ptr sym;


	/*copy label*/
	sym=(symbol_ptr)allocate_mem_general(1,sizeof(sym));
	sym->name=(String)allocate_mem_general(strlen(item.label),sizeof(char));
	strcpy(sym->name,item.label);



	/*Address*/
	if (strlen(item.operantion)==0){ /*is operation was not received*/
		/*instructions*/
		if (strcmp(item.instruction,"data")==0 ||
			strcmp(item.instruction,"mat")==0||
			strcmp(item.instruction,"string")==0){
			sym->address=dc;
			sym->declared_as=internal;
			sym->command_type=instructional;
		}

		if (strcmp(item.instruction,"extern")==0){
			sym->name=item.OPERAND1;
			sym->address=0;
			sym->declared_as=external;
			sym->command_type=unknown;
		}

	}
	else{
		/*Operational Command*/
		sym->address=ic;
		sym->declared_as=internal;
		sym->command_type=operational;

	}




	return sym;

}



void add_symbol_to_list(symbol_ptr current,symbol_ptr* list){
	symbol_ptr p;

	if (!*list){

		/*list=(symbol_ptr)allocate_mem_general(1,sizeof(symbol_ptr));*/
		(*list)=current;
		(*list)->next=NULL;
		return;
	}

	p=*list;
	while (p->next != NULL){
		p=p->next;
	}

	p->next=current;
	p->next->next=NULL;

}



/*
 * This function calculates how much memory to reserve for IC.
 * Receives:
 * Returns: The calculated number.
 * If the command is .extern, we reserve 1 memory;
 * if the command is .data, .mat .string .entry, we reserve none as it uses dc.
 * if the command is one of the 16 operational commands, we reserve 1 for the command itself
 * and 1 more memory for each operand received
 */
int calc_new_ic(body item){
	int n;

	n=0;

	if (strlen(item.operantion)==0){
		/*dealing with instruction*/
		if (strcmp(item.instruction,EXTERN)==0){
			return n;
		}
		return n; /*if we're mat,string,data,entry*/
	}


	n++;
	/*for the command itsef*/
	if (strlen(item.OPERAND1)>0){
		n++;
	}
	if (strlen(item.OPERAND2)>0){
		if (get_operand_type(item.OPERAND1)==REGISTER && get_operand_type(item.OPERAND2)==REGISTER){
			return n;
		}
		n++;
	}

	return n;
}



/*
 * This function calculates how much memory to reserve for DC.
 * Receives:
 * Returns: The calculated number.
 * The number depends on the number of received chars as data
 */

int calc_new_dc(body item){
	int n;
	n=0;

	/*if it's instructional*/
	if (strlen(item.operantion)==0){
		if (strcmp(item.instruction,MAT)==0){

			n=item.mat_size;

			printf("n: %d\n",n);
			return n;
		}
		if (strcmp(item.instruction,DATA)==0){
			return item.data_values_number;
		}

		if (strcmp(item.instruction,STR)==0){
			/*string*/
			n=strlen(item.OPERAND1);
			n++;/*save spaces for \0*/
		}
	}


	return n;
}


void update_data_addresses(symbol_ptr* symbols,int IC){
	symbol_ptr current;


	current=*symbols;

	if (current==NULL){
		return;
	}
	while (current->next != NULL){
		if (current->command_type==instructional && current->declared_as==internal){
			current->address=current->address+IC;
		}
		current=current->next;
	}

	if (current->command_type==instructional && current->declared_as==internal){
		current->address=current->address+IC;
	}

}


void add_external_item_to_list (external_labels_ptr* list,String value, int address){
	external_labels_ptr p;
	external_labels_ptr new;

	printf(KYELLOW"adding item <%s> to external\n",value);
	new=(external_labels_ptr)allocate_mem_general(1,sizeof(external_labels));
	new->address=address;
	new->value=allocate_mem_string(strlen(value)+1);
	strcpy(new->value,value);

	printf("created an item\n");

	if (*list==NULL){

		*list=new;
		(*list)->next=NULL;
		return;
	}

	p=*list;
	while(p->next!=NULL){
		p=p->next;
	}
	p->next=new;
	new->next=NULL;

}
