/*fread() and fwrite()*/
#include <stdio.h>
#include <stdlib.h>

void main(){
  FILE *fd1, *fd2;
  int buf[5]={250,-25,780,4680,12};
  int buf2[100], buf3[100];
  int i,n_read;

  /*saves the numbers as text*/
  if (! (fd1=fopen("numbers1.txt", "w"))){ /*create new file for text writing*/
    fprintf(stderr, "cannot create file\n");
    exit(0);
  }

  /*saves as a binary*/
  if (! (fd2=fopen("numbers2.txt","wb"))){ /*creates new file a bit writing*/
    fprintf(stderr, "cannot create file\n" );
    exit(0);
  }

  for (i=0; i<5; i++){
    fprintf(fd1, "%d\n",buf[i]);/*writes from buf to the fd1 file§*/
  }

  fwrite(buf,sizeof(int), 5,fd2); /*does the same into fd2 only without the loop*/

  fclose(fd1);
  fclose(fd2);

  puts("\n-----------------------------");


  if (! (fd1=fopen("numbers1.txt","r") ))
  {
    fprintf(stderr, "cannot open file\n" );
    exit(0);
  }

  if (! (fd2=fopen("numbers2.txt","rb"))){
    fprintf(stderr, "cannot open file\n" );
    exit(0);
  }

  for (i=0;i<5;i++){ /*read from fd1, a number with \n(to skip), put it in buf2*/
    fscanf(fd1,"%d\n",&buf2[i]);
    printf("%d\n",buf[i]);

  }

  n_read=fread(buf3,sizeof(int),5,fd2); /*reads from the binary file, returns how many were successful*/

  for (i=0;i<n_read; i++){
    printf("%d\n",buf3[i]);
  }

  fclose(fd1);
  fclose(fd2);

}
