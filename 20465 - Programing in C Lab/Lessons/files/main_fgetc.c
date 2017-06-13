#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *fd; /*it's always fd*/
  int ch;
  fpos_t p1;
  long d1;
  char buf[100];

  if (! (fd = fopen("mytext.txt","r+")) ){ /*Open file check if null. open for read and write*/
    fprintf(stderr, "cannot open file\n" );/*file printf for writing into files*/
    exit(0);
  }

/* read the file char by char and print each char and it's ascii
*/
  while ( ! feof(fd)){ /* feof goes to the struct fd and returns the end of file flag - 0 or 1. do, while eof = 0*/
    ch=fgetc(fd); /*go to the struct and get the next ch*/
    printf( "%c:ascii %d\n", ch,ch);

  }

  rewind(fd); /*returns fd to the beginning of the file*/

   puts("\n----------------------------------------------"); /*puts automatically does \n*/

/*advancing, until we reach the first char of the second line*/
   while ( (ch=fgetc(fd)) != '\n'){
     ;
   }

   fgetpos(fd,&p1); /* requires fpos_t*/

/*This one prints the second line and advances the pointer to the start of the third
line*/
   do {
     ch=fgetc(fd);
     putchar(ch);
   }while (ch!='\n');

/*here, we use the fsetpo to set the poisition in the file to be the second line again*/
   fsetpos(fd,&p1);

     do {
        ch=fgetc(fd);
        putchar(ch);
      }while (ch!='\n');

 puts("\n----------------------------------------------");
 d1 = ftell(fd); /*distance from start of file to current position in bytes*/
 rewind(fd);

 /*prints 2 chars from the first line*/
 ch=fgetc(fd);
 putchar(ch);
 ch=fgetc(fd);
 putchar(ch);

 puts("\n----------------------------------------------");
 fseek(fd,d1,SEEK_SET); /*jump to a specific place. negative - jumping back.*/

 puts("\n----------------------------------------------");
 rewind(fd);
 fgets(buf,96,fd);
 puts(buf); /*prints the first line*/
 puts("\n----------------------------------------------");
fseek(fd,0,SEEK_END); /*jumps to 0 bytes from the end of file = eof*/
fputs(buf,fd); /*writes another line into fd -> the forth line*/
rewind(fd);

/*print the file*/
puts("\nThe new file:");

while (!feof(fd)){
  putchar (ch= fgetc(fd));
  puts("\n----------------------------------------------");
  puts("\n**END**");
}

fclose(fd);

}



  printf("\n" );
  return 0;
}
