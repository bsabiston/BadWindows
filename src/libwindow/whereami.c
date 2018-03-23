#include <stdio.h>
#include <math.h>


/* whereami(name) 
   give it argv[0] from your main(), it will return the full directory pathname.
   ie., if your program is /u/joe/a.out and argv[0] = a.out, it will return /u/joe/
*/


whereami(arg0,name)
char arg0[], *name[];
{
  FILE *fp;
  char command[200];

  sprintf(command,"which %s > /tmp/badwdelete",arg0);
  system(command);
  fp = fopen("/tmp/badwdelete","r");
  fscanf(fp,"%s",name);
  fclose(fp);
  system("rm /tmp/badwdelete");
  Subext(name,arg0);
  return;
}

