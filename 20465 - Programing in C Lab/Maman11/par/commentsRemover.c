/*AlexZ
This program was coppied from the book, page 165. It removes all the comments from the input program.
*/
#include <stdio.h>

enum status {OUT,IN_STRING,LEFT_SLASH,IN_COMMENT,RIGHT_STAR,IN_CPP_COM};

void main(void)
{
	int c;
	int state=OUT;

	while ((c=getchar()) !=EOF)
	{

		switch(state){
			case OUT:
				if (c=='/'){
					state=LEFT_SLASH;
				}
				else{
					putchar(c);
					if (c=='\"'){
						state=IN_STRING;
					}
				}
					break;

			case LEFT_SLASH:
				if(c=='*'){
					state=IN_COMMENT;
				}
				else if (c=='/'){
					state=IN_CPP_COM;
				}
				else {
					putchar('/');
					putchar(c);
					state=OUT;
				}

				break;

			case IN_COMMENT:
				if(c=='*'){
					state=RIGHT_STAR;
				}

				break;

			case IN_CPP_COM:
				if (c=='\n'){
					state=OUT;
					putchar('\n');
				}

				break;

			case RIGHT_STAR:
				if (c=='/'){
					state=OUT;
				}
				else if ( c!='*'){
					state=IN_COMMENT;
				}
				break;

			case IN_STRING:
				if (c=='\"'){
					state=OUT;
					putchar(c);
				}
			break;
		}
	}
}
