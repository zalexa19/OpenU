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

#define AS ".as"



Bool create_obj_file(encoded_ptr encoded_list,String file_name, int, int);

Bool create_entry_file(symbol_ptr symbols,String file_name);


Bool create_extern_file(symbol_ptr symbols,String file_name,external_labels_ptr external_labels_list);

String convert_to_base4(unsigned int, int);
/*String convert_to_base4_sums(unsigned int number);*/

#endif /* OUTPUT_H_ */
