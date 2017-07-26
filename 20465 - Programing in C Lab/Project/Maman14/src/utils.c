/*
 * utils.c
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#include "utils.h"



String allocate_mem_string (int size){
	char* str = (char*)malloc (size * sizeof(char));
	if (!str){
		/*
		 * PRINT TO LOG
		 */
	}
	return str;
}
