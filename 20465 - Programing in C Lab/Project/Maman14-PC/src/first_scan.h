/*
 * label_finder.h
 *
 *  Created on: Aug 25, 2017
 *      Author: alexz
 */

#include "utils.h"



#ifndef LABEL_FINDER_H_
#define LABEL_FINDER_H_





typedef struct external_labels* external_labels_ptr;

typedef struct external_labels{
	int address;
	String value;
	external_labels_ptr next;

}external_labels;









Bool first_scan(bodyArray items, int, symbol_ptr*, int*, int*,external_labels_ptr*);



symbol_ptr search_symbol (String, symbol_ptr);

symbol_ptr create_symbol(body item,int, int);

void add_symbol_to_list(symbol_ptr item,symbol_ptr *);

int calc_new_ic(body);
int calc_new_dc(body);

void update_data_addresses(symbol_ptr*,int);
void add_external_item_to_list (external_labels_ptr* list,String value, int address);


#endif /* LABEL_FINDER_H_ */
