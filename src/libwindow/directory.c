#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

struct Window *DirectoryWin;
/* c1...base color
   b1...internal mat color
   t1...normal text color
   h1...highlight text color */



MakeDirectoryLoader(Root, echo, font, size, x, y, c1, c2, c3, b1, b2, b3, t1, t2, t3, h1, h2, h3)     /* v 1.0b */
     struct Window *Root;
     struct curstruct *echo;
     int x, y, size, c1, c2, c3, b1, b2, b3, t1, t2, t3, h1, h2, h3;
     char *font;
{
  DirectoryWin = (struct Window *)MakeScroller(Root->display, Root->input, Root, echo, font, size, x, y,
					       c1, c2, c3, b1, b2, b3,
					       t1, t2, t3, h1, h2, h3);
}



GetDirectoryInfo(string, suffix, files, bases, numstrings)     /* v 1.0b */
     char *string, ***files, ***bases;
     int *numstrings;
{
  ListDirectory(string, numstrings, files, bases, suffix);
}



/* GetDirectory takes the file search command in string (like "*.midi" or "*.pix")
   the selected title will be returned in title. it will be a null string if canceled
   or typed messages selected. pass in a string to remove from the titles in suffix.
   x and y are window locations */

GetDirectory2(title, x, y, files, bases, numstrings)     /* v 1.0b */
     char *title, **files, **bases;
     int x, y, numstrings;
{
  int *commands, windows, i;

  if (numstrings == 0) return(1);
  commands = (int *)malloc((numstrings+1)*sizeof(int));

  for (i = 0; i <= numstrings; i++) *(commands+numstrings) = 0;

  PopUpScroller(DirectoryWin, "Select File to load", x, y, bases, commands, 0);

  if (*(commands+numstrings) == CANCEL) return(1);

  if (! *(commands+numstrings-1))
    for (i = 0; i < numstrings-1; i++) if (*(commands+i)) strcpy(title, *(files+i));

  free(commands);
  return(0);
}



/* WARNING: You must free the array 'commands' after checking it */

GetDirectory_Plural(rcommands, x, y, files, bases, numstrings)     /* v 1.0b */
     char **files, **bases;
     int x, y, numstrings, **rcommands;
{
  int *commands, windows, i;

  if (numstrings == 0) return(1);
  commands = (int *)malloc((numstrings+1)*sizeof(int));

  for (i = 0; i <= numstrings; i++) *(commands+numstrings) = 0;

  PopUpScroller(DirectoryWin, "Select File to load", x, y, bases, commands, 1);

  if (*(commands+numstrings) == CANCEL) return(1);

 *rcommands = commands;

/***
  if (! *(commands+numstrings-1))
  for (i = 0; i < numstrings-1; i++)
  {
  if (*(commands+i)) strcpy(title, *(files+i));
  }

  free(commands);
***/

  return(0);
}



GetDirectory(string, title, suffix, x, y)     /* v 1.0b */
     char *string, *title, *suffix;
     int x, y;
{
  int *commands, numstrings, windows, i;
  char **files, **bases;

  numstrings = 0;
  strcpy( title, "" );
  ListDirectory(string, &numstrings, &files, &bases, suffix);
  if (numstrings == 0) return(1);
  commands  = (int *)malloc((numstrings+1)*sizeof(int));

  for (i = 0; i <= numstrings; i++) *(commands+numstrings) = 0;

  PopUpScroller(DirectoryWin, "Select File to load", x, y, bases, commands, 0);

  if (*(commands+numstrings) == CANCEL)
    {
      for (i = 0; i <numstrings; i++) free(*(bases+i)), free(*(files+i));
      return(1);
    }

  if (! *(commands+numstrings-1)) {
    for (i = 0; i < numstrings-1; i++)
      if (*(commands+i)) strcpy(title, *(files+i));
  }
  else
    strcpy( title, "" );    /* "Type a filename" selected */

  for (i = 0; i <numstrings; i++) free(*(bases+i)), free(*(files+i));
  free(bases);
  free(files);
  free(commands);
  return(0);
}



ListDirectory(string, numstrings, files, bases, suffix)     /* v 1.0b */
     char *string, ***files, ***bases, *suffix;
     int *numstrings;
{
  char command[300], name[300], options[20], base[200], *CopyString();
  int n;
  FILE *fopen(), *fp;

  *numstrings = 0;
/* strcpy( options, "-1 -t -r" ); */ /* one column, time order, reverse */
  strcpy( options, "-1");            /* one column, alphabetic order    */

  sprintf(command, "ls %s %s > templist", options, string);
  system(command);

  n = 0;
  fp = fopen("templist", "r");
  while (fscanf(fp, "%s", name) != EOF) n++;
  fclose(fp);

  n++; /* for type string */
  *numstrings = n;
  *files = (char **)malloc((n+1)*sizeof(char *)); /* extra for 0 */
  *bases = (char **)malloc((n+1)*sizeof(char *));

  n = 0;
  fp = fopen("templist", "r");
  while (fscanf(fp, "%s", name) != EOF)
    {
      *(*(files)+n) = CopyString(name);
      Basename(name, suffix, base);
      *(*(bases)+n) = CopyString(base);
      n++;
    }

  *(*(files)+*numstrings-1) = CopyString("Type a filename");
  *(*(bases)+*numstrings-1) = CopyString("Type a filename");

  *(*(files)+*numstrings) = NULL;
  *(*(bases)+*numstrings) = NULL;

  fclose(fp);
  system("rm templist");
}

