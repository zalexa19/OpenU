#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*points to lines_list struct*/
typedef struct lines_list * lnode_ptr;

/*linked list of the line numbers in which the word appears*/
typedef struct lines_list{
  int line_number;
  lnode_ptr next;
}lnode;

/*Represents a node in the binary tree*/
typedef struct tree_node * tnode_ptr;

typedef struct tree_node {
  char * word;
  int * number_of_appearances;
  tnode_ptr left;
  tnode_ptr right;
  lnode_ptr list_head;
}tnode;


void add_to_tree(tnode_ptr root, char * word, int * number_of_appearances);
tnode_ptr search_in_tree(char * word, tnode_ptr);
