/*
 * second_scan.c
 *
 *  Created on: Aug 27, 2017
 *      Author: alexz
 */

#include "second_scan.h"

Bool second_scan (bodyArray parsed, int parsed_size, symbol_ptr * symbols, int ic){
	int IC,DC,i;
	body current;
	Bool valid_file=TRUE;


	IC=DC=0;


	/*Check if the label is valid*/
	for (i=0;i<parsed_size;i++){
		current=parsed[i];
		if (strlen(current.label)>0){
			if (!search_symbol(current.label,*symbols)){ /*label is not found*/
				fprintf(stderr, "Error in line %d: Label %s is undefined\n",current.line_number,current.label);
				valid_file=FALSE;
			}
		}
	}

	if (valid_file==FALSE){
		return FALSE;
	}

	/*ALL LABELS ARE VALID*/





	return TRUE;
}


/*
int code = 0; // 0000000000000
int fifthBit = 1 << 5; //100000

code = 2; // 0000010
code = code << 4 //00000100000*/
