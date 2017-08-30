/*
 * output.h
 *
 *  Created on: Aug 30, 2017
 *      Author: alexz
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "utils.h"
#include "second_scan.h"



void create_obj_file(encoded_ptr encoded_list,String file_name);

void_create_entry_file(encoded_ptr symbols);


void create_extern_file(encoded_ptr symbols);

String convert_to_base4(unsigned int, int);


#endif /* OUTPUT_H_ */
