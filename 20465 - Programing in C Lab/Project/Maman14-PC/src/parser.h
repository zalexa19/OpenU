/*
 * parser.h
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "utils.h"


/*
 * Input: A reference to a file
 * Output: an array of structs
 *
 * This function receives a file reference, converts each read line into a struct
 * and eventually returning an array of structs
 */

bodyArray parse_file (FILE *fp, int *);

/*
 * This function converts a string (one line) into a struct
 * Input: an array of chars
 * Output: a struct of the line
 *
 */


body parse_line (String str);

char * get_label (char * line);

char * extract_instruction(char *);

String extract_label (String line);

String remove_first_spaces(String  str);

int count_spaces (String str);

String extract_operation(String str);

String extract_operand (String str);

Bool check_empty_line(String str);


#endif /* PARSER_H_ */
