/*
 ============================================================================
 Name        : Maman12.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 10
typedef struct node * nodeRef;
typedef struct node{
	int counter;
	int charArray[ARRAYSIZE];
	nodeRef next;
	nodeRef prev;
}item;

void addToList(nodeRef *,nodeRef *, int);
void printList (nodeRef);
void freeList(nodeRef *);


int main() {
	int inputChar;

	nodeRef listHead=NULL;
	nodeRef listTail=listHead;

	while ((inputChar=getchar()) != EOF ){
		addToList(&listHead,&listTail,inputChar);
	}

	printList(listHead);
	freeList(&listHead);
	listTail=listHead;




	return 0;
}

/*Function that adds a char into the list*/
/*
 * At first we check if the list is empty. When empty, we create a new node.
 * Otherwise, we check if the tails has free space in it's array. If it does, we add the char into the array
 * otherwise we create a new node;
 *
 */


void addToList (nodeRef * head, nodeRef * tail, int newChar){
	nodeRef new,temp;


	if (*head==NULL){
		new = (nodeRef)malloc(sizeof(item));
		if (!new){
			printf("Memory allocation failed. closing the program");
			exit(0);
		}

		new->counter=0;
		new->charArray[new->counter]=newChar;
		new->next=NULL;
		new->prev=NULL;

		*head=new;
		*tail=new;
	}

	else {
		temp=*tail;

		if ( (temp->counter) < ARRAYSIZE-1){
			temp->counter =(temp->counter)+1;
			temp->charArray[temp->counter]=newChar;
		}

		else{
			new = (nodeRef)malloc(sizeof(item));
			if (!new){
				printf("Memory allocation failed. closing the program");
				exit(0);
			}

			new->counter=0;
			new->charArray[new->counter]=newChar;
			temp->next=new; /*Current tail points to the new node*/
			new->prev=temp; /*New node points to the current tails as it's prev*/
			*tail=new;
		}
	}


}

void printList(nodeRef head){
	printf("Printing\n");

	while (head != NULL){
		int i=0;
		int arrayInd=head->counter;
		/*printf("\nCLast used index=%d\n",arrayInd);*/

		for (i=0;i<=arrayInd;i++){
			printf("%c",head->charArray[i]);
		}

		head=head->next;
	}
	printf("\n");
	printf("***List End***\n\n");

}

void freeList(nodeRef * node){
	nodeRef temp;

	while (*node != NULL){
		temp=*node;
		*node=(*node)->next;
		free(temp);
	}

}

