#include "utils.h"
#include <ctype.h>
#include "validator.h"


#define MAXLABELSIZE 30
#define MAXERRORSIZE 200
#define NOMATCH "none"
#define TERMINATOR "\0"
#define MATRIXCOLANDROW 2
#define NUMOFBRACKETS 2


/*Macro that adds a log*/
#define INVALIDINPUT fprintf(stderr, "Invalid input: ");
/*
 * Macro for printing
 */
#define PRINT_PASSED_OR_FAILED \
{\
			if (item.valid==TRUE){\
			printf(KGREEN "PASSED\n");\
		} else {\
			printf(KRED "FAILED\n");\
		}\
		NORMALCOLOR\
}


void validate_file(bodyArray parsed, int array_size){
	int i;
	body item;
	list_item_reference error_list_head;
	char error[MAXERRORSIZE];


	printf(KYELLOW"------------------------------\n");
    printf("      VALIDATION STAGE:        \n");
	printf("------------------------------\n");


	NORMALCOLOR

	i=0;
	item=parsed[i];
	error_list_head=NULL;


	if(strcmp(item.label,"\0") != 0){
		/*VALIDATE LABEL*/
		validate_label(&item,&error_list_head);


		printf(BOLDWHITE"Label validation:\nFile is: ");
		PRINT_PASSED_OR_FAILED
	}

	if(strcmp(item.instruction,"\0") != 0){
		/***********************
		 * VALIDATE INSTRUCTION*
		 ***********************/

		validate_instruction(&item,&error_list_head);

		printf("Instruction validation:\nFile is: ");
		PRINT_PASSED_OR_FAILED


		/*DATA*/
		if (strcmp(item.instruction,"data")==0){
			validate_ins_data(&item, &error_list_head);

			NORMALCOLOR

			printf(BOLDWHITE "data operands validation: ");
			PRINT_PASSED_OR_FAILED
		}

		printf(".string operands validation: \n");

		if (strcmp(item.instruction,"string")==0){
			validate_ins_string(&item,&error_list_head);
		}


		printf(BOLDWHITE "string operands validation: ");

		PRINT_PASSED_OR_FAILED

		/*MAT*/
		printf("mat validation:\n");
		if (strcmp(item.instruction,"mat")==0){
			validate_ins_mat(&item,&error_list_head);

			printf(BOLDWHITE "mat operands validation: ");
			PRINT_PASSED_OR_FAILED
		}


		/*ENTRY*/
		if (strcmp(item.instruction,"entry")==0){
			validate_ins_entry(&item,&error_list_head,error);

		}

		printf(BOLDWHITE "entry operands validation: ");
		PRINT_PASSED_OR_FAILED

		/*EXTERN*/
		if (strcmp(item.instruction,"extern")==0){
			validate_ins_extern(&item,&error_list_head,error);
		}

		printf(BOLDWHITE "extern operands validation: ");
		PRINT_PASSED_OR_FAILED

	}	else {
		/*
		 * Validate the operation
		 */

	if (strcmp(item.operantion,"\0")==0){
		item.valid=FALSE;
		sprintf(error,"22. Error in line: %d: Operation/Instruction were not received.\n",item.line_number);
		add_to_list(&error_list_head,error);
	} else {

		validate_operation(&item,&error_list_head,error);

		printf(BOLDWHITE "Operational command validation: ");
		PRINT_PASSED_OR_FAILED

		validate_oper_operands(&item,&error_list_head,error);

		printf(BOLDWHITE "Operation-Operands command validation: ");
		PRINT_PASSED_OR_FAILED
	}



	/*end of operation validation*/
	}

	printf("finished validating file\n");

	printf(KYELLOW "------------------------------\n");
    printf("      ERRORS:        \n");
	printf("------------------------------\n");

	print_list(error_list_head);
	NORMALCOLOR



}



Bool validate_label (body* item, list_item_reference*  head){
	String label;
	int line_number;
	char error[MAXERRORSIZE];
	int length;
	int size;
	int i;
	char c;
	Bool valid_letter;
	Bool is_a_num;
	Bool valid_label=TRUE;


	label=item->label;
	line_number=item->line_number;


	/*validating label length*/
	length=strlen(label);
	if (length > MAXLABELSIZE){
		sprintf(error,"1. Error in line %d: Label <%s> is too long.\n",line_number,label);
		add_to_list(head,error);
		item->valid=FALSE;
		valid_label=FALSE;

	}



	/*validate the first char*/
	i=0;
	c=label[i];
	valid_letter=is_valid_letter(c);

	if (valid_letter==FALSE){
		item->valid=FALSE;
		sprintf(error,"2. Error in line %d: Label <%s> doesn't start with a letter (%c).\n",line_number,label,c);
		add_to_list(head,error);
		valid_label=FALSE;
	}
	i++;


	/*validating each char in the string, starting from cell #1:*/
	size=strlen(label);
	while (i<size){
		c=label[i];
		valid_letter=is_valid_letter(c);
		if (valid_letter==FALSE){
			/*not a letter*/
			is_a_num=is_valid_number(c);

			if (is_a_num==FALSE){
				item->valid=FALSE;

				printf("weird character\n");
				sprintf(error,"3. Error found in line %d: invalid char <%c> found in label <%s>.\n",line_number,c,label);
				add_to_list(head,error);
				valid_label=FALSE;
			}

		}

		i++;
	}

	/*validating that the label is not a saved word*/
	printf("label is a special word: %s\n",find_command_name(label));

	if (strcmp("none",find_command_name(label)) != 0){
		item->valid=FALSE;
		sprintf(error,"4. Error found in line %d: label <%s> is a preserved word.\n",line_number,label);
		add_to_list(head,error);
		valid_label=FALSE;
	}

	return valid_label;
}

void validate_instruction(body* item, list_item_reference*  head){
	int line=item->line_number;
	String inst_value= item->instruction;
	char error[MAXERRORSIZE];

	/*Check if instruction is all lower case*/
	if (is_string_lowercase(inst_value)==FALSE){
		item->valid=FALSE;
		sprintf(error,"5. Error in line %d: Instruction value <%s> has non-lowecase chars.\n",line,inst_value);
		add_to_list(head,error);
	}

	/*check if instruction is a valid command*/

	if (strcmp(NOMATCH,find_command_name(item->instruction))==0){
		item->valid=FALSE;
		sprintf(error,"6. Error in line %d: Instruction value <%s> is unrecognized.\n",line,inst_value);
		add_to_list(head,error);
	}

}

void validate_operation(body* item, list_item_reference*  head, String error){
	String value;
	int line;

	line=item->line_number;
	value=item->operantion;


	if (is_operational_command(value)==FALSE){
		item->valid=FALSE;
		sprintf(error,"28. Error in line %d: Operational value <%s> is unrecognized.\n",line,value);
		add_to_list(head,error);
	}


}

/*This function validates that the operands are valid numbers*/
void validate_ins_data (body* item, list_item_reference*  head){
	int num_of_operands;
	int line;
	Bool invalid_char_found=FALSE;
	int counter;
	String current;
	char c;
	int str_length;
	int i;
	char error[MAXERRORSIZE];

	num_of_operands=item->data_values_number;
	line=item->line_number;


	if (item->data_values_number==0){
		item->valid=FALSE;
		sprintf(error,"8. Error in line %d: No operands received for .data.\n",line);
		add_to_list(head,error);
	}


	/*check if each string has valid numbers*/
	for(counter=0;counter<num_of_operands;counter++){
/*		printf(KMAGENTA "working on: %s\n",item->data_string_array[counter]);*/

		current=item->data_string_array[counter];
		str_length=strlen(current);

	/*first char is a symbol - or +*/
		/*i=0;
		if (current[i]=='-' || current[i]=='+'){
			i++;
		}




		while (i<str_length){
			c=current[i];
			if(is_valid_number(c) ==FALSE){
				invalid_char_found=TRUE;
			}
			i++;
		}*/

		if (is_valid_number(current)==FALSE){

			item->valid=FALSE;
			sprintf(error,"7. Error in line %d: non-numbers received in %s, for command %s.\n",line,current,item->instruction);
			add_to_list(head,error);
			return;
		}

	}


	/*If we reached here, it means that we have valid numbers*/
	if((item->data_int_values=(int*)malloc(sizeof(int)*num_of_operands)) == NULL){
		fprintf(stderr,"Unable to allocate memory to data_int_values. Continuing\n");
	}


	for (counter=0;counter<num_of_operands;counter++){
		item->data_int_values[counter]=atoi(item->data_string_array[counter]);
/*		printf("current cell: %s, extracted number: %d\n",item->data_string_array[counter],item->data_int_values[counter]);*/
	}

	free(item->data_string_array);


	/*validate other*/

}


void validate_ins_string (body* item, list_item_reference*  head){
	char error[MAXERRORSIZE];
	String temp;
	int length;
	String pointer;

	/*checks that the string was received with ""*/


	/*checks if enough operands were received*/
	if ((strcmp(item->operand2,TERMINATOR))!=0){
		item->valid=FALSE;

		sprintf(error,"10. Error in line %d: Excess operand for .string: <%s>.\n",item->line_number,item->operand2);
		add_to_list(head,error);
	}

	if ((strcmp(item->operand3,TERMINATOR))!=0){
		item->valid=FALSE;
		sprintf(error,"11. Error in line %d: Excess operand for .string: <%s>.\n",item->line_number,item->operand3);
		add_to_list(head,error);
	}

	if ((strcmp(item->operand1,TERMINATOR))==0){
		item->valid=FALSE;
		sprintf(error,"9. Error in line %d: Missing operands for .string.\n",item->line_number);
		add_to_list(head,error);
		return;
	}


	if (item->operand1[strlen(item->operand1)]!='\0'){
		item->valid=FALSE;
		sprintf(error,"12. Error in line %d: .string <%s> is not closed with a turminating char.\n",item->line_number,item->operand1);
		add_to_list(head,error);
	}

	if(item->valid==TRUE){
		pointer=item->operand1;
		length=strlen(pointer);

		if (pointer[length-length]!= '"'){
			item->valid=FALSE;
			sprintf(error,"13. Error in line %d: .string <%s> is missing opening <\">.\n",item->line_number,item->operand1);
			add_to_list(head,error);
		}else{
			printf("advanced the pointer\n");
			pointer++;
			length--;
		}
		if (pointer[length-1] != '"'){
			item->valid=FALSE;
			sprintf(error,"14. Error in line %d: .string <%s> is missing closing <\">.\n",item->line_number,item->operand1);
			add_to_list(head,error);
		}else{

			length--;

		}

		temp=allocate_mem_string(length);

		strncy_safe(temp,pointer,length);

		free(item->operand1);
		item->operand1=allocate_mem_string(length+1);

		strcpy(item->operand1,temp);

		free(temp);

	}



}

/*
 * 1.Removes all spaces. According to the forum, matrix will be recieved without unexpected spaces
 * 2.check that operand1 includes valid numbers
 * 3. Put the valid numbers in a special array
 * 4. check that the other values recieved also includes valid numbers
 */
void validate_ins_mat(body* item, list_item_reference*  head){
	Bool is_number=TRUE; /*This bool is used to determine if we encounter a space between digits*/
	String orig;
	String fixed_operand;
	String ptr;
	String col;
	String row;
	int size;
	char error[MAXERRORSIZE];
	int opening_bracket;
	int closing_bracket;
	int i,j;
	int letter_counter;
	int length;
	int c;
	int line;


	printf(BOLDMAGENTA "Starting validation on mat operands: <%s>\n",item->operand1);

	NORMALCOLOR;

	/*Removing spaces*/
	opening_bracket=0;
	closing_bracket=0;
	orig=item->operand1;
	line=item->line_number;
	length=strlen(orig);
	letter_counter=0;
	i=0;

	while (i<length){
		c=orig[i];
		if (is_white_char(c) == FALSE){
			letter_counter++;

		}
		i++;
	}

	printf("counter %d letters \n",letter_counter);
	fixed_operand=allocate_mem_string(letter_counter+1);

	/*copy into fixed without spaces*/
	i=0;
	j=0;

	while (i<length){

		c=orig[i];
		if (is_white_char(c) == FALSE){
			fixed_operand[j]=c;
			j++;

			if (c=='['){
				opening_bracket++;
			} else if (c==']'){
				closing_bracket++;
			}


		}

		printf("%c",fixed_operand[j]);
		i++;
	}
	fixed_operand[j]='\0';

	printf("fixed: <%s>\n",fixed_operand);

	/*begin validation*/

	if (fixed_operand[letter_counter-letter_counter] != '['){
		item->valid=FALSE;
		sprintf(error,"Error 15 found in line %d:operand: %s doesn't start with [.\n",line,fixed_operand);
		add_to_list(head,error);
	}

	if (fixed_operand[letter_counter-1] != ']'){
		item->valid=FALSE;
		sprintf(error,"Error 16 found in line %d:operand: %s doesn't end with ].\n",line,fixed_operand);
		add_to_list(head,error);
	}


	if (opening_bracket !=NUMOFBRACKETS){
		item->valid=FALSE;
		sprintf(error,"Error 17 found in line %d: invalid number of '[' for operand: %s.\n",line,fixed_operand);
		add_to_list(head,error);
	}

	if (closing_bracket != NUMOFBRACKETS){
		item->valid=FALSE;
		sprintf(error,"Error 18 found in line %d: invalid number of ']' for operand: %s.\n",line,fixed_operand);
		add_to_list(head,error);
	}

	else {

		/*string is of form [][]*/
		orig=fixed_operand;
		orig+=1;

		/*copy the first [value] to a seperated string*/
		ptr=strchr(orig,']');
		size=CALCSIZE(orig,ptr);
		col=allocate_mem_string(size);

		strncy_safe(col,orig,size);

		for (j=0;j<size;j++){
			if (is_valid_number(col[j])==FALSE){
				is_number=FALSE;
			}
		}


		orig+=size;
		i=0;

		if (is_number==TRUE){
			/*allocate memory*/
			if (! (item->mat_size=(int*)malloc(sizeof(int)*MATRIXCOLANDROW))  ){
				fprintf(stderr,"Unable to allocate memory to mat_size\n.");
			}

			item->mat_size[i]=extract_number(col);
			orig+=size;
			i++;
		}else {
			item->valid=FALSE;
				sprintf(error,"Error 19 found in line %d: operand: %s is not a number\n",line,fixed_operand);
				add_to_list(head,error);
			}

		is_number=TRUE; /*reseting to check the other operand*/


		/*extract row*/
		ptr=strchr(orig,']');
		size=CALCSIZE(orig,ptr);
		row=allocate_mem_string(size);
		strncy_safe(row,orig,size);
		orig+=size;

		for (j=0;j<size;j++){
			if (is_valid_number(col[j])==FALSE){
				is_number=FALSE;
			}
		}

		if (is_number==TRUE){
			/*allocate memory*/
			item->mat_size[i]=extract_number(row);
		}else {
			item->valid=FALSE;
				sprintf(error,"Error 20 found in line %d: operand: %s is not a number\n",line,fixed_operand);
				add_to_list(head,error);
		}


		printf("in my matrix: col: %d, row: %d\n",item->mat_size[0],item->mat_size[1]);
		/*Checking the other operand*/

	}
}

void validate_ins_entry(body* item, list_item_reference*  head, char * error){
	int line;

	line=item->line_number;


/* unreachable
	if (is_string_lowercase(item->operantion)==FALSE){
		item->valid=FALSE;
		sprintf(error,"24. Error in line %d: .entry command is not written in lowercase: %s .\n",line,item->operantion);
		add_to_list(head,error);
	}
*/



	if (strcmp(item->label,TERMINATOR)!=0){
		sprintf(error,"Attention to line %d: label '%s' received for .entry command will be ignored.\n",line,item->label);
		add_to_list(head,error);
	}

	if (strcmp(item->operand1,TERMINATOR)==0){
		item->valid=FALSE;
		sprintf(error,"22. Error in line %d: Missing statement for .entry command .\n",line);
		add_to_list(head,error);

	}

	if (strcmp(item->operand2,TERMINATOR)!=0 ||strcmp(item->operand3,TERMINATOR)!=0 ){
		item->valid=FALSE;
		sprintf(error,"23. Error in line %d: Too much data received for .entry command: %s %s .\n",line,item->operand2,item->operand3);
		add_to_list(head,error);
	}



}

void validate_ins_extern(body* item, list_item_reference*  head,String error){

	int line;

	line=item->line_number;


/* unreachable
	if (is_string_lowercase(item->operantion)==FALSE){
		item->valid=FALSE;
		sprintf(error,"24. Error in line %d: .extern command is not written in lowercase: %s .\n",line,item->operantion);
		add_to_list(head,error);
	}
*/



	if (strcmp(item->label,TERMINATOR)!=0){
		sprintf(error,"Attention to line %d: label '%s' received for .extern command will be ignored.\n",line,item->label);
		add_to_list(head,error);
	}

	if (strcmp(item->operand1,TERMINATOR)==0){
		item->valid=FALSE;
		sprintf(error,"24. Error in line %d: Missing statement for .extern command .\n",line);
		add_to_list(head,error);

	}

	if (strcmp(item->operand2,TERMINATOR)!=0 ||strcmp(item->operand3,TERMINATOR)!=0 ){
		item->valid=FALSE;
		sprintf(error,"25. Error in line %d: Too much data received for .extern command: %s %s .\n",line,item->operand2,item->operand3);
		add_to_list(head,error);
	}




}








void validate_oper_operands (body* item, list_item_reference*  head, String error){
	String commant;
	int operand_type;

	commant=item->operantion;

	if (is_operational_command(item->operantion)==FALSE){
		return;
	}


	operand_type=get_operand_type(item->operand1,head,error);


	/*check if a valid number of perands was received*/
	/*check if each operand is a valid form*/
	/*check if the operand form matches the operational command*/



}


Bool is_valid_letter(char c){

	if ( ('a'<=c && c<= 'z') || ('A'<=c && c<= 'Z')){
		return TRUE;
	}

	return FALSE;


}

Bool is_white_char (char c){
	if (c==' ' || c=='\t' || c=='\n' || c=='\0'){
		return TRUE;
	}
	return FALSE;
}




Bool is_lowcase(char c){
	if ('a'<=c && c<='z'){
			return TRUE;
	}

	return FALSE;
}

Bool is_string_lowercase(String str){
	int length = strlen(str);
	Bool lowercase=TRUE;
	int i;
	char c;
	i=0;

	c=str[i];
	while(i<length && lowercase==TRUE){
		if(is_lowcase(c)==FALSE){
			lowercase=FALSE;

		}

		i++;
		c=str[i];
	}

	return lowercase;
}


Bool is_valid_number (String str){
	int str_length,i;
	char c;



	i=0;
	str_length=strlen(str);

	if (str_length==0){
		return FALSE;
	}



	if (str[i]=='-' || str[i]=='+'){
		if (str_length==1){
			return FALSE;
		}

		i++;
	}



	while (i<str_length){
		if (isdigit(c)==FALSE){
			return FALSE;
		}
		i++;
	}

	return TRUE;
}

int extract_number (String str){
	int result;

	result=atoi(str);

	if (!result){
		fprintf(stderr,"unable to parse into from string %s\n.",str);
	}
	return result;
}







String find_command_name(String key){
	String data="data";
	String str="string";
	String mat="mat";
	String entry="entry";
	String none=NOMATCH;
	String external="external";

	String mov="mov";
	String cmp="cmp";
	String add="add";
	String sub="sub";
	String lea="lea";

	String not="not";
	String clr="clr";
	String inc="inc";
	String dec="dec";
	String jmp="jmp";
	String bne="bne";
	String red="red";
	String prn="prn";
	String jsr="jsr";

	String rts="rts";
	String stop="stop";

	if (strcmp(key,data)==0){
		return data;
	}
	if (strcmp(key,str)==0){
		return str;
	}
	if (strcmp(key,mat)==0){
		return mat;
	}
	if (strcmp(key,entry)==0){
		return entry;
	}
	if (strcmp(key,external)==0){
		return external;
	}



	if (strcmp(key,mov)==0){
		return mov;
	}

	if (strcmp(key,cmp)==0){
		return cmp;
	}

	if (strcmp(key,add)==0){
		return add;
	}

	if (strcmp(key,sub)==0){
		return sub;
	}

	if (strcmp(key,lea)==0){
		return lea;
	}


	if (strcmp(key,not)==0){
		return not;
	}
	if (strcmp(key,clr)==0){
		return clr;
	}

	if (strcmp(key,inc)==0){
		return inc;
	}

	if (strcmp(key,dec)==0){
		return dec;
	}

	if (strcmp(key,jmp)==0){
		return jmp;
	}

	if (strcmp(key,bne)==0){
		return bne;
	}

	if (strcmp(key,red)==0){
		return red;
	}

	if (strcmp(key,prn)==0){
		return prn;
	}

	if (strcmp(key,jsr)==0){
		return jsr;

	}

	if (strcmp(key,rts)==0){
		return rts;
	}

	if (strcmp(key,stop)==0){
		return stop;
	}

	return none;

}

Bool is_operational_command(String str){

	if (strcmp(str,MOV)==0){
		return TRUE;
	}

	if (strcmp(str,CMP)==0){
		return TRUE;
	}

	if (strcmp(str,ADD)==0){
		return TRUE;
	}

	if (strcmp(str,SUB)==0){
		return TRUE;
	}

	if (strcmp(str,NOT)==0){
		return TRUE;
	}

	if (strcmp(str,CLR)==0){
		return TRUE;
	}

	if (strcmp(str,LEA)==0){
		return TRUE;
	}

	if (strcmp(str,INC)==0){
		return TRUE;
	}

	if (strcmp(str,DEC)==0){
		return TRUE;
	}

	if (strcmp(str,JMP)==0){
		return TRUE;
	}

	if (strcmp(str,BNE)==0){
		return TRUE;
	}

	if (strcmp(str,RED)==0){
		return TRUE;
	}
	if (strcmp(str,PRN)==0){
			return TRUE;
	}

	if (strcmp(str,JSR)==0){
			return TRUE;
	}

	if (strcmp(str,RTS)==0){
			return TRUE;
	}

	if (strcmp(str,STOP)==0){
			return TRUE;
	}

	return FALSE;

}

Operand_type get_operand_type (String operand, list_item_reference * head, String error){
	Operand_type result;
	int operand_type;
	int i;
	int length;
	String t1,t2;

	printf("Getting the operands for operational\n");
	length=strlen(operand);
	i=0;

	if (operand[i]=='#'){

		if (is_valid_number(operand+1)==TRUE){
			return INTERMID;
		}

	}

	if (validate_label(operand,head)==TRUE){
		return LABLE;
	}








	return UNRECOGNIZED;

}
