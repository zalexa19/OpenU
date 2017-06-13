/*
 ============================================================================
 Name        : Maman12
 Author      : Alex Zablotsky, 314494964
 Version     :
 Copyright   : Your copyright notice
 Description : This is Question #2: Implementation of a double linked list.

 Each node is a struct, which consists of an array in the size of 10, a counter (which
 holds the number of the last populated cell) and two pointers: previous node and next node.

 main:
Main has two pointers: head and tail of the list. Both are null at the beginning.

 addToList:
 Receives a reference to the head of the list, tails of the list and the new character.
 When adding a new char to the array:
 - Check if the list is empty
 	 - If so, create a new node, add the char into the chars array, make head and tail
 	   pointers to point to the new node
     - Otherwise, check the tail's counter. if there's free space in the array,
       add the char.
       	   - Otherwise, create a new node, insert the char into index 0, make the tail->
       	     to point to the new node, the new node->prev to point to the tail, and then
       	     make the new node as the new tail


 printList:
 Receives the head of the list (a copy).
 Prints the whole array char by char. Once done, we do the same for the next node.
 Function stops printing when head becomes NULL.

 freeList:
 Receives a pointer to first node in the list.
 A temporary pointer points to the head of the list.
 The head pointer then points to the next in the link, so we can safely free the first
 node in the list, which the temp pointer is pointing to.
 Doing the same for each node until head points to NULL and then we know that the list is empty.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 10
typedef struct node * nodeRef; /*Pointer to the struct*/
typedef struct node{
	int counter;
	int charArray[ARRAYSIZE];
	nodeRef next;
	nodeRef prev;
}item; /*Represents a node*/

void addToList(nodeRef *,nodeRef *, int);
void printList (nodeRef);
void freeList(nodeRef *);


int main() {
	int inputChar;
	nodeRef listHead=NULL; /*Pointer to the head of the list*/
	nodeRef listTail=listHead;/*Pointer to the tail of the list*/

	printf("Please enter your input. Stop with EOF\n");

	while ((inputChar=getchar()) != EOF ){
		addToList(&listHead,&listTail,inputChar);
	}

	printf("Your input was:\n");

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

	while (head != NULL){
		int i=0;
		int arrayInd=head->counter;

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

