/*
 * linkedlist.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */
#include "utils.h"

typedef struct node * node_ref;
typedef struct node{
	String label;
	String address;
	Bool external;


	node_ref next;
	node_ref previous;

}item;
