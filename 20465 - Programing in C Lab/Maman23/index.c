
#include "tree.h"
#define  NAMELENGTH 100

void print_file(FILE *);

int main(){
  FILE *fd;
  FILE *outputFile;
  int i;
  char * name;
  char c;
  tnode_ptr root;
  tnode a1,a2,a3,a4;
  a1.word = "crow";
  a1.number_of_appearances=1;
  a1.left = a2;
  a.right=a3;

  a2.word="ark";
  a2.left=a4;
  a2.righ=NULL;

  a3.word="dark";
  a3.left=NULL;
  a3.right=NULL;

  a4.word="ale";
  a4.left=NULL;
  a4.right=NULL;

/*tests*/


  printf("Please insert the name of the file:\n" );
  name = (char *)malloc (sizeof(char)*NAMELENGTH);
  if (!name){
    printf("Problem with malloc\n");
    exit(0);
  }

  /*saving the name of the file*/
  i=0;
  while ( (c=getchar()) != EOF){
    if (c=='\n'){
      name[i]='\0';
    }
    else {
      name[i]=c;
      i++;
    }
  }
  /*opening the file*/

  if (! (fd=fopen(name,"r"))){
  printf("~Unable to open %s\n",name);
  }

  /*Testing the search function*/





/*
printing the name of the file
  i=0;
  while (name[i] != '\0'){
    printf("%c",name[i] );
    i++;
  }*/


  return 0;
}


/*Simply prints the output file*/
void print_file(FILE * fd){
  char c;
  printf("Current file is:\n");
  while (!feof(fd)){
    c=fgetc(fd);
    printf("%c", c);
  }
}

/*Method to validate the input*/
