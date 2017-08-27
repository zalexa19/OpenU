/*
 * label_finder.h
 *
 *  Created on: Aug 25, 2017
 *      Author: alexz
 */

#include "utils.h"



#ifndef LABEL_FINDER_H_
#define LABEL_FINDER_H_

typedef enum{
	instructional=0,
	operational=1,
	unknown=2
}label_type;

typedef enum{
	internal=0,
	external=1
}declared;


typedef struct symbol* symbol_ptr;

typedef struct symbol{
	String name;
	label_type command_type;
	declared declaration_type;
	int address;
	symbol_ptr next;
}symbol;












void first_scan(bodyArray items, int);



symbol_ptr search_symbol (String, symbol_ptr);

symbol_ptr create_symbol(body item,int, int);

void add_symbol_to_list(symbol_ptr item,symbol_ptr *);

int calc_new_ic(body);
int calc_new_dc(body);





#endif /* LABEL_FINDER_H_ */
