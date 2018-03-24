

/******************************************************************************
Copyright 1990 by the Massachusetts Institute of Technology.  All 
rights reserved.

Developed by the Visible Language Workshop at the Media Laboratory, MIT, 
Cambridge, Massachusetts, with support from Hewlett Packard, DARPA, and Nynex.

For use by Suguru Ishizaki.  
This distribution is approved by Nicholas Negroponte, Director of 
the Media Laboratory, MIT.

Permission to use, copy, or modify these programs and their 
documentation for educational and research purposes only and 
without fee is hereby granted, provided that this copyright notice 
appears on all copies and supporting documentation.  For any other 
uses of this software, in original or modified form, including but not 
limited to distribution in whole or in part, specific prior permission 
must be obtained from MIT.  These programs shall not be used, 
rewritten, or adapted as the basis of a commercial software or 
hardware product without first obtaining appropriate licenses from 
MIT.  MIT makes no representations about the suitability of this 
software for any purpose.  It is provided "as is" without express or 
implied warranty."
******************************************************************************/





/*** basename.c --- dead@media-lab --- 11/25/85 ***/

#include <stdio.h>

char *Basename(str, sfx, dest)     /* v 1.0b */
     char *str, *sfx, *dest;
{
  char temp[128];
  char *p, *p1;
  char *subext();
  
  p = p1 = temp;
  strcpy(p, str);
  while (*p)
    {	
      if (*p++ == '/') p1 = p;
    }
  strcpy (dest, Subext(p1, sfx));
  return(dest);
}


