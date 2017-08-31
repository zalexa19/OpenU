/*
 * constants.h
 *
 *  Created on: Aug 17, 2017
 *      Author: alexz
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define DATA "data"

#define STR "string"
#define MAT "mat"
#define ENTRY "entry"
#define NONE NOMATCH
#define EXTERN "extern"

#define MOV "mov"
#define CMP "cmp"
#define ADD "add"
#define SUB "sub"
#define LEA "lea"

#define NOT "not"
#define CLR "clr"
#define INC "inc"
#define DEC "dec"
#define JMP "jmp"
#define BNE "bne"
#define RED "red"
#define PRN "prn"
#define JSR "jsr"

#define RTS "rts"
#define STOP "stop"

#define R0 "r0"
#define R1 "r1"
#define R2 "r2"
#define R3 "r3"
#define R4 "r4"
#define R5 "r5"
#define R6 "r6"
#define R7 "r7"



typedef enum {
	INTERMID=0,
	LABLE=1,
	MATRIX=2,
	REGISTER=3,
	UNRECOGNIZED=-1

} Operand_type;









#endif /* CONSTANTS_H_ */
