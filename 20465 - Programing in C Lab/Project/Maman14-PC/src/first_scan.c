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

	while (current_pointer != NULL){

		if (strcmp(key,current_pointer->name) == 0){
			return current_pointer;

		}
		current_pointer=current_pointer->next;
	}
	return NULL;
}
/*
 * for each line:
 * if it has a label, a new symbol struct is created for the label and added to the symbol list + caluclate ic
 * if its an operational command, we calculate ic
 * if it's instructional command, we calculate dc
 *
 * this stage can fail if the a label is declared twice in the assembly file
 */

Bool first_scan(parsed_item_ptr items, int bodyarray_size, symbol_ptr* symbols_list_head, int* IC,int* DC){
	int item_counter; /*how many items are scanned*/
	parsed_item current; /*current item*/
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
					sprintf(error,"Error is line %d: label %s was declared as .extern and declared in this file.\n",current.line_number, current.label);
					add_to_list(&errors_list,error);
				}

				else {
					sprintf(error,"Error is line %d: label %s is a duplicate.\n",current.line_number, current.label);
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

		}
		else {
			*IC+=calc_new_ic(current);/*advance ic*/
		}
	}
	return valid_file;
}


/*
 * this function receives the parsed line struct, ic, dc and creates a new symbol with all the required info
 * it return a pointer of this symbol
 * name = label
 */

symbol_ptr create_symbol(parsed_item item,int ic, int dc){
	symbol_ptr sym;


	/*copy label*/
	sym=(symbol_ptr)allocate_mem_general(1,sizeof(symbol));

	sym->name=allocate_mem_string(strlen(item.label)+1);
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
			if (strcmp(item.instruction,"mat")==0){
				sym->is_matrix=TRUE;
			}
			else {
				sym->is_matrix=FALSE;

			}
		}

		if (strcmp(item.instruction,"extern")==0){
			sym->name=item.operand1;
			sym->address=0;
			sym->declared_as=external;
			sym->command_type=unknown;
			sym->is_matrix=FALSE;

		}

	}
	else{
		/*Operational Command*/
		sym->address=ic;
		sym->declared_as=internal;
		sym->command_type=operational;
		sym->is_matrix=FALSE;

	}
	return sym;

}

/*
 * receives a symbol struct and adds it to the list by pointing the last node.next to the new symbol
 */

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
int calc_new_ic(parsed_item item){
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
	if (strlen(item.operand1)>0){

		if (item.op1_type==type_matrix){
			n+=2;
		}
		else{
		n++;
		}
	}
	if (strlen(item.operand2)>0){
		if (item.op1_type==type_register && item.op2_type==type_register){
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

int calc_new_dc(parsed_item item){
	int n;
	n=0;

	/*if it's instructional*/
	if (strlen(item.instruction)>0){
		if (strcmp(item.instruction,MAT)==0){
			n=item.mat_size;
			return n;
		}
		if (strcmp(item.instruction,DATA)==0){
			n=item.data_values_number;
			return n;

		}

		if (strcmp(item.instruction,STR)==0){
			/*string*/
			n=strlen(item.operand1);
			n++;/*save spaces for \0*/
		}
	}

	return n;
}

/*
 * this function receives the symbols list (it's address) and update each instructional non-external address
 * with the ic, to make sure that this info appears at the end of the ob file.
 * this function is invoked after the first scan by the main
 */
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

/*
 * whenever we encounter a command which uses an external label, we save the address and the value of this label in this list
 * this list is later sent to the output module which creates the .ext from this.
 * it receives the list address, the value and it's address
 */

void add_external_item_to_list (external_labels_ptr* list,String value, int address){
	external_labels_ptr p;
	external_labels_ptr new;

	new=(external_labels_ptr)allocate_mem_general(1,sizeof(external_labels));
	new->address=address;
	new->value=allocate_mem_string(strlen(value)+1);
	strcpy(new->value,value);


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
