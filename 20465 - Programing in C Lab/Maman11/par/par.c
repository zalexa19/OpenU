/*AlexZ/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 100 /*Max size of a line*/
#define EMPTY -1 /*Represents an empty stack*/


void printMyString(char line[], int length);
void invalidCharFound (char str[], int length, int invChar, int lineNumber);

/*This program receives an output file from commentsRemover and checks that all of
the brackets are balanced.
To do so, I used a stack for ()[], and a simple counter for {}.

At first I check the first character received. if it's EOF, scan is complete.
Otherwise, I store it in the str[] array and continue reading the line until \n.

Then, I go over the array and push every [ or ( I see into the stack. for '{', counter is increased.
for every ')' or ']' I check the stack. If it's empty or doesn't have the right sign,
I mark the line as invalid.
If the stack holds the right sign, I pop it out of the stack (decrease the stack counter).
for each '}' I decrease the corresponding counter.

Once Im done going over the line, I check the stack counter (stackTop). If it's not empty,
Then the line is invalid.

After EOF recieved, I check the counter of {}. If it's different than 0, means 
That there either one sign is missing, or there is an extra one

*/

void printString(char str[], int length);

int main(){
	int character; /*Int that holds that character*/
	int lineNumber=0; /*Counts number of lines*/
	char str[MAXLINE]; /*array that stores a line of code*/
	int validLine=1; /*Line is considered valid until invalid char is found*/
	int curlyBracketsCounter=0; /*counts number of curly brackets*/ 
	int lineLength;
	int i;
	printf("\nValidating file:\n\n");


	/*starting to read the file*/
	while ((character=getchar()) != EOF){
		char stack[MAXLINE]; /*stack to hold the brackets*/
		int stackTop=EMPTY;
		lineNumber++;
		lineLength=0;
		validLine=1;
		i=0;

		if (character=='\n'){
			lineNumber++;
		}

		str[i]=character; /*Storing the first char*/
		lineLength++;
		i++;

		character=getchar(); /*read next char*/
		while (character != '\n'){
			str[i]=character;
			character=getchar();
			i++;
			lineLength++;
		}
		str[i]=character;


		/*validate characters*/
		for (i=0; i<lineLength; i++){
			character=str[i];


			if (character=='{' && str[i+1]=='\n'){
				curlyBracketsCounter++;
			}

			if (character=='}' && str[i+1]=='\n'){
				curlyBracketsCounter--;
			}

			if (validLine==1 && (character=='[' || character=='(')){
				stackTop++;
				stack[stackTop]=character;
			}

			if (validLine==1 && character==')'){
				if (stackTop==EMPTY || stack[stackTop] != '('){
					validLine=0;
					invalidCharFound(str,lineLength,character,lineNumber);

				}
				else{
					stackTop--;
				}
			}

			if (validLine==1 && character==']'){
				if (stackTop==EMPTY || stack[stackTop] != '['){
					validLine=0;
					invalidCharFound(str,lineLength,character,lineNumber);
				} else {
					stackTop--;
				}
			}

		}

		if (validLine==1 && stackTop != EMPTY){
			validLine=0;
			printf("Line %d is invalid - Missing closing brackets for %c\n",lineNumber,stack[stackTop] );
			printString(str,lineLength);
		}

		if(validLine==1){
			printf("line %d is valid\n",lineNumber );
		} 

	}

	if (curlyBracketsCounter !=0){
		printf("Curly Brackets are not balanced: ");
		if(curlyBracketsCounter>0){
			printf("Missing closing bracket\n");
		}else {
			printf("missing openning bracket\n");
		}
	}

	printf("Done\n");

	return 0;
}

/*This method simply prints the line by going over the str[].
It receives the str[], and the length of the line*/
void printString (char str[], int length){
	int i;

	for (i=0; i<length; i++){
		printf("%c", str[i]);
	}
	printf("\n" );
}
/*This method prints in which line an invalid character was found.
it receives the line (str[]), the length of it, the sign and in which line*/
void invalidCharFound (char str[], int length, int invChar, int lineNumber){
	printf("Line %d is invalid. Unexpected char received: '%c'.\n", lineNumber,invChar);
	printString(str,length);
}
